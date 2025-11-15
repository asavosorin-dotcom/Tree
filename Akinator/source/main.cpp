#include "akinmain.h"

int main(int argc, char* argv[])
{
    setlocale(LC_CTYPE, "");
    wprintf(L"Кто это?\n");
    

    const char* filenameread = argv[1];
    char* code_tree = CreateBuffer(filenameread).buff + 1;
    
    FILE* file_akin = NULL;

    switch (argc)
    {
        case 2:
        {
            file_akin = fopen(argv[1], "w");
            break;
        }
        
        case 3:
        {
            file_akin = fopen(argv[2], "w");
            break;
        }


    default:
        return 0;
    }

    // wchar_t* data0 = (wchar_t*) strdup("животное");
    // AkinNode_t* root = AkinNodeCtor(data0, NULL, FLAG_FREE);
    // AkinNode_t* node1 = AkinInsertElem(&root->left, "Полторашка", root);
    // AkinNode_t* node2 = AkinInsertElem(&root->right, "Ведет матан", root);
    // AkinNode_t* node3 = AkinInsertElem(&node2->left, "Petrovich", node2);
    // AkinNode_t* node4 = AkinInsertElem(&node2->right, "Pasha T", node2);

    // printf("[%s]\n", code_tree);

    int position = 0;
    AkinNode_t* root = ReadNode(&position, code_tree);

    // if (root == NULL)
    // {
    //     root = AkinNodeCtor(strdup("Neizvestno chto?"), NULL, FLAG_FREE);
    // }

    // сбросить буфера

    AkinDump(root, L"Before akinator");

    printf(GREEN "Start? [y/n]\n" RESET);
    int c = getchar();

    if (c == 'n')
    {
        AkinDtor(root);
        free(code_tree - 1);
        fclose(file_akin);
        return 0;
    }

    do{
        Akin(root);
    } while (user_end_programm("Хочешь продолжить?"));

    AkinPrintDefinition(root);
    AkinPrintDifference(root);

    AkinPrintNode(root, file_akin);
    AkinDump(root, L"Akinator");

    // с клавиатуры

    AkinDtor(root);

    free(code_tree - 1);
    fclose(file_akin);
}

int user_end_programm(const char* string)
{
    printf(BOLD_BLUE "%s\n" RESET, string);
    clear_input_buffer();
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