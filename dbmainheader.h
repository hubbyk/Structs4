//
// Created by hubbyk on 13.07.2020.
//

#ifndef STRUCTS4_DBMAINHEADER_H
#define STRUCTS4_DBMAINHEADER_H

#include "dbio.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define genre_horror_en  L"Horror"
#define genre_horror_ru  L"Хоррор"
#define genre_thriller_en  L"Thriller"
#define genre_thriller_ru  L"Триллер"
#define genre_gothic_en  L"Gothic"
#define genre_gothic_ru  L"Готика"

enum genres {HORROR = 1, THRILLER, GOTHIC};

typedef struct{
    int authCount;
    int year;
    int price;
    float rating;
    wchar_t* name;
    wchar_t* genre;
    wchar_t* publishing;
    wchar_t* description;
    wchar_t** authors;
}BOOK;




#endif //STRUCTS4_DBMAINHEADER_H
