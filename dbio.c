//
// Created by hubbyk on 13.07.2020.
//

#include "dbio.h"

wchar_t* readName() {
    wchar_t* name = (wchar_t*)calloc(1, sizeof(wchar_t)), ch;
    int len = 0;
    int letterCount = 0;

    wprintf(L"Enter book name: ");

    while((ch = getwchar()) != L'\n') {
        //на случай, если нельзя цифры в книгах
        if(!isLetter(ch)) {
            if(!isWhiteSpace(ch)) {
                if(!isNumber(ch)) {
                    wprintf(L"В названии допустимы буквы, цифры, пробел \"-\" и \"_\"\n");
                    while ((ch = getwchar()) != L'\n');
                    free(name);
                    return NULL;
                }else {
                    ++letterCount;
                }
            }
                if (!letterCount) {
                    wprintf(L"Должно начинаться с буквы или цифры\n");
                    while ((ch = getwchar()) != L'\n');
                    free(name);
                    return NULL;
                }


            if(isNumber(ch)) ++letterCount;
        }else {
            ++letterCount;
        }
        ++len;
        name = (wchar_t*)realloc(name, len*sizeof(wchar_t));
        name[len - 1] = ch;
    }
    if(len == 0) {
        free(name);
        return NULL;
    }
    if(!letterCount) {
        wprintf(L"Должна быть хотя бы одна буква или цифра\n");
        free(name);
        return NULL;
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
    int letterCount = 0;
    wprintf(L"Имена авторов пишутся через запятую\n");
    wprintf(L"Enter book authors: ");
    *authCount = 0;
    while((ch = getwchar()) != L'\n') {
        if(ch == L',') {
            if(len == 0) {
                while((ch = getwchar()) != L'\n');
                free(*authors);
                return NULL;
            }
            if(letterCount == 0) {
                wprintf(L"Должна быть хотя бы одна буква\n");
                while((ch = getwchar()) != L'\n');
                free(*authors);
                return NULL;
            }
            ++len;
            authors[*authCount] = (wchar_t*)realloc(authors[*authCount], len*sizeof(wchar_t));
            authors[*authCount][len - 1] = L'\0';
            len = 0; letterCount = 0;
            ++*authCount;
            authors = (wchar_t**)realloc(authors, (*authCount+1)*sizeof(wchar_t*));
            authors[*authCount] = (wchar_t*)calloc(1, sizeof(wchar_t));
        }else {
            if(!isLetter(ch)) {
                if(!isWhiteSpace(ch)) {
                    while ((ch = getwchar()) != L'\n');
                    free(*authors);
                    return NULL;
                }
                if(letterCount == 0) {
                    while ((ch = getwchar()) != L'\n');
                    wprintf(L"Должно начинаться с буквы\n");
                    free(*authors);
                    return NULL;
                }
            }else {
                ++letterCount;
            }
            ++len;
            authors[*authCount] = (wchar_t*)realloc(authors[*authCount], len * sizeof(wchar_t));
            authors[*authCount][len - 1] = ch;
        }
    }
    if(len == 0) {
        free(*authors);
        return NULL;
    }
    if(letterCount == 0) {
        wprintf(L"Должна быть хотя бы одна буква\n");
        free(*authors);
        return NULL;
    }
    ++len;
    authors[*authCount] = (wchar_t*)realloc(authors[*authCount], len*sizeof(wchar_t));
    authors[*authCount][len - 1] = L'\0';

    return authors;
}

wchar_t* readAuthor() {
    wchar_t* author = (wchar_t*)calloc(1, sizeof(wchar_t)), ch;
    int len = 0;
    int letterCount = 0;

    while((ch = getwchar()) != L'\n') {
        if(!isLetter(ch)) {
            if(!isWhiteSpace(ch)) {
                while ((ch = getwchar()) != L'\n');
                free(author);
                return NULL;
            }
            if(letterCount == 0) {
                wprintf(L"Должно начинаться с буквы\n");
                while((ch = getwchar()) != L'\n');
                free(author);
                return NULL;
            }
        }else {
            ++letterCount;
        }
        ++len;
        author = (wchar_t*)realloc(author, len*sizeof(wchar_t));
        author[len - 1] = ch;
    }
    if(!len) {
        free(author);
        return NULL;
    }
    if(!letterCount) {
        wprintf(L"Должна быть хотя бы одна буква\n");
        while((ch = getwchar()) != L'\n');
        free(author);
        return NULL;
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
    int letters = 0;

    wprintf(L"Enter book publishing: ");

    while((ch = getwchar()) != L'\n') {
        if(!isLetter(ch)) {
            if (letters == 0) {
                wprintf(L"Должна быть хотя бы одна буква\n");
                while ((ch = getwchar()) != L'\n');
                free(publishing);
                return NULL;
            }
        }else {
            ++letters;
        }
        ++len;
        publishing = (wchar_t*)realloc(publishing, len*sizeof(wchar_t));
        publishing[len - 1] = ch;
    }
    if(len == 0 || letters < 1) {
        free(publishing);
        wprintf(L"Подозрительное издание (хотя бы 1 буква в названии)\n");
        return NULL;
    }
    ++len;
    publishing = (wchar_t*)realloc(publishing, len*sizeof(wchar_t));
    publishing[len - 1] = L'\0';


    return publishing;
}

wchar_t* readShortDescription() {
    wchar_t* description = (wchar_t*)malloc(sizeof(wchar_t)), ch;
    int len = 0;
    int letterCount = 0;

    wprintf(L"Enter short description: ");

    while((ch = getwchar()) != L'\n') {
        if(!isLetter(ch) && !isNumber(ch)) {
            if(letterCount == 0) {
                wprintf(L"Должно начинаться с буквы или цифры\n");
                while((ch = getwchar()) != L'\n');
                free(description);
                return NULL;
            }
        }else {
            ++letterCount;
        }
        ++len;
        description = (wchar_t*)realloc(description, len*sizeof(wchar_t));
        description[len - 1] = ch;
    }
    if(len == 0) {
        free(description);
        return NULL;
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
            while((ch = getwchar()) != L'\n');
            return -1;
        }
    }
    if(year < 1900) {
        wprintf(L"Мы не храним книги старее 1900 года\n");
        return -1;
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
            while((ch = getwchar()) != L'\n');
            return -1;
        }
    }
    if(price < 300) {
        wprintf(L"Слишком низкая цена (<300)\n");
        return -1;
    }

    return price;
}

float readRating() {
    wchar_t ch;
    int readed = 0;
    float rating = (float)0;
    wprintf(L"Enter book rating: ");
    while((ch = getwchar()) != L'\n') {//начинаем читать целую часть
        if(isNumber(ch)) {
            ++readed;
            rating = rating * 10 + (float)((char)ch) - 48;
        }else if(ch == L'.' || ch == L','){
            float pow = (float)0.1;

            while((ch = getwchar()) != L'\n') {//читаем дробную часть
                if(isNumber(ch)) {
                    rating = rating + (float)(((char)ch) - 48) * pow;
                    pow /= 10;
                }else {
                    wprintf(L"ERROR: incorrect input\n");
                    while((ch = getwchar()) != L'\n');
                    return -1;
                }
            }
            break;
        }else {
            wprintf(L"ERROR: incorrect input\n");
            while((ch = getwchar()) != L'\n');
            return -1;
        }
    }
    if(!readed) return -1;

    return rating;
}

int isLetter(wchar_t ch) {
    if(L'a' <= ch && ch <= L'z' || L'A' <= ch && ch <= L'Z' ||
            L'а' <= ch && ch <= L'я' || L'А' <= ch && ch <= L'Я' ||
       ch == L'ё' || ch == L'Ё') return 1;
    return 0;
}

int isWhiteSpace(wchar_t ch) {
    if(ch == L' ' || ch == L'-' || ch == L'_') return 1;
    return 0;
}

int isNumber(wchar_t ch) {
    if(L'0' <= ch && ch <= L'9') return 1;
    return 0;
}