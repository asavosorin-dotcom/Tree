#ifndef _AKINATOR_H_
#define _AKINATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "colors.h"

#define PRINT_IMAGE(...) fprintf(file_dump, __VA_ARGS__)
#define PRINT_HTM(...)   fprintf(file_htm, __VA_ARGS__)

enum Flag_free_t {FLAG_NO_FREE = 0, FLAG_FREE = 1};

struct AkinNode_t 
{
    char* string;
    AkinNode_t* left;
    AkinNode_t* right;
    AkinNode_t* parent;
    Flag_free_t flag_for_free;
};

enum Question_t {NO_QUESTION = 0, NEW_QUETION = 1};

AkinNode_t* AkinNodeCtor (char* data, AkinNode_t* parent, Flag_free_t flag);
AkinNode_t* AkinInsertElem(AkinNode_t** node, const char* value, AkinNode_t* parent);

void AkinDumpNode(AkinNode_t* node, FILE* file_dump);
void AkinDumpImage(AkinNode_t* node);
void AkinDump(AkinNode_t* node, const char* text);
void AkinPrintNode(const AkinNode_t* node);

int Akin(AkinNode_t* node);

void AkinAskQuestion(AkinNode_t* node);
void AkinGetAnswer  (char* answer);
AkinNode_t* AkinInsertNewElem(AkinNode_t* node);

char* Read_title(int* pos, char* buffer);
AkinNode_t* ReadNode(int* pos, char* buffer);

void AkinDtor(AkinNode_t* node);


#endif