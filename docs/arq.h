#ifndef _ARQ_H_
#define _ARQ_H_

FILE *open_arq(char *n);

void fecha_arq(FILE *f);

void pega_linha(FILE *n, int *l, int *co, float *v);

int pega_topo(FILE *n);
#endif