#ifndef _MATRIZ_H_
#define _MATRIZ_H_

typedef struct _matriz MAT;
typedef struct _list List;

MAT *createMat(int size);

void freeMat(MAT *m);

void insertMat(MAT *m, int linha, int coluna, float valor);

void printMat(MAT *m);

MAT *somaMat(MAT *m1, MAT *m2);

void deletePos(MAT *m, int linha, int coluna);

float search(MAT *m, int linha, int coluna, int flag);

#endif