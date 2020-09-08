//
// Created by hubbyk on 13.07.2020.
//

#ifndef STRUCTS4_DBDATAMANAGER_H
#define STRUCTS4_DBDATAMANAGER_H

#include "dbmainheader.h"
#include "dbtree.h"

int addRecord(struct treeNode** root);
int removeRecord(struct treeNode** root);
int editRecord(struct treeNode** root);

struct treeNode* buildByName(struct treeNode*, struct treeNode**);
struct treeNode* buildByGenre(struct treeNode*, struct treeNode**, wchar_t* genre);
struct treeNode* buildByPrice(struct treeNode*, struct treeNode**);
struct treeNode* buildByYear(struct treeNode*, struct treeNode**);
struct treeNode* buildByPubl(struct treeNode*, struct treeNode**);
struct treeNode* buildByAuth(struct treeNode*, struct treeNode**);
struct treeNode* buildByRating(struct treeNode*, struct treeNode**);

void searchN(struct treeNode*);
void searchG(struct treeNode*);
void searchP(struct treeNode*);
void searchY(struct treeNode*);
void searchPU(struct treeNode*);
void searchA(struct treeNode*);
void searchR(struct  treeNode*);

BOOK* updateBook(BOOK*);
void freeBook(BOOK* book);

#endif //STRUCTS4_DBDATAMANAGER_H
