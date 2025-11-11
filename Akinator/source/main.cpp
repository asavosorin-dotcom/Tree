#include "akinmain.h"

extern FILE* file_akin;

int main(int argc, char* argv[])
{
    const char* filename = argv[1];
    char* code_tree = CreateBuffer(filename).buff + 1;
    
    printf("[%s]\n", code_tree);

    int position = 0;
    AkinNode_t* root = ReadNode(&position, code_tree);

    // char* data0 = strdup("animal");
    // AkinNode_t* root = AkinNodeCtor(data0, FLAG_FREE);
    // AkinNode_t* node1 = AkinInsertElem(&root->left, "Poltorashka", root);
    // AkinNode_t* node2 = AkinInsertElem(&root->right, "Teach matan", root);
    // AkinNode_t* node3 = AkinInsertElem(&node2->left, "Petrovich", node2);
    // AkinNode_t* node4 = AkinInsertElem(&node2->right, "Pasha T", node2);

    AkinDump(root, "Before akinator");

    do{
        Akin(root);
    } while (user_end_programm("Do you want to countine? [Y/n]"));

    AkinPrintNode(root);
    AkinDump(root, "Akinator");
    AkinDtor(root);

    free(code_tree - 1);
    fclose(file_akin);
}

int user_end_programm(const char* string)
{
    printf(BOLD_BLUE "%s\n" RESET, string);
    int command = getchar();

    switch (command)
    {
    case 'Y':
        return CONTINUE;
        break;
    
    case 'n':
        return END;
        break;

    default:
        return user_end_programm("Please enter [Y/n]\n");
        break;
    }
}