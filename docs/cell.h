#ifndef _CELL_H_
#define _CELL_H_


typedef struct _cell CELL;

void freeCell(CELL *c);

CELL *getNextLinha(CELL *c);

CELL *getNextColuna(CELL *c);

void setLinha(CELL *c, int linha);

void setColuna(CELL *c, int coluna);

void setValor(CELL *c, float valor);

void setProxLinha(CELL *anterior, CELL *proximo);

void setProxColuna(CELL *anterior, CELL *proximo);

int getLinha(CELL *c);

int getColuna(CELL *c);

float getVal(CELL *c);

CELL *createCell(int linha, int coluna, float valor);

void printCell(CELL *c);

int proxCell(CELL *c, int flag);
#endif