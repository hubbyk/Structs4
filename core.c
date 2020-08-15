//
// Created by hubbyk on 12.06.2020.
//

#include "core.h"
#include "dbtree.h"

void waitRequest() {
    struct treeNode** MAIN_TREE_ROOT = (struct treeNode**)malloc(sizeof(struct treeNode*));

    for(;;) {
        switch (requestTypeMenu()) {
            case ADD_RECORD:
                addRecord(MAIN_TREE_ROOT);
                printTree(*MAIN_TREE_ROOT);
                break;
            case REMOVE_RECORD:
                if(*MAIN_TREE_ROOT) {
                    removeRecord(MAIN_TREE_ROOT);
                    printTree(*MAIN_TREE_ROOT);
                }else {
                    wprintf(L"Data base not loaded.\n");
                }
                break;
            case EDIT_RECORD:
                if(*MAIN_TREE_ROOT) {
                    editRecord(MAIN_TREE_ROOT);
                    printTree(*MAIN_TREE_ROOT);
                }else {
                    wprintf(L"Data base not loaded.\n");
                }
                break;
            case SEARCH_BY:
                if(*MAIN_TREE_ROOT) {
                    searchBy(*MAIN_TREE_ROOT);
                }else {
                    wprintf(L"Data base not loaded.\n");
                }
                break;
            case SORT_BY:
                if(*MAIN_TREE_ROOT) {
                    sortBy(*MAIN_TREE_ROOT);
                }else {
                    wprintf(L"Data base not loaded.\n");
                }
                break;
            case SAVE_TO_FILE:
                if(*MAIN_TREE_ROOT) {
                    saveDbToFile(MAIN_TREE_ROOT);
                }else {
                    wprintf(L"Data base not loaded.\n");
                }
                break;
            case LOAD_FROM_FILE:
                loadDbFromFile(MAIN_TREE_ROOT);
                printTree(*MAIN_TREE_ROOT);
                break;
            default:
                return;
        }
    }
}
int requestTypeMenu() {
    int userChoice;

    wprintf(L"===========MENU===========\n\
1.Add new book    2.Remove book\n\
3.Edit book       4.Search book\n\
5.Sort books by   6.Save DB to file\n\
7.Load DB from file\n\
Enter the number: ");

    wscanf(L"%d", &userChoice);
    getwchar();

    if(ADD_RECORD + 1 <= userChoice && userChoice <= LOAD_FROM_FILE + 1) {
        return userChoice - 1;
    }else {
        wprintf(L"ERROR: incorrect input\n");
        return 100;
    }
}

void saveDbToFile(struct treeNode** root) {
    FILE* inputFile;
    char* buff = (char*)calloc(1, sizeof(char )), ch;
    wchar_t wch;
    int len = 0;

    wprintf(L"Enter file name: ");
    while((ch = (char)getwchar()) != '\n') {
        ++len;
        buff = (char*)realloc(buff, len*sizeof(char));
        buff[len - 1] = ch;
    }
    ++len;
    buff = (char*)realloc(buff, len*sizeof(char));
    buff[len - 1] = '\0';

    inputFile = fopen(buff, "wb");

    fseek(inputFile,0, SEEK_END);
    int fileSize = (int)ftell(inputFile);
    if(fileSize) {
        wprintf(L"WARNING: this file is always exist!\nDo you want to rewrite it?(Y - yes, anything else - no): ");
        wscanf(L"%c\n", &wch);
        if(wch != L'Y') {
            fclose(inputFile);
            return;
        }
    }
    saveToFile(*root, inputFile);

    fclose(inputFile);
}
void loadDbFromFile(struct treeNode** root) {
    FILE* inputFile;
    char* buff, ch;
    int len = 0;

    buff = (char*)malloc(sizeof(char));

    wprintf(L"Enter file name: ");
    while((ch = (char)getwchar()) != '\n') {
        ++len;
        buff = (char*)realloc(buff, len*sizeof(char));
        buff[len - 1] = ch;
    }
    ++len;
    buff = (char*)realloc(buff, len*sizeof(char));
    buff[len - 1] = '\0';

    inputFile = fopen(buff, "rb");

    readFromFile(root, inputFile);

    fclose(inputFile);
}

int chooseColumn() {
    int userChoice;

    wprintf(L"Choose column:\n\
1.Genre    2.Price\n\
3.Year     4.Rating\n\
5.Publishing\n\
6.Name     7.Authors\n\
Enter the number: ");

    wscanf(L"%d", &userChoice);
    getwchar();

    if(GENRE + 1 <= userChoice && userChoice <= SHORT_DESCRIPTION) {
        return userChoice - 1;
    }else {
        wprintf(L"ERROR: incorrect input\n");
        return 100;
    }
}

void sortBy(struct treeNode* mainTree) {
    int k = chooseColumn();
    wchar_t* buf = NULL;
    struct treeNode** tree = (struct treeNode**)malloc(sizeof(struct treeNode*));
    *tree = NULL;

    switch (k) {
        case GENRE:
            buf = readGenre();
            *tree = buildByGenre(mainTree, tree, buf);
            break;
        case PRICE:
            *tree = buildByPrice(mainTree, tree);
            break;
        case YEAR:
            *tree = buildByYear(mainTree, tree);
            break;
        case RATING:
            *tree = buildByRating(mainTree, tree);
            break;
        case PUBLISHING:
            *tree = buildByPubl(mainTree, tree);
            break;
        case NAME:
            *tree = buildByName(mainTree, tree);
            break;
        case AUTHORS:
            *tree = buildByAuth(mainTree, tree);
            break;
        default:
            return;
    }

    if(*tree != NULL) {
        printTree(*tree);
        freeTree(*tree);
    }
}
void searchBy(struct treeNode* mainTree) {
    int k = chooseColumn();
    struct treeNode** tree = (struct treeNode**)malloc(sizeof(struct treeNode*));
    *tree = NULL;

    switch (k) {
        case GENRE:
            searchG(mainTree);
            break;
        case PRICE:
            searchP(mainTree);
            break;
        case YEAR:
            searchY(mainTree);
            break;
        case PUBLISHING:
            searchPU(mainTree);
            break;
        case NAME:
            searchN(mainTree);
            break;
        case AUTHORS:
            searchA(mainTree);
            break;
        case RATING:
            searchR(mainTree);
            break;
        default:
            return;
    }
}

void freeTree(struct treeNode* tree) {
    if(tree->right) freeTree(tree->right);
    if(tree->left) freeTree(tree->left);
    if(tree != NULL) free(tree);
}