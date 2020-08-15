//
// Created by hubbyk on 13.07.2020.
//

#ifndef STRUCTS4_DBIO_H
#define STRUCTS4_DBIO_H

#include <wchar.h>
#include <stdio.h>
#include <malloc.h>

wchar_t* readName();
wchar_t** readAuthors(int*);
wchar_t* readAuthor();
wchar_t* readGenre();
wchar_t* readPublishing();
wchar_t* readShortDescription();
int readYear();
int readPrice();
float readRating();


//wchar_t* readNameF();
//wchar_t* readAuthorsF();
//wchar_t* readGenreF();
//wchar_t* readPublishingF();
//wchar_t* readShortDescriptionF();
//int readYearF();
//int readPriceF();
//float readRatingF();

#endif //STRUCTS4_DBIO_H
