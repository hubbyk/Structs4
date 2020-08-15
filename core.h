//
// Created by hubbyk on 12.06.2020.
//

#ifndef STRUCTS4_CORE_H
#define STRUCTS4_CORE_H

#include "dbmainheader.h"
#include "dbtree.h"
#include "dbdatamanager.h"

enum requestType {ADD_RECORD, REMOVE_RECORD, EDIT_RECORD,
    SEARCH_BY, SORT_BY, SAVE_TO_FILE, LOAD_FROM_FILE};
enum columns {GENRE, PRICE, YEAR, RATING, PUBLISHING, NAME, AUTHORS, SHORT_DESCRIPTION};

void waitRequest();
int requestTypeMenu();

int chooseColumn();

void sortBy(struct treeNode* mainTree);
void searchBy(struct treeNode* mainTree);

void saveDbToFile(struct treeNode**);
void loadDbFromFile(struct treeNode** root);

void freeTree(struct treeNode* tree);
void freeTreeFull(struct treeNode* tree);

#endif //STRUCTS4_CORE_H
