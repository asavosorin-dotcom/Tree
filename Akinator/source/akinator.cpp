#include "akinator.h"

FILE* file_htm  = fopen("Logfile.htm", "w");
FILE* file_akin = fopen("akinat1.txt" , "w");

static int index_png = 0;

AkinNode_t* AkinNodeCtor (char* data, AkinNode_t* parent, Flag_free_t flag)
{
    AkinNode_t* node = (AkinNode_t* ) calloc(1, sizeof(AkinNode_t));
    
    node->left = NULL;
    node->right = NULL;
    node->string = data;
    node->flag_for_free = flag; 
    node->parent = parent;
    node->yes_no = FLAG_YES;

    return node;
}

void AkinDumpNode(AkinNode_t* node, FILE* file_dump)
{
    if (node->left == NULL && node->right == NULL)
        PRINT_IMAGE("\tnode%p[label = \"{%p |%s | %d | {0 | 0}}\", shape = Mrecord, style = \"filled\", fillcolor = \"#C0FFC0\"]\n", node, node->parent , node->string, node->rank);
    else
        PRINT_IMAGE("\tnode%p[label = \"{%p | %d | Is it %s? | {YES | NO}}\", shape = Mrecord, style = \"filled\", fillcolor = \"#C0FFC0\"]\n", node, node->parent, node->rank, node->string);
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

    if (strcmp(answer, "y") * strcmp(answer, "n") != 0)
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

        if (strcmp(answer, "y") == 0) // переделать в switch
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

    AkinNode_t* new_node_right = AkinNodeCtor(node->string, node, FLAG_NO_FREE);
    node->string = strdup(new_question);
    node->flag_for_free = FLAG_FREE;
    
    // printf("new_question = %s\n", node->string);
    node->right = new_node_right;
    node->right->rank = node->rank + 1;
    node->right->yes_no = FLAG_NO;
    // printf("###%p\n", new_node_question->right);

    AkinNode_t* new_node_left = AkinNodeCtor(new_elem, node, FLAG_FREE);
    node->left = new_node_left;
    node->left->rank = node->rank + 1;
    node->left->yes_no = FLAG_YES;

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

AkinNode_t* ReadNode(int* pos, char* buffer)
{
    // printf(BOLD_BLUE "In beginnig read: [%s]\n" RESET, buffer + *pos);

    static int rank = 0;
    rank++;

    if (buffer[*pos] == '(')
    {
        AkinNode_t* node = AkinNodeCtor(NULL, NULL, FLAG_NO_FREE);
        (*pos)++; // пропуск скобки
        node->string = Read_title(pos, buffer);
        node->rank = rank;
        node->left = ReadNode(pos, buffer);
        rank--;
        
        if (node->left != NULL)
        {
            node->left->parent = node;
            node->left->yes_no = FLAG_YES;
        }        

        node->right = ReadNode(pos, buffer);
        rank--;
        
        if (node->right != NULL)
        {
            node->right->parent = node; 
            node->right->yes_no = FLAG_NO;
        }
        
        if (buffer[*pos] == ')')
            (*pos)++;
            
        // printf("%s\n", buffer + *pos);
        return node;
    }
    else if (buffer[*pos] == 'n' /*&& buffer[*pos + 1] == 'i' && buffer[*pos + 2] == 'l'*/)
    {
        *pos += strlen("nil");
        // printf("if nil [%s]\n", buffer + *pos);
        return NULL;
    }
    else 
    {
        printf("[%s]\n", buffer);
        // printf(RED "ERROR format code tree\n" RESET);
        return NULL;
    }
    // return ;
}

char* Read_title(int* pos, char* buffer) // можно возвращать len и вручную изменять указатель, но потом не вызывать strlen()
{
    int len = 0;
    // printf("In read title = [%s]\n", buffer + *pos);
    sscanf(buffer + *pos, " \"%*[^\"]\"%n", &len);
    *(buffer + *pos + len - 1) = '\0';
    (*pos) += len;
    // printf(CYAN "In read title = [%s]\n" RESET, buffer + *pos + 1);

    return buffer + *pos - len + 1;
}

AkinNode_t* AkinGetNode (AkinNode_t* root, char* text)
{
    assert(text);
    
    AkinNode_t* node = NULL;

    static int counter_iter = 0;
    counter_iter++;

    if (strcmp(root->string, text) == 0)
    {
        printf("comp [%d] %s\n", counter_iter, root->string);
        return root;
    }
    
    
    if (root->left == NULL && root->right == NULL)
    {
        return NULL;
    }
    
    node = AkinGetNode(root->left, text);

    if (node)
    {
        printf("[%d] %s\n", counter_iter, node->string);
        return node;
    }

    node = AkinGetNode(root->right, text);

    if (node)
    {
        printf("[%d] %s\n", counter_iter, node->string);
        return node;
    }

    printf("[%d]\n", counter_iter);

    if (root->parent == NULL) printf(BOLD_RED "No such word\n" RESET);

    return NULL;
}

void AkinMakeDefinition(AkinNode_t* node, AkinNode_t* root)
{
    char* definit[1000] = {};
    int counter_words = 0;

    int flag_no = 0;

    for (;node != root->parent; node = node->parent)
    {
        definit[counter_words++] = node->string;
        if (flag_no == 1)
        {
            definit[counter_words++] = "ne";
            flag_no = 0;
        }

        if (node->yes_no == FLAG_NO)
        {
            flag_no = 1;
        }
        
    }

    for (int index = counter_words - 1; index > 0; index--)
    {
        printf("%s ", definit[index]);
    }

    printf("\n");
}

void AkinPrintDefinition(AkinNode_t* root, char* name)
{
    AkinNode_t* node = AkinGetNode(root, name);
    printf("%s - eto ", node->string);
    AkinMakeDefinition(node, root);
}

void AkinPrintDifference(AkinNode_t* root, char* name1, char* name2)
{
    AkinNode_t* node1 = AkinGetNode(root, name1);
    AkinNode_t* node2 = AkinGetNode(root, name2);
    
    AkinNode_t* node_max = node2;
    AkinNode_t* node_min = node1;

    if (node1->rank >= node2->rank)
    {
        AkinNode_t* node_max = node1;
        AkinNode_t* node_min = node2;
    }

    for (int counter = 0; counter < (node_max->rank - node_min->rank); counter++, node_max = node_max->parent) 
    {;}

    for (; node_max != node_min; node_max = node_max->parent, node_min = node_min->parent)
    {;}

    printf("Similarity %s and %s: ", name1, name2);
    AkinMakeDefinition(node_min, root);

    printf("Difference %s and %s:\n  ", name1, name2);
    printf("%s: ", name1);
    AkinMakeDefinition(node1, node_min);
    printf("%s: ", name2);
    AkinMakeDefinition(node2, node_min);
}