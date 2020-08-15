//
// Created by hubbyk on 12.06.2020.
//

#ifndef STRUCTS4_DBTREE_H
#define STRUCTS4_DBTREE_H

#include "dbmainheader.h"

struct treeNode {
    BOOK* book;
    unsigned char height;
    struct treeNode* left;
    struct treeNode* right;
    struct treeNode* nextBook;
};

BOOK* newBook(int authCount, int year, int price, float rating, wchar_t* name, wchar_t** authors, wchar_t* genre, wchar_t* publishing, wchar_t* description);
int bookCompare(BOOK*, BOOK*);

BOOK* readBookFromFile(FILE* inputFile);
BOOK* readBook();

void printBook(BOOK* book);
void writeBook(BOOK* book, FILE* inputFile);

int authCompare(BOOK* book1, BOOK* book2);
wchar_t** sortAuth(wchar_t**, int authCount);
int isAuthor(BOOK* book, wchar_t* author);

int ratingsCompare(float rate1, float rate2);
int whatGenre(wchar_t* str);
int genreCompare(wchar_t* str, wchar_t* str1);

struct treeNode* newRecord(BOOK* newBook);

unsigned char height(struct treeNode* p);
int balanceFactor(struct treeNode* p);
void fixHeight(struct treeNode* p);

struct treeNode* rotateRight(struct treeNode* p);
struct treeNode* rotateLeft(struct treeNode* q);

struct treeNode* balance(struct treeNode* p);
struct treeNode* findMin(struct treeNode* p);
struct treeNode* removeMin(struct treeNode* p);

struct treeNode* removeFromTree(struct treeNode* p, BOOK* newBook);

struct treeNode* insertN(struct treeNode* p, BOOK* newBook);
struct treeNode* insertP(struct treeNode* p, BOOK* newBook);
struct treeNode* insertY(struct treeNode* p, BOOK* newBook);
struct treeNode* insertPU(struct treeNode* p, BOOK* newBook);
struct treeNode* insertA(struct treeNode* p, BOOK* newBook);
struct treeNode* insertR(struct treeNode* p, BOOK* newBook);

struct treeNode* searchByName(struct treeNode* p, wchar_t* name);
struct treeNode* searchByPublishing(struct treeNode* p, wchar_t* publishing);
struct treeNode* searchByAuthor(struct treeNode* p, wchar_t* author);
struct treeNode* searchByPrice(struct treeNode* p, int price);
struct treeNode* searchByYear(struct treeNode* p, int year);
struct treeNode* searchByRating(struct treeNode* p, float rating);

void printTree(struct treeNode* root);
void saveToFile(struct treeNode* root, FILE* inputFile);
void readFromFile(struct treeNode** root, FILE* inputFile);
#endif //STRUCTS4_DBTREE_H
