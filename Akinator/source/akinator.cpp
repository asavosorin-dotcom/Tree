#include "akinator.h"

FILE* file_htm  = fopen("Logfile.htm", "w");
FILE* file_akin = fopen("akinat.txt" , "w");

static int index_png = 0;

AkinNode_t* AkinNodeCtor (char* data, AkinNode_t* parent, Flag_free_t flag)
{
    AkinNode_t* node = (AkinNode_t* ) calloc(1, sizeof(AkinNode_t));
    
    node->left = NULL;
    node->right = NULL;
    node->string = data;
    node->parent = parent;
    node->flag_for_free = flag; 

    return node;
}

void AkinDumpNode(AkinNode_t* node, FILE* file_dump)
{
    if (node->left == NULL && node->right == NULL)
        PRINT_IMAGE("\tnode%p[label = \"{%s | {0 | 0}}\", shape = Mrecord, style = \"filled\", fillcolor = \"#C0FFC0\"]\n", node , node->string);
    else
        PRINT_IMAGE("\tnode%p[label = \"{Is it %s? | {YES | NO}}\", shape = Mrecord, style = \"filled\", fillcolor = \"#C0FFC0\"]\n", node , node->string);
    // index *= 10;

    if (node->left != NULL) 
    {
        AkinDumpNode(node->left, file_dump);
        PRINT_IMAGE("\tnode%p -> node%p [color = \"blue\"]\n ", node, node->left);
        // index /= 10;
    }
    
    if (node->right != NULL)
    {
        AkinDumpNode(node->right, file_dump);
        // index = (index - 1) / 10;
        PRINT_IMAGE("\tnode%p -> node%p [color = \"red\"]\n", node, node->right);
    }
    
}

AkinNode_t* AkinInsertElem(AkinNode_t** node, const char* value, AkinNode_t* parent) // добавляет элемент в дерево
{
    // int res = a == b ? 1 : 0;

    char* data = strdup(value);
    *node = AkinNodeCtor(data, parent, FLAG_FREE);

    return *node;
}

// поиск элемента

void AkinDtor(AkinNode_t* node)
{
    if (node->left != NULL)
        AkinDtor(node->left);

    if (node->right != NULL)
        AkinDtor(node->right);
    
    if (node->flag_for_free == FLAG_FREE) free(node->string);
    free(node);
}

void AkinPrintNode(const AkinNode_t* node)
{
    
    fprintf(file_akin, "(");

    fprintf(file_akin, "\"%s\"", node->string);

    if (node->left)
        AkinPrintNode(node->left);
    else
        fprintf(file_akin, "nil");

    if (node->right)
        AkinPrintNode(node->right);
    else
        fprintf(file_akin, "nil");

    fprintf(file_akin, ")");
}

void AkinAskQuestion(AkinNode_t* node)
{
    printf("Is it %s? [Y/n]\n", node->string);
}

void AkinGetAnswer(char* answer)
{
    scanf("%s", answer);

    if (strcmp(answer, "Y") * strcmp(answer, "n") != 0)
    {
        printf("Wrong answer format. Please write Yes\\No\n");
        AkinGetAnswer(answer);
    }

}

int Akin(AkinNode_t* node)
{
    while (1)
    {
        AkinAskQuestion(node);

        static char answer[5] = "";

        AkinGetAnswer(answer);

        if (strcmp(answer, "Y") == 0) // переделать в switch
        {
            if (node->right == NULL)
            {
                printf("URAAAA!!!\n");
                break;
            } else
            {
                node = node->left;
            }
        }
        else
        {
            if (node->right == NULL)
            {
                AkinInsertNewElem(node);
                break;
            }
            else
            {
                node = node->right;
            }
        }

    }

    return NO_QUESTION;
}

AkinNode_t* AkinInsertNewElem(AkinNode_t* node)
{
    printf("Who is it?\n");

    char* new_elem = (char* ) calloc(30, sizeof(char)); 
    scanf(" %[^\n]", new_elem);

    printf("Write different with %s. It (verb)... \n", node->string);
    char new_question[30] = "";
    scanf(" %[^\n]", new_question);

    AkinNode_t* new_node_right = AkinNodeCtor(node->string, node, FLAG_FREE);
    node->string = strdup(new_question);
    
    printf("new_question = %s\n", node->string);
    node->right = new_node_right;
    // printf("###%p\n", new_node_question->right);

    AkinNode_t* new_node_left = AkinNodeCtor(new_elem, node, FLAG_FREE);
    node->left = new_node_left;

    return node;
}

void AkinDumpImage(AkinNode_t* node)
{
    const char* filename = "Akin_dump.txt";
    FILE* file_dump = fopen(filename, "w");
    
    PRINT_IMAGE("digraph {\n");
    AkinDumpNode(node, file_dump);

    PRINT_IMAGE("}");
    
    char command[100] = "";
    fclose(file_dump);
    
    sprintf(command, "dot \"%s\" -T png -o Akinator/pictures/graph%d.png", filename, index_png);
    // printf("command = %s\n", command);
    system(command);

    index_png++;
}

void AkinDump(AkinNode_t* node, const char* text)
{
    PRINT_HTM("<pre>\n");
    PRINT_HTM("\t<h3>DUMP %s</h3>\n", text);

    AkinDumpImage(node);

    PRINT_HTM("Image: \n <img src= \"Akinator/pictures/graph%d.png\">", index_png - 1);
    PRINT_HTM("</pre>");

}

// AkinNode_t* ReadNode(int* pos, const char* buffer)
// {
//     if (buffer[*pos] == '(')
//     {
//         AkinNode_t* node = AkinNodeCtor("")
//     }
// }