#include <stdlib.h>
#include <stdio.h>
#include "cell.h"

/*estrutura da celula*/
struct _cell{
	int linha, coluna;
	float valor;
	struct _cell *proxLinha;
	struct _cell *proxColuna;
};

/*funcao que destri a celula*/
void freeCell(CELL *c){
	free(c);
}
/*funcao que retorna o endereco da proxima celula na linha*/
CELL *getNextLinha(CELL *c){
	if(c){
		return c->proxLinha;
	}
	return c;
}
/*funcao que retorna o endereco da proxima celula na coluna*/
CELL *getNextColuna(CELL *c){
	if(c){
		return c->proxColuna;
	}
	return c;
}
/*insere valor da linha na celula*/
void setLinha(CELL *c, int linha){
	if(c){
		c->linha = linha;	
	}
}
/*insere valor da coluna na celula*/
void setColuna(CELL *c, int coluna){
	if(c){
		c->coluna = coluna;	
	}
}
/*insere o valor da celula*/
void setValor(CELL *c, float valor){
	if(c){
		c->valor = valor;
	}
}
/*funcao onde a celula anterior aponta para a proxima da linha*/
void setProxLinha(CELL *anterior, CELL *proximo){
	if(anterior){
		anterior->proxLinha = proximo;
	}
}
/*funcao onde a celula anterior aponta para a proxima da coluna*/
void setProxColuna(CELL *anterior, CELL *proximo){
	if(anterior){
		anterior->proxColuna = proximo;
	}
}
/*retorna valor da linha se diferente de NULL*/
int getLinha(CELL *c){
	if(c){
		return c->linha;
	}
	return -1;
}
/*retorna valor da coluna se diferente de NULL*/
int getColuna(CELL *c){
	if(c){
		return c->coluna;
	}
	return -1;
}
/*retorna valor da celula*/
float getVal(CELL *c){
	if(c){
		return c->valor;
	}
	return 0.0;
}
/*funcao cria celula*/
CELL *createCell(int linha, int coluna, float valor){

	CELL *new = (CELL*)malloc(sizeof(CELL));

	if(!new) return NULL;

	setLinha(new, linha);
	setColuna(new, coluna);
	setValor(new, valor);
	setProxLinha(new, NULL);
	setProxColuna(new, NULL);
	return new;
}
/*funcao que printa na tela as informacoes da celula*/
void printCell(CELL *c){
	if(c){
		printf("%d;%d;%g\n", getLinha(c)+1, getColuna(c)+1, getVal(c));		
	}
}
/*retorna 1 se o proximo da linha ou coluna for diferente de NULL*/
int proxCell(CELL *c, int flag){

	if(flag){
		if(c->proxLinha == NULL) return 0;

	}else{
		if(c->proxColuna == NULL) return 0;
	}
	return 1;
}