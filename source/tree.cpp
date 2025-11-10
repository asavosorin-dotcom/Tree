#include "tree.h"

FILE* file_htm  = fopen("Logfile.htm", "w");
static int index_png = 0;

Node_t* NodeCtor (TreeElem_t data)
{
    Node_t* node = (Node_t* ) calloc(1, sizeof(Node_t));
    
    node->data = data;
    node->left = NULL;
    node->right = NULL; 

    return node;
}

void TreeDumpNode(Node_t* node, FILE* file_dump)
{

    PRINT_IMAGE("\tnode%p[label = \"{%p | %d | {%p | %p}}\", shape = Mrecord, style = \"filled\", fillcolor = \"#C0FFC0\"]\n", node , node, node->data, node->left, node->right);
    // index *= 10;

    if (node->left != NULL) 
    {
        TreeDumpNode(node->left, file_dump);
        PRINT_IMAGE("\tnode%p -> node%p [color = \"blue\"]\n ", node, node->left);
        // index /= 10;
    }
    
    if (node->right != NULL)
    {
        TreeDumpNode(node->right, file_dump);
        // index = (index - 1) / 10;
        PRINT_IMAGE("\tnode%p -> node%p [color = \"red\"]\n", node, node->right);
    }
    
}

//       40
//    20    60
//  10  

Node_t* TreeInsertElem(Node_t* node, TreeElem_t value) // добавляет элемент в отсортированное дерево
{
    // int res = a == b ? 1 : 0;

    if (node == NULL)
    {
        node = NodeCtor(value);
        return node;
    }

    if (value <= node->data)
    {
        node->left = TreeInsertElem(node->left, value);
    }
    else
    {
       node->right = TreeInsertElem(node->right, value);
    }
    
    return node;
}

// поиск элемента

void TreeDtor(Node_t* node)
{
    if (node->left != NULL)
        TreeDtor(node->left);

    if (node->right != NULL)
        TreeDtor(node->right);
    
    free(node);
}

void PrintNode(const Node_t* node) // три разных буффера
{
    
    printf("(");

    if (node->left)
        PrintNode(node->left);
    
    printf("%d", node->data);

    if (node->right)
        PrintNode(node->right);

    printf(")");
}

void TreeDumpImage(Node_t* node)
{
    const char* filename = "tree_dump.txt";
    FILE* file_dump = fopen(filename, "w");
    
    PRINT_IMAGE("digraph {\n");
    TreeDumpNode(node, file_dump);

    PRINT_IMAGE("}");
    
    char command[100] = "";
    fclose(file_dump);
    
    sprintf(command, "dot \"%s\" -T png -o pictures/graph%d.png", filename, index_png);
    // printf("command = %s\n", command);
    system(command);

    index_png++;
}

void TreeDump(Node_t* node, const char* text)
{
    PRINT_HTM("<pre>\n");
    PRINT_HTM("\t<h3>DUMP %s</h3>\n", text);

    TreeDumpImage(node);

    PRINT_HTM("Image: \n <img src= \"pictures/graph%d.png\">", index_png - 1);
    PRINT_HTM("</pre>");
}

// void MakeTreeSort(int* arr, int capasity)
// {
    // 
// }