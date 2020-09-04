//
// Created by hubbyk on 12.06.2020.
//
#include "dbtree.h"

BOOK* newBook(int authCount, int year, int price, float rating, wchar_t* name, wchar_t** authors, wchar_t* genre, wchar_t* publishing, wchar_t* description) {
    BOOK* book = (BOOK*)malloc(sizeof(BOOK));

    wchar_t* tmp = *(authors + 0);

    book->authCount = authCount;
    book->year = year;
    book->price = price;
    book->rating = rating;
    book->name = name;
    book->authors = sortAuth(authors, authCount);
    book->genre = genre;
    book->publishing = publishing;
    book->description = description;

    return book;
}
int bookCompare(BOOK* book1, BOOK* book2) {
    if (!wcscmp(book1->name, book2->name) &&
        !wcscmp(book1->genre, book2->genre) &&
        authCompare(book1, book2) &&
        !wcscmp(book1->description, book2->description) &&
        !wcscmp(book1->publishing, book2->publishing) &&
        book1->year == book2->year && book1->price == book2->price &&
        (book1->rating - book2->rating) < 0.1 && (book1->rating - book2->rating) > -0.1) return 1;
    return 0;
}

BOOK* readBookFromFile(FILE* inputFile) {
    wchar_t* name,** authors,* genre,* publishing,* description, wch = 1;
    int year = 0, price = 0, len = 0;
    float rating = (float)0.0;

    name = (wchar_t*)malloc(sizeof(wchar_t));
    authors = (wchar_t**)malloc(sizeof(wchar_t*));
    genre = (wchar_t*)malloc(sizeof(wchar_t));
    publishing = (wchar_t*)malloc(sizeof(wchar_t));
    description = (wchar_t*)malloc(sizeof(wchar_t));

    //чтение имени
    while(wch != L'\"' && wch) wch = fgetwc(inputFile);
    wch = fgetwc(inputFile);
    while(wch != L'\"') {
        ++len;
        name = (wchar_t*)realloc(name, len*sizeof(wchar_t));
        name[len - 1] = wch;
        wch = fgetwc(inputFile);
    }
    ++len;
    name = (wchar_t*)realloc(name, len*sizeof(wchar_t));
    name[len - 1] = L'\0'; len = 0;
    wch = fgetwc(inputFile);

    //чтение авторов
    //TODO
    int authCount = 0;
    *authors = (wchar_t*)malloc(sizeof(wchar_t));
    while(wch != L'\"') wch = fgetwc(inputFile);
    wch = fgetwc(inputFile);
    while(wch != L'\"') {
        if(wch == L',') {
            ++len;
            authors[authCount] = (wchar_t*)realloc(authors[authCount], len*sizeof(wchar_t));
            authors[authCount][len - 1] = L'\0'; len = 0;

            ++authCount;
            authors = (wchar_t**)realloc(authors, (authCount+1)*sizeof(wchar_t*));
            authors[authCount] = (wchar_t*)calloc(1, sizeof(wchar_t));
            wch = fgetwc(inputFile);
        }else {
            ++len;
            authors[authCount] = (wchar_t*)realloc(authors[authCount], len*sizeof(wchar_t));
            authors[authCount][len - 1] = wch;
            wch = fgetwc(inputFile);
        }
    }
    ++len;
    authors[authCount] = (wchar_t*)realloc(authors[authCount], len*sizeof(wchar_t));
    authors[authCount][len - 1] = L'\0'; len = 0;
    wch = fgetwc(inputFile);

    //чтение года
    while(wch != L'\"') wch = fgetwc(inputFile);
    wch = fgetwc(inputFile);
    while(wch != L'\"') {
        year = year * 10 + (char)wch - 48;
        wch = fgetwc(inputFile);
    }
    wch = fgetwc(inputFile);

    //чтение жанра
    while(wch != L'\"') wch = fgetwc(inputFile);
    wch = fgetwc(inputFile);
    while(wch != L'\"') {
        ++len;
        genre = (wchar_t*)realloc(genre, len*sizeof(wchar_t));
        genre[len - 1] = wch;
        wch = fgetwc(inputFile);
    }
    ++len;
    genre = (wchar_t*)realloc(genre, len*sizeof(wchar_t));
    genre[len - 1] = L'\0'; len = 0;
    wch = fgetwc(inputFile);

    //чтение издательства
    while(wch != L'\"') wch = fgetwc(inputFile);
    wch = fgetwc(inputFile);
    while(wch != L'\"') {
        ++len;
        publishing = (wchar_t*)realloc(publishing, len*sizeof(wchar_t));
        publishing[len - 1] = wch;
        wch = fgetwc(inputFile);
    }
    ++len;
    publishing = (wchar_t*)realloc(publishing, len*sizeof(wchar_t));
    publishing[len - 1] = L'\0'; len = 0;
    wch = fgetwc(inputFile);

    //чтение цены
    while(wch != L'\"') wch = fgetwc(inputFile);
    wch = fgetwc(inputFile);
    while(wch != L'\"') {
        price = price * 10 + (char)wch - 48;
        wch = fgetwc(inputFile);
    }
    wch = fgetwc(inputFile);

    //чтение рейтинга
    while(wch != L'\"') wch = fgetwc(inputFile);
    wch = fgetwc(inputFile);
    while(wch != L'\"') {//начинаем читать целую часть
        if(L'0' <= wch && wch <= L'9') {
            rating = rating * 10 + (float)((char)wch) - 48;
            wch = fgetwc(inputFile);
        }else if(wch == L',' || wch == L'.'){
            wch = fgetwc(inputFile);
            float pow = (float)0.1;
            while(wch != '\"') {//читаем дробную часть
                rating = rating + (float)(((char)wch) - 48) * pow;
                pow /= 10;
                wch = fgetwc(inputFile);
            }
            break;
        }
    }
    wch = fgetwc(inputFile);

    //чтение описания
    while(wch != L'\"') wch = fgetwc(inputFile);
    wch = fgetwc(inputFile);
    while(wch != L'\"') {
        ++len;
        description = (wchar_t*)realloc(description, len*sizeof(wchar_t));
        description[len - 1] = wch;
        wch = fgetwc(inputFile);
    }
    ++len;
    description = (wchar_t*)realloc(description, len*sizeof(wchar_t));
    description[len - 1] = L'\0';

    while(wch != L'-') wch = fgetwc(inputFile);
    while(wch != L'\n' && !feof(inputFile)) wch = fgetwc(inputFile);
    wch = fgetwc(inputFile);

    return newBook(authCount, year, price, rating, name, authors, genre, publishing, description);
}
BOOK* readBook() {
    wchar_t* name,** authors,* genre,* publishing,* description;
    int price = 0, year = 0, authCount = 0;
    float rating = 0;

    wprintf(L"==========================\n");

    name = readName();
    if(!name) return NULL;
    authors = readAuthors(&authCount);
    if(!authors) return NULL;
    genre = readGenre();
    if(!whatGenre(genre)) return NULL;
    publishing = readPublishing();
    if(!publishing) return NULL;
    price = readPrice();
    if(price < 0) return NULL;
    year = readYear();
    if(year < 0) return NULL;
    rating = readRating();
    if(rating < 0) return NULL;
    description = readShortDescription();

    return newBook(authCount, year, price, rating, name, authors, genre, publishing, description);
}

int authCompare(BOOK* book1, BOOK* book2) {
    int res;
    for(int i = 0; i < book1->authCount; i++) {
        res = wcscmp(book1->authors[i], book2->authors[i]);
        if(res) return res;
    }
    return 0;
}
wchar_t** sortAuth(wchar_t** authors, int authCount) {//TODO
    wchar_t* tmp = NULL;
    for(int i = 0; i <= authCount; i++) {
        for(int j = 1; j <= authCount - i; j++) {
            if(wcscmp(authors[j], authors[j - 1]) < 0) {
                tmp = authors[j];
                authors[j] = authors[j - 1];
                authors[j - 1] = tmp;
            }
        }
    }
    return authors;
}
int isAuthor(BOOK* book, wchar_t* author) {
    for(int i = 0; i < book->authCount + 1; i++) {
        if(!wcscmp(book->authors[i], author)) return 1;
    }
    return 0;
}

int ratingsCompare(float rate1, float rate2) {
    if((rate1 - rate2) > 0.1) {
        return 1;
    }else if((rate1 - rate2) < -0.1) {
        return -1;
    }else {
        return 0;
    }
}
int whatGenre(wchar_t* str) {
    if(!wcscmp(str, genre_horror_en) || !wcscmp(str, genre_horror_ru)) return HORROR;
    if(!wcscmp(str, genre_thriller_en) || !wcscmp(str, genre_thriller_ru)) return THRILLER;
    if(!wcscmp(str, genre_gothic_en) || !wcscmp(str, genre_gothic_ru)) return GOTHIC;
    return 0;
}
int genreCompare(wchar_t* str, wchar_t* str1) {
    return (whatGenre(str) == whatGenre(str1));
}

void printBook(BOOK* book) {
    wprintf(L"-----------------------------------\n\
\"%ls\"    \"", book->name);
    for(int i = 0; i < book->authCount + 1; i++) {
        if(i) wprintf(L",");
        wchar_t* tmp = book->authors[i];
        wprintf(L"%ls", tmp);
    }
    wprintf(L"\"  \"%d\"  \"%ls\"  \"%ls\"  \"%d\"  \"%f\"\n\"%ls\"\n\
-----------------------------------\n", book->year, book->genre, book->publishing,
             book->price, book->rating, book->description);
}
void writeBook(BOOK* book, FILE* inputFile) {
    fwprintf(inputFile, L"-----------------------------------\n\
\"%ls\"    \"", book->name);
    for(int i = 0; i < book->authCount + 1; i++) {
        if(i) fwprintf(inputFile, L",");
        fwprintf(inputFile, L"%ls", book->authors[i]);
    }
    fwprintf(inputFile, L"\"  \"%d\"  \"%ls\"  \"%ls\"  \"%d\"  \"%f\"\n\"%ls\"\n\
-----------------------------------\n", book->year, book->genre, book->publishing,
            book->price, book->rating, book->description);
}

struct treeNode* newRecord(BOOK* newBook) {
    struct treeNode* rec = (struct treeNode*)malloc(sizeof(struct treeNode));

    rec->book = newBook;
    rec->left = NULL;
    rec->right = NULL;
    rec->nextBook = NULL;
    rec->height = 1;

    return rec;
}

unsigned char height(struct treeNode* p) {
    return p?p->height:0;
}
int balanceFactor(struct treeNode* p) {
    return height(p->right)-height(p->left);
}
void fixHeight(struct treeNode* p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

struct treeNode* rotateRight(struct treeNode* p) {
    struct treeNode* q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}
struct treeNode* rotateLeft(struct treeNode* q) {
    struct treeNode* p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

struct treeNode* balance(struct treeNode* p) {
    fixHeight(p);
    if(balanceFactor(p)==2) {
        if(balanceFactor(p->right) < 0) p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if(balanceFactor(p)==-2) {
        if(balanceFactor(p->left) > 0) p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p; // балансировка не нужна
}
struct treeNode* findMin(struct treeNode* p) {
    return p->left ? findMin(p->left) : p;
}
struct treeNode* removeMin(struct treeNode* p) {
    if( p->left==0 )
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

struct treeNode* insertN(struct treeNode* p, BOOK* newBook) {
    if( !p ) return newRecord(newBook);
    if(wcscmp(newBook->name, p->book->name) > 0) {
        p->left = insertN(p->left, newBook);
    }else if(wcscmp(newBook->name, p->book->name) < 0) {
        p->right = insertN(p->right, newBook);
    }else {
        struct treeNode* tmp = p;
        while(tmp->nextBook) tmp = tmp->nextBook;
        tmp->nextBook = newRecord(newBook);
        return p;
    }
    return balance(p);
}
struct treeNode* insertP(struct treeNode* p, BOOK* newBook) {
    if( !p ) return newRecord(newBook);
    if(newBook->price < p->book->price) {
        p->left = insertP(p->left, newBook);
    }else if(newBook->price > p->book->price) {
        p->right = insertP(p->right, newBook);
    }else {
        struct treeNode* tmp = p;
        while(tmp->nextBook != NULL) tmp = tmp->nextBook;
        tmp->nextBook = newRecord(newBook);
        return p;
    }
    return balance(p);
}
struct treeNode* insertY(struct treeNode* p, BOOK* newBook) {
    if( !p ) return newRecord(newBook);
    if(newBook->year < p->book->year) {
        p->left = insertY(p->left, newBook);
    }else if(newBook->year > p->book->year) {
        p->right = insertY(p->right, newBook);
    }else {
        struct treeNode* tmp = p;
        while(tmp->nextBook != NULL) tmp = tmp->nextBook;
        tmp->nextBook = newRecord(newBook);
        return p;
    }
    return balance(p);
}
struct treeNode* insertPU(struct treeNode* p, BOOK* newBook) {
    if( !p ) return newRecord(newBook);
    if(wcscmp(newBook->publishing, p->book->publishing) < 0) {
        p->left = insertPU(p->left, newBook);
    }else if(wcscmp(newBook->publishing, p->book->publishing) > 0) {
        p->right = insertPU(p->right, newBook);
    }else {
        struct treeNode* tmp = p;
        while(tmp->nextBook) tmp = tmp->nextBook;
        tmp->nextBook = newRecord(newBook);
        return p;
    }
    return balance(p);
}
struct treeNode* insertA(struct treeNode* p, BOOK* newBook) {
    if( !p ) return newRecord(newBook);
    if(authCompare(newBook, p->book) < 0) {
        p->left = insertA(p->left, newBook);
    }else if(authCompare(newBook, p->book) > 0) {
        p->right = insertA(p->right, newBook);
    }else {
        struct treeNode* tmp = p;
        while(tmp->nextBook) tmp = tmp->nextBook;
        tmp->nextBook = newRecord(newBook);
        return p;
    }
    return balance(p);
}
struct treeNode* insertR(struct treeNode* p, BOOK* newBook) {
    if( !p ) return newRecord(newBook);
    if(ratingsCompare(newBook->rating, p->book->rating) < 0) {
        p->left = insertR(p->left, newBook);
    }else if(ratingsCompare(newBook->rating, p->book->rating) > 0) {
        p->right = insertR(p->right, newBook);
    }else {
        struct treeNode* tmp = p;
        while(tmp->nextBook) tmp = tmp->nextBook;
        tmp->nextBook = newRecord(newBook);
        return p;
    }
    return balance(p);
}

struct treeNode* removeFromTree(struct treeNode* p, BOOK* newBook) {
    if( !p ) return NULL;
    if(wcscmp(newBook->name, p->book->name) > 0)
        p->left = removeFromTree(p->left, newBook);
    else if(wcscmp(newBook->name, p->book->name) < 0)
        p->right = removeFromTree(p->right, newBook);
    else {
        if(p->nextBook) {
            while(p->nextBook) {
                if (bookCompare(p->book, newBook)) {
                    p->nextBook->right = p->right;
                    p->nextBook->left = p->left;
                    p = p->nextBook;
                }
                p = p->nextBook;
            }
        }else {
            struct treeNode *q = p->left;
            struct treeNode *r = p->right;
            free(p);
            if (!r) return q;
            struct treeNode *min = findMin(r);
            min->right = removeMin(r);
            min->left = q;
            return balance(min);
        }
    }

    return balance(p);
}

struct treeNode* searchByName(struct treeNode* root, wchar_t* name) {
    if(!root) return NULL;
    if(wcscmp(root->book->name, name) > 0) {
        return searchByName(root->left, name);
    }else if(wcscmp(root->book->name, name) < 0) {
        return searchByName(root->right, name);
    }else {
        return root;
    }
}
struct treeNode* searchByPublishing(struct treeNode* root, wchar_t* publishing) {
    if(!root) return NULL;
    if(wcscmp(root->book->name, publishing) < 0) {
        return searchByPublishing(root->left, publishing);
    }else if(wcscmp(root->book->name, publishing) > 0) {
        return searchByPublishing(root->right, publishing);
    }else {
        return root;
    }
}
struct treeNode* searchByAuthor(struct treeNode* root, wchar_t* author) {
    if(root->right != NULL)searchByAuthor(root->right, author);
    if(root != NULL) {
        if(isAuthor(root->book, author))printBook(root->book);
        if(root->nextBook) {
            struct treeNode *tmp = root->nextBook;
            while(tmp) {
                if(isAuthor(root->book, author))printBook(tmp->book);
                tmp = tmp->nextBook;
            }
        }
    }
    if(root->left != NULL) searchByAuthor(root->left, author);
}
struct treeNode* searchByPrice(struct treeNode* root, int price) {
    if(!root) return NULL;
    if(root->book->price > price) {
        return searchByPrice(root->left, price);
    }else if(root->book->price < price) {
        return searchByPrice(root->right, price);
    }else {
        return root;
    }
}
struct treeNode* searchByYear(struct treeNode* root, int year) {
    if(!root) return NULL;
    if(root->book->year > year) {
        return searchByYear(root->left, year);
    }else if(root->book->year < year) {
        return searchByYear(root->right, year);
    }else {
        return root;
    }
}
struct treeNode* searchByRating(struct treeNode* root, float rating) {
    if(!root) return NULL;
    if(ratingsCompare(rating, root->book->rating) < 0) {
        return searchByRating(root->left, rating);
    }else if(ratingsCompare(rating, root->book->rating) > 0) {
        return searchByRating(root->right, rating);
    }else {
        return root;
    }
}

void printTree(struct treeNode* root) {
    if(!root) return;
    if(root->right != NULL)printTree(root->right);
    if(root != NULL) {
        printBook(root->book);
        if(root->nextBook) {
            struct treeNode *tmp = root->nextBook;
            while(tmp) {
                printBook(tmp->book);
                tmp = tmp->nextBook;
            }
        }
    }
    if(root->left != NULL) printTree(root->left);
}
void saveToFile(struct treeNode* root, FILE* inputFile) {
    if(root->right != NULL)saveToFile(root->right, inputFile);
    if(root != NULL) {
        writeBook(root->book, inputFile);
        if(root->nextBook) {
            struct treeNode *tmp = root->nextBook;
            while(tmp) {
                writeBook(tmp->book, inputFile);
                tmp = tmp->nextBook;
            }
        }
    }
    if(root->left != NULL)saveToFile(root->left, inputFile);
}
void readFromFile(struct treeNode** root, FILE* inputFile) {
    BOOK* book;
    while(!feof(inputFile)) {
        book = readBookFromFile(inputFile);
        *root = insertN(*root, book);
    }
}