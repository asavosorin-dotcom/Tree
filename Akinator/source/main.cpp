#include "akinmain.h"

int main()
{
    AkinNode_t* node0 = AkinNodeCtor("Is it animal?");
    AkinNode_t* node1 = AkinInsertElem(&node0->left, "Poltorashka");
    AkinNode_t* node2 = AkinInsertElem(&node0->right, "Teach matan?");
    AkinNode_t* node3 = AkinInsertElem(&node2->left, "Petrovich");
    AkinNode_t* node4 = AkinInsertElem(&node2->right, "Pasha T");

    AkinDump(node0, "Akinator");
    AkinDtor(node0);
}