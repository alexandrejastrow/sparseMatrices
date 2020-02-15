#ifndef _LIST_H_
#define _LIST_H_

typedef struct _cell CELL;
typedef struct _list List;

void addList(List *l);

void subList(List *l);

void freeVetor(List **l);

int sizeList(List *l);

void setSizeList(List *l);

void setHeadList(List *l, CELL *c);

CELL *getHeadList(List *l);

void setList(List *l);

int statusVet(List **l, int pos);

List *getList(List **l, int pos);

List *createList();

int searchList(List *l, int linha, int coluna, int flag);

void freeList(List *l, int flag);

List **createVetor(int size);

void insertList(List *l, CELL *c, int flag);

void deletePosList(List *l1, List *l2, int linha, int coluna);

void printList(List* l);

float takeVal(List *l, int linha, int coluna, int flag);
#endif