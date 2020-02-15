#include <stdio.h>
#include "arq.h"

FILE *open_arq(char *n){

	FILE *novo = fopen(n, "r");

	return novo;
}

void pega_linha(FILE *n, int *l, int *co, float *v){


	float val;
	int  cont = 0, pos = 0, flag = 0, lin, col;
	char temp[10], c;

	do{
		c = fgetc(n);
		
		if(feof(n) && flag == 0){
			*l = -1;
			*co = -1;
			return;
		}
		flag = 1;
		if(c == ';'){
			switch(cont){
				case 0:
					temp[pos] = 0;
					sscanf(temp, "%d", &lin);	
					pos = 0;
					cont++;
					break;
				case 1:
					temp[pos] = 0;
					sscanf(temp, "%d", &col);
					pos = 0;
					cont++;
					break;
			}

		}else if(c == '\n'){

			temp[pos] = 0;
			sscanf(temp, "%f", &val);
			*l = lin;
			*co = col;
			*v = val;
			return;
		}else{
			temp[pos] = c;
			pos++;
			}
		}while(!feof(n));
		temp[pos] = 0;
		sscanf(temp, "%f", &val);
		*l = lin;
		*co = col;
		*v = val;
		return;
}
int pega_topo(FILE *n){
	
	char temp[20], c;
	int val, cont =0;
	while(c != '\n'){
		c = fgetc(n);
		temp[cont] = c;	
		cont++;
	}
	temp[cont] = 0;
	sscanf(temp, "%d", &val);
	return val;
}
void fecha_arq(FILE *f){
	fclose(f);
}