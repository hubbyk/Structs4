//
// Created by hubbyk on 13.07.2020.
//

#include "dbdatamanager.h"

struct treeNode* buildByPrice(struct treeNode* mainTree, struct treeNode** newTree) {
    if(mainTree) {
        BOOK *book = (BOOK *) malloc(sizeof(BOOK));
        memcpy(book, mainTree->book, sizeof(BOOK));
        *newTree = insertP(*newTree, book);
    }
    if(mainTree->right) *newTree = buildByPrice(mainTree->right, newTree);
    if(mainTree->left) *newTree = buildByPrice(mainTree->left, newTree);
    return *newTree;
}
struct treeNode* buildByName(struct treeNode* mainTree, struct treeNode** newTree) {
    return mainTree;
}
struct treeNode* buildByGenre(struct treeNode* mainTree, struct treeNode** newTree, wchar_t* genre) {
    if(mainTree) {
        struct treeNode* tmp = mainTree;
        while (tmp) {
            if(genreCompare(genre, tmp->book->genre)) {
                BOOK *book = (BOOK *) malloc(sizeof(BOOK));
                memcpy(book, tmp->book, sizeof(BOOK));
                *newTree = insertN(*newTree, book);
            }
            tmp = tmp->nextBook;
        }
    }
    if(mainTree->right) *newTree = buildByGenre(mainTree->right, newTree, genre);
    if(mainTree->left) *newTree = buildByGenre(mainTree->left, newTree, genre);
    return *newTree;
}
struct treeNode* buildByYear(struct treeNode* mainTree, struct treeNode** newTree) {
    if(mainTree) {
        BOOK *book = (BOOK *) malloc(sizeof(BOOK));
        memcpy(book, mainTree->book, sizeof(BOOK));
        *newTree = insertY(*newTree, book);
    }
    if(mainTree->right) *newTree = buildByYear(mainTree->right, newTree);
    if(mainTree->left) *newTree = buildByYear(mainTree->left, newTree);
    return *newTree;
}
struct treeNode* buildByPubl(struct treeNode* mainTree, struct treeNode** newTree) {
    if(mainTree) {
        BOOK *book = (BOOK *) malloc(sizeof(BOOK));
        memcpy(book, mainTree->book, sizeof(BOOK));
        *newTree = insertPU(*newTree, book);
    }
    if(mainTree->right) *newTree = buildByPubl(mainTree->right, newTree);
    if(mainTree->left) *newTree = buildByPubl(mainTree->left, newTree);
    return *newTree;
}
struct treeNode* buildByAuth(struct treeNode* mainTree, struct treeNode** newTree) {
    if(mainTree) {
        BOOK *book = (BOOK *) malloc(sizeof(BOOK));
        memcpy(book, mainTree->book, sizeof(BOOK));
        *newTree = insertA(*newTree, book);
    }
    if(mainTree->right) *newTree = buildByAuth(mainTree->right, newTree);
    if(mainTree->left) *newTree = buildByAuth(mainTree->left, newTree);
    return *newTree;
}
struct treeNode* buildByRating(struct treeNode* mainTree, struct treeNode** newTree) {
    if(mainTree) {
        BOOK *book = (BOOK *) malloc(sizeof(BOOK));
        memcpy(book, mainTree->book, sizeof(BOOK));
        *newTree = insertR(*newTree, book);
    }
    if(mainTree->right) *newTree = buildByRating(mainTree->right, newTree);
    if(mainTree->left) *newTree = buildByRating(mainTree->left, newTree);
    return *newTree;
}

int addRecord(struct treeNode** root) {
    BOOK* book = readBook();

    if(book) {
        *root = insertN(*root, book);
        return 1;
    }else {
        wprintf(L"Incorrect input\n");
        return 0;
    }
}
int removeRecord(struct treeNode** root) {
    BOOK* book = readBook();
    if(book) {
        removeFromTree(*root, book);
        return 1;
    }
    wprintf(L"Incorrect input\n");
    return 0;
}
int editRecord(struct treeNode** root) {
    BOOK* book = readBook();
    if (!book) {
        wprintf(L"Incorrect input\n");
        return 0;
    }
    struct treeNode* result = removeFromTree(*root, book);

    if(result) {
        book = updateBook(book);
        result = insertN(result, book);
        *root = result;
    }else {
        wprintf(L"Not found");
    }

    return 1;
}


void searchN(struct treeNode* mainTree) {
    wchar_t* name;
    struct treeNode* result;

    name = readName();

    if((result = searchByName(mainTree, name))) {
        while (result) {
            printBook(result->book);
            result = result->nextBook;
        }
    }else {
        wprintf(L"Not found.\n");
    }
}
void searchG(struct treeNode* mainTree) {
    wchar_t* genre;
    struct treeNode* newTree = NULL;

    genre = readGenre();

    newTree = buildByGenre(mainTree, &newTree, genre);

    if(newTree) {
        printTree(newTree);
    }else {
        wprintf(L"Not found.\n");
    }
}
void searchP(struct treeNode* mainTree) {
    int price;
    struct treeNode* result,* newTree = NULL;

    price = readPrice();

    newTree = buildByPrice(mainTree, &newTree);

    if((result = searchByPrice(newTree, price))) {
        while (result) {
            printBook(result->book);
            result = result->nextBook;
        }
    }else {
        wprintf(L"Not found.\n");
    }
}
void searchY(struct treeNode* mainTree) {
    int year;
    struct treeNode* result,* newTree = NULL;

    year = readYear();

    newTree = buildByYear(mainTree, &newTree);

    if((result = searchByYear(mainTree, year))) {
        while (result) {
            printBook(result->book);
            result = result->nextBook;
        }
    }else {
        wprintf(L"Not found.\n");
    }
}
void searchPU(struct treeNode* mainTree) {
    wchar_t* publishing;
    struct treeNode* result,* newTree = NULL;

    publishing = readPublishing();

    newTree = buildByPubl(mainTree, &newTree);

    if((result = searchByPublishing(mainTree, publishing))) {
        while (result) {
            printBook(result->book);
            result = result->nextBook;
        }
    }else {
        wprintf(L"Not found.\n");
    }
}
void searchA(struct treeNode* root) {
    wchar_t* author;

    author = readAuthor();

    searchByAuthor(root, author);
}
void searchR(struct  treeNode* mainTree) {
    float rating;
    struct treeNode* result,* newTree = NULL;

    rating = readRating();

    newTree = buildByRating(mainTree, &newTree);

    if((result = searchByRating(newTree, rating))) {
        while (result) {
            printBook(result->book);
            result = result->nextBook;
        }
    }else {
        wprintf(L"Not found.\n");
    }
}

BOOK* updateBook(BOOK* book) {
    int userChoice = 0;
    wchar_t ch;

    wprintf(L"Update name?(0 - yes, another number - no)\n");
    wscanf(L"%d", &userChoice);
    getwchar();
    if(!userChoice) {
        book->name = readName();
    }

    wprintf(L"\nUpdate genre?(0 - yes, another number - no)\n");
    wscanf(L"%d", &userChoice);
    while((ch = getwchar()) != '\n');
    if(!userChoice) {
        book->genre = readGenre();
    }

    wprintf(L"\nUpdate publishing?(0 - yes, another number - no)\n");
    wscanf(L"%d", &userChoice);
    while((ch = getwchar()) != '\n');
    if(!userChoice) {
        book->publishing = readPublishing();
    }

    wprintf(L"\nUpdate description?(0 - yes, another number - no)\n");
    wscanf(L"%d", &userChoice);
    while((ch = getwchar()) != '\n');
    if(!userChoice) {
        book->description = readShortDescription();
    }

    wprintf(L"Update authors?(0 - yes, another number - no)\n");
    wscanf(L"%d", &userChoice);
    while((ch = getwchar()) != '\n');
    if(!userChoice) {
        int count = 0;
        book->authors = readAuthors(&count);
        book->authCount = count;
    }

    wprintf(L"Update year?(0 - yes, another number - no)\n");
    wscanf(L"%d", &userChoice);
    while((ch = getwchar()) != '\n');
    if(!userChoice) {
        book->year = readYear();
    }

    wprintf(L"Update price?(0 - yes, another number - no)\n");
    wscanf(L"%d", &userChoice);
    while((ch = getwchar()) != '\n');
    if(!userChoice) {
        book->price = readPrice();
    }

    wprintf(L"Update rating?(0 - yes, another number - no)\n");
    wscanf(L"%d", &userChoice);
    while((ch = getwchar()) != '\n');
    if(!userChoice) {
        book->rating = readRating();
    }

    return book;
}