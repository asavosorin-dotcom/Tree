#include "main.h"

// строится массив случайных чисел, ссортируется и дамп ... и так 10 раз

// [1, 3, 7, 9, 12, 13, 15, 17, 23]

int main()
{   
    int arr[9] = {13, 3, 71, 91, 12, 19, 16, 17, 2};
    
    Node_t* node1 = NodeCtor(13);

    for (int i = 1; i < 9; i++)
    {
        TreeInsertElem(node1, arr[i]);
        // printf("[%d] node1 = [%p]\n", i, node1);
        TreeDump(node1, "First version");
    }
    
    PrintNode(node1);

    TreeDtor(node1);
    // м

}