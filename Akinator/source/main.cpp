#include "akinmain.h"

extern FILE* file_akin;

int main()
{
    AkinNode_t* node0 = AkinNodeCtor("animal", NULL);
    AkinNode_t* node1 = AkinInsertElem(&node0->left, "Poltorashka", node0);
    AkinNode_t* node2 = AkinInsertElem(&node0->right, "Teach matan", node0);
    AkinNode_t* node3 = AkinInsertElem(&node2->left, "Petrovich", node2);
    AkinNode_t* node4 = AkinInsertElem(&node2->right, "Pasha T", node2);

    AkinDump(node0, "Before akinator");

    do{
        Akin(node0);
    } while (user_end_programm("Do you want to countine? [Y/n]"));

    AkinPrintNode(node0);
    AkinDump(node0, "Akinator");
    AkinDtor(node0);
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