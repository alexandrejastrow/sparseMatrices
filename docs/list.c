#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "cell.h"

/*estrutura da lista*/
struct _list{
	int size;
	struct _cell *inicio;
};
/*incrementa tamanho da lista*/
void addList(List *l){
	if(l){
		l->size++;
	}
}
/*decrementa tamanho da lista*/
void subList(List *l){
	if(l){
		l->size--;
	}
}
/*destroi vetor de ponteiros para lista*/
void freeVetor(List **l){
	free(l);
}
/*retorna tamanho da lista*/
int getsizeList(List *l){
	if(l){
		return l->size;
	}
	return 0;
}
/*seta valor da lista para 0*/
void setSizeList(List *l){
	if(l){
		l->size = 0;
	}
}
/*insere a primeira celula da lista*/
void setHeadList(List *l, CELL *c){
	if(l){
		l->inicio = c;
	}
}
/*retorna o topo da lista*/
CELL *getHeadList(List *l){
	if(l){
		return l->inicio;
	}
	return NULL;
}
/*pontero pra lista recebe NULL*/
void setList(List *l){
	l = NULL;
}
/*retorna 1 se o vetor na posicao for diferente de NULL*/
int statusVet(List **l, int pos){
	if(l[pos]){
		return 1;
	}
	return 0;
}
/*retorna umponteiro pra lista do vetor de listas*/
List *getList(List **l, int pos){
	return l[pos];
}
/*cria lista*/
List *createList(){

	List *new = (List*)malloc(sizeof(List));

	setHeadList(new, NULL);
	setSizeList(new);

	return new;
}
/*funcao que faz busca pela linha ou coluna e retorna 1 se a celula existir*/
int searchList(List *l, int linha, int coluna, int flag){
	
	CELL *c = getHeadList(l);
	while(c){
		if(getLinha(c) == linha && getColuna(c) == coluna){
			return 1;
		}
		if(flag){
			c = getNextLinha(c);
		}else{
			c = getNextColuna(c);
		}
	}
	return 0;
}
/*limpa a lista pela linha ou pela coluna*/
void freeList(List *l, int flag){

	CELL *anterior, *c = getHeadList(l);
	while(c){
		anterior = c;
		if(flag){
			c = getNextLinha(c);
		}else{
			c = getNextColuna(c);
		}
		freeCell(anterior);
	}
	free(l);
}
/*cria vetor de ponteiros para lista*/
List **createVetor(int size){

	List **vetorList = (List**)malloc(sizeof(List*)*size);

	for(int i = 0; i<size; i++){
		setList(vetorList[i]);
	}
	return vetorList;
}
/*funcao que insere a celula pela linha*/	
void insertLinha(List *l, CELL *c){

	if(getVal(c) != 0){
		if(!getsizeList(l)){
			setHeadList(l, c);
			addList(l);
		}else{

			CELL *anterior = NULL, *atual = getHeadList(l);
			while(proxCell(atual, 1) && getColuna(atual) < getColuna(c)){
				anterior = atual;
				atual = getNextLinha(atual);
			}

			if(anterior == NULL && getColuna(atual) < getColuna(c)){
				setProxLinha(atual, c);
			
			}else if(anterior == NULL && getColuna(atual) > getColuna(c)){
				setHeadList(l, c);
				setProxLinha(c, atual);
			}else if(getColuna(atual) == getColuna(c)){
				setValor(atual, getVal(c));
				subList(l);
			}else if(anterior != NULL && getColuna(atual) < getColuna(c)){
				anterior = getNextLinha(atual);
				setProxLinha(atual, c);
				setProxLinha(c, anterior);

			}else if(anterior != NULL && getColuna(atual) > getColuna(c)){
				setProxLinha(anterior, c);
				setProxLinha(c, atual);
			}else{
				setProxLinha(atual, c);
			}
			addList(l);
		}
	}	
}
/*funcao que insere a celula pela coluna*/
void insertColuna(List *l, CELL *c){

	if(getVal(c) != 0){
		if(!getsizeList(l)){
			setHeadList(l, c);
			addList(l);
		}else{

			CELL *anterior = NULL, *atual = getHeadList(l);
			while(proxCell(atual, 0) && getLinha(atual) < getLinha(c)){
				anterior = atual;
				atual = getNextColuna(atual);
			}

			if(anterior == NULL && getLinha(atual) < getLinha(c)){
				setProxColuna(atual, c);
			
			}else if(anterior == NULL && getLinha(atual) > getLinha(c)){
				setHeadList(l, c);
				setProxColuna(c, atual);
			}else if(getLinha(atual) == getLinha(c)){
				setValor(atual, getVal(c));
				subList(l);
			}else if(anterior != NULL && getLinha(atual) < getLinha(c)){
				anterior = getNextColuna(atual);
				setProxColuna(atual, c);
				setProxColuna(c, anterior);

			}else if(anterior != NULL && getLinha(atual) > getLinha(c)){

				setProxColuna(anterior, c);
				setProxColuna(c, atual);
			}else{
				setProxColuna(atual, c);
			}
			addList(l);
		}
	}
}
/*funcao que encaminha para as funcoes de insercao na linha e coluna*/
void insertList(List *l, CELL *c, int flag){

	if(flag){
		insertLinha(l, c);
	}else{
		insertColuna(l, c);
	}
}
/*deleta uma celula que*/
void deletePosList(List *l1, List *l2, int linha, int coluna){

	CELL *anterior_linha =NULL;
	CELL *anterior_coluna = NULL;
	CELL *atual_linha = getHeadList(l1);
	CELL *atual_coluna = getHeadList(l2);
	/*loop que percorre lista da linha ate chegar na posicao com a variavel atual_linha*/
	while(atual_linha){
		if(getLinha(atual_linha) == linha && getColuna(atual_linha) == coluna){
			/*loop que percorre lista da coluna ate chegar na posicao com a variavel atual_coluna*/
			while(atual_linha){
				if(getLinha(atual_coluna) == linha && getColuna(atual_coluna) == coluna){
						
						if(!anterior_linha && !proxCell(atual_linha,1)){
							setHeadList(l1, NULL);
							
							}else if(!anterior_linha && proxCell(atual_linha,1)){
								setHeadList(l1, getNextLinha(atual_linha));
								}else{
									setProxLinha(anterior_linha, getNextLinha(atual_linha));

								}

						if(!anterior_coluna && !proxCell(atual_coluna, 0)){
							setHeadList(l2, NULL);

							}else if(!anterior_coluna && proxCell(atual_coluna,0)){
								setHeadList(l2, getNextColuna(atual_coluna));
								
								}else{
									setProxColuna(anterior_coluna, getNextColuna(atual_coluna));
								}

						if(atual_linha == atual_coluna){
							freeCell(atual_linha);	
						}
						return;
						return;
				}
				anterior_coluna = atual_coluna;
				atual_coluna = getNextColuna(atual_coluna);
			}			
		}
		anterior_linha = atual_linha;
		atual_linha = getNextLinha(atual_linha);
	}

}
/*funcao que printa uma lista*/
void printList(List* l){

	CELL *c = getHeadList(l);
	while(c){
		printCell(c);
		c = getNextLinha(c);
	}
	
}
/*funcao que retorna o valor de uma celula da lista*/
float takeVal(List *l, int linha, int coluna, int flag){

	CELL *atual = getHeadList(l);

	while(atual){
		if(getLinha(atual) == linha && getColuna(atual) == coluna){
			return getVal(atual);
		}
		if(flag){
			atual = getNextLinha(atual);
		}else{
			atual = getNextColuna(atual);
		}
		
	}
	return 0.0;
}