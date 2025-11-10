#include "akinator.h"

FILE* file_htm  = fopen("Logfile.htm", "w");
static int index_png = 0;

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

AkinNode_t* AkinInsertElem(AkinNode_t** node, char* value) // добавляет элемент в отсортированное дерево
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

// void PrintNode(const AkinNode_t* node) // три разных буффера
// {
    
//     printf("(");

//     if (node->left)
//         PrintNode(node->left);
    
//     printf("%d", node->string);

//     if (node->right)
//         PrintNode(node->right);

//     printf(")");
// }

void AkinAskQuestion(AkinNode_t* node)
{
    printf("%s\n", node->string);
}

void AkinGetAnswer(char* answer)
{
    scanf("%s", answer);

    if (strcmp(answer, "Yes") * strcmp(answer, "No") != 0)
    {
        printf("Wrong answer format. Please write Yes/No\n");
        AkinGetAnswer(answer);
    }
    
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

// void MakeAkinSort(int* arr, int capasity)
// {
    // 
// }