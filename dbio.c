//
// Created by hubbyk on 13.07.2020.
//

#include "dbio.h"

wchar_t* readName() {
    wchar_t* name = (wchar_t*)calloc(1, sizeof(wchar_t)), ch;
    int len = 0;

    wprintf(L"Enter book name: ");

    while((ch = getwchar()) != L'\n') {
        ++len;
        name = (wchar_t*)realloc(name, len*sizeof(wchar_t));
        name[len - 1] = ch;
    }
    ++len;
    name = (wchar_t*)realloc(name, len*sizeof(wchar_t));
    name[len - 1] = L'\0';

    return name;
}

wchar_t** readAuthors(int* authCount) {
    wchar_t** authors = (wchar_t**)malloc(sizeof(wchar_t*)), ch;
    authors[*authCount] = (wchar_t*)malloc(sizeof(wchar_t));
    int len = 0;

    wprintf(L"Enter book authors: ");
    *authCount = 0;
    while((ch = getwchar()) != L'\n') {
        if(ch == L',') {
            ++len;
            authors[*authCount] = (wchar_t*)realloc(authors[*authCount], len*sizeof(wchar_t));
            authors[*authCount][len - 1] = L'\0';
            len = 0;
            ++*authCount;
            authors = (wchar_t**)realloc(authors, (*authCount+1)*sizeof(wchar_t*));
            authors[*authCount] = (wchar_t*)calloc(1, sizeof(wchar_t));
        }else {
            ++len;
            authors[*authCount] = (wchar_t*)realloc(authors[*authCount], len * sizeof(wchar_t));
            authors[*authCount][len - 1] = ch;
        }
    }
    ++len;
    authors[*authCount] = (wchar_t*)realloc(authors[*authCount], len*sizeof(wchar_t));
    authors[*authCount][len - 1] = L'\0';

    return authors;
}

wchar_t* readAuthor() {
    wchar_t* author = (wchar_t*)calloc(1, sizeof(wchar_t)), ch;
    int len = 0;

    while((ch = getwchar()) != L'\n') {
        ++len;
        author = (wchar_t*)realloc(author, len*sizeof(wchar_t));
        author[len - 1] = ch;
    }
    ++len;
    author = (wchar_t*)realloc(author, len*sizeof(wchar_t));
    author[len - 1] = L'\0';

    return author;
}

wchar_t* readGenre() {
    wchar_t* genre = (wchar_t*)malloc(sizeof(wchar_t)), ch;
    int len = 0;

    wprintf(L"Enter book genre: ");

    while((ch = getwchar()) != L'\n') {
        ++len;
        genre = (wchar_t*)realloc(genre, len*sizeof(wchar_t));
        genre[len - 1] = ch;
    }
    ++len;
    genre = (wchar_t*)realloc(genre, len*sizeof(wchar_t));
    genre[len - 1] = L'\0';

    return genre;
}

wchar_t* readPublishing() {
    wchar_t* publishing = (wchar_t*)malloc(sizeof(wchar_t)), ch;
    int len = 0;

    wprintf(L"Enter book publishing: ");

    while((ch = getwchar()) != L'\n') {
        ++len;
        publishing = (wchar_t*)realloc(publishing, len*sizeof(wchar_t));
        publishing[len - 1] = ch;
    }
    ++len;
    publishing = (wchar_t*)realloc(publishing, len*sizeof(wchar_t));
    publishing[len - 1] = L'\0';

    return publishing;
}

wchar_t* readShortDescription() {
    wchar_t* description = (wchar_t*)malloc(sizeof(wchar_t)), ch;
    int len = 0;

    wprintf(L"Enter short description: ");

    while((ch = getwchar()) != L'\n') {
        ++len;
        description = (wchar_t*)realloc(description, len*sizeof(wchar_t));
        description[len - 1] = ch;
    }
    ++len;
    description = (wchar_t*)realloc(description, len*sizeof(wchar_t));
    description[len - 1] = L'\0';

    return description;
}

int readYear() {
    int year = 0;
    wchar_t ch;

    wprintf(L"Enter book year: ");

    while((ch = getwchar()) != L'\n') {
        if(L'0' <= ch && ch <= L'9') {
            year = year * 10 + (char)ch - 48;
        }else {
            wprintf(L"ERROR: incorrect input\n");
            return -1;
        }
    }

    return year;
}

int readPrice() {
    int price = 0;
    wchar_t ch;

    wprintf(L"Enter book price: ");

    while((ch = getwchar()) != L'\n') {
        if(L'0' <= ch && ch <= L'9') {
            price = price * 10 + (char)ch - 48;
        }else {
            wprintf(L"ERROR: incorrect input\n");
            return -1;
        }
    }

    return price;
}

float readRating() {
    wchar_t ch;
    float rating = (float)0;
    wprintf(L"Enter book rating: ");
    while((ch = getwchar()) != L'\n') {//начинаем читать целую часть
        if(L'0' <= ch && ch <= L'9') {
            rating = rating * 10 + (float)((char)ch) - 48;
        }else if(ch == L'.'){
            float pow = (float)0.1;

            while((ch = getwchar()) != L'\n') {//читаем дробную часть
                if(L'0' <= ch && ch <= L'9') {
                    rating = rating + (float)(((char)ch) - 48) * pow;
                    pow /= 10;
                }else {
                    wprintf(L"ERROR: incorrect input\n");
                    return -1;
                }
            }
            break;
        }else {
            wprintf(L"ERROR: incorrect input\n");
            return -1;
        }
    }

    return rating;
}