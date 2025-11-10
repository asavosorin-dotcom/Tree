#include "akinator.h"

FILE* file_htm  = fopen("Logfile.htm", "w");
FILE* file_akin = fopen("akinat.txt", "w");

static int index_png = 0;

char* arr[20] = {};
int counter = 0;

AkinNode_t* AkinNodeCtor (char* data)
{
    AkinNode_t* node = (AkinNode_t* ) calloc(1, sizeof(AkinNode_t));
    
    node->string = data;
    node->left = NULL;
    node->right = NULL; 

    return node;
}

void AkinDumpNode(AkinNode_t* node, FILE* file_dump)
{

    PRINT_IMAGE("\tnode%p[label = \"{%s | {YES | NO}}\", shape = Mrecord, style = \"filled\", fillcolor = \"#C0FFC0\"]\n", node , node->string);
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

//       40
//    20    60
//  10  

AkinNode_t* AkinInsertElem(AkinNode_t** node, char* value) // добавляет элемент в дерево
{
    // int res = a == b ? 1 : 0;

    *node = AkinNodeCtor(value);

    return *node;
}

// поиск элемента

void AkinDtor(AkinNode_t* node)
{
    if (node->left != NULL)
        AkinDtor(node->left);

    if (node->right != NULL)
        AkinDtor(node->right);
    
    free(node);
}

void AkinPrintNode(const AkinNode_t* node)
{
    
    fprintf(file_akin, "(");

    if (node->left)
        AkinPrintNode(node->left);
    
    fprintf(file_akin, "\"%s\"", node->string);

    if (node->right)
        AkinPrintNode(node->right);

    fprintf(file_akin, ")");
}

void AkinAskQuestion(AkinNode_t* node)
{
    printf("%s\n", node->string);
}

void AkinGetAnswer(char* answer)
{
    scanf("%s", answer);

    if (strcmp(answer, "Yes") * strcmp(answer, "No") != 0)
    {
        printf("Wrong answer format. Please write Yes\\No\n");
        AkinGetAnswer(answer);
    }

}

int Akin(AkinNode_t* node)
{
    int flag = 0;

    AkinAskQuestion(node);

    static char answer[5] = "";

    AkinGetAnswer(answer);

    if (strcmp(answer, "Yes") == 0)
    {
        if (node->right == NULL)
        {
            printf("URAAAA!!!\n");
        }
        else
        {
            flag = Akin(node->left);
            printf("flag = %d\n", flag);
            if (flag == NEW_QUETION)
            {
                printf("#%s\n", node->string);
                printf("#node->left[%p]\n", node->left);
                node->left = AkinInsertNewElem(node->left);
                printf("node[%p]\n", node->left);
                printf("node->left[%p]\n", node->left->left);
                printf("node->right[%p]\n", node->left->right);

            }
        }
    }
    else
    {
        if (node->right == NULL)
        {
            return NEW_QUETION;
        }
        else
        {
            flag = Akin(node->right);
            if (flag == NEW_QUETION)
            {
                node->right = AkinInsertNewElem(node->left);
            }
        }
    }
    
    return NO_QUESTION;
}

AkinNode_t* AkinInsertNewElem(AkinNode_t* node)
{
    printf("Who is it?\n");

    char* new_elem = (char* ) calloc(30, sizeof(char));
    scanf("%s", new_elem);
    arr[counter] = new_elem;
    counter++; 

    printf("Write different with %s. It (verb)... \n", node->string);
    char* new_question = (char* ) calloc(30, sizeof(char));
    scanf("%s", new_question);
    arr[counter] = new_question;
    counter++;

    AkinNode_t* new_node_question = AkinNodeCtor(new_question);
    printf("new_question = %s\n", new_node_question->string);
    new_node_question->right = node;
    printf("###%p\n", new_node_question->right);
    node->left = NULL;
    node->right = NULL;

    AkinNode_t* new_node_elem = AkinNodeCtor(new_elem);
    new_node_question->left = new_node_elem;

    return new_node_question;
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

    for (int i = 0; i < counter - 1; i++)
        free(arr[i]);
}

// void MakeAkinSort(int* arr, int capasity)
// {
    // 
// }