#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>

#define PRINT_IMAGE(...) fprintf(file_dump, __VA_ARGS__)
#define PRINT_HTM(...)   fprintf(file_htm, __VA_ARGS__)

typedef int TreeElem_t;

struct Node_t 
{
    TreeElem_t data;
    Node_t* left;
    Node_t* right;
};

Node_t* NodeCtor (TreeElem_t data);
void TreeDumpNode(Node_t* node, FILE* file_dump);
void TreeDumpImage(Node_t* node);
void TreeDump(Node_t* node, const char* text);
Node_t* TreeInsertElem(Node_t* node, TreeElem_t value);
void PrintNode(const Node_t* node);

void TreeDtor(Node_t* node);

#endif