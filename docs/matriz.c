#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"
#include "list.h"
#include "cell.h"
/*estrutura da matriz*/
struct _matriz{
	int size;
	struct _list **vetorLinha;
	struct _list **vetorColuna;
};
/*insere a dimencao da matriz*/
void setSizeMat(MAT *m, int size){
	m->size = size;
}
/*retorna o tamanho da matriz*/
int getSizeMat(MAT *m){
	return m->size;
}
/*funcao que cria um vetor de ponteiros para lista*/
int setVetor(MAT *m, int size, int flag){

	List **l = createVetor(size);
	if(!l) return 0;
	
	if(flag){
		m->vetorLinha = l;
	}else{
		m->vetorColuna = l;
	}
	
	return 1;
}
/*funcao que cria a matriz*/
MAT *createMat(int size){

	MAT *new = (MAT*)malloc(sizeof(MAT));
	if(!new) return NULL;

	if(!setVetor(new, size, 1)){
		freeMat(new);
		return NULL;
	}
	if(!setVetor(new, size, 0)){
		freeMat(new);
		return NULL;	
	}
	setSizeMat(new, size);
	return new;
}
/*funcao que destroi a matriz*/
void freeMat(MAT *m){

	for(int i = 0; i< getSizeMat(m); i++){
		if(m->vetorLinha[i]){
			freeList(getList(m->vetorLinha, i), i);
		}
	}
	freeVetor(m->vetorLinha);
	freeVetor(m->vetorColuna);
	free(m);
}
/*cria e insere uma celula na matriz na posicao de linha e coluna*/
void insertMat(MAT *m, int linha, int coluna, float valor){

	CELL *c = createCell(linha, coluna, valor);
	if(valor != 0){
		if(getList(m->vetorLinha, linha) == NULL){
			m->vetorLinha[linha] = createList();
		}
		if(getList(m->vetorColuna,coluna) == NULL){
			m->vetorColuna[coluna] = createList();
		}
		insertList(getList(m->vetorLinha, linha), c, 1);
		insertList(getList(m->vetorColuna,coluna), c, 0);
	}else{
		deletePos(m, linha, coluna);
	}	
}
/*funcao que imprime a matriz*/
void printMat(MAT *m){

	printf("%d\n", getSizeMat(m));
	for(int i = 0; i< getSizeMat(m); i++){

		if(getList(m->vetorLinha, i)){
			printList(getList(m->vetorLinha, i));

		}
	}
}
/*funcao que soma 2 matrizes*/
MAT *somaMat(MAT *m1, MAT *m2){

	if(getSizeMat(m1) != getSizeMat(m2)) return NULL;

	MAT *m3 = createMat(getSizeMat(m1));
	int linha, coluna;
	float valor, soma;
	/*copia a matriz m1 para a matriz m3*/
	for(int i = 0; i< getSizeMat(m1); i++){
		if(getList(m1->vetorLinha, i)){
			CELL *c = getHeadList(getList(m1->vetorLinha, i));
			while(c){
				linha = getLinha(c);
				coluna = getColuna(c);
				valor = getVal(c);
				insertMat(m3, linha, coluna, valor);
				c = getNextLinha(c);
			}
		}
	}
	/*loop que percorre a matriz m2 e busca na matriz m3, se nao existir a posicao insere na m3
	se existir a posicao e feita a soma, se a soma for igual a 0 a celula eh excluida*/
	for(int i = 0; i< getSizeMat(m2); i++){
		if(getList(m2->vetorLinha, i)){
			CELL *c = getHeadList(getList(m2->vetorLinha, i));
			while(c){				
				linha = getLinha(c);
				coluna = getColuna(c);
				valor = getVal(c);
				soma = search(m3, linha, coluna, 1);
				if(soma){
					valor += soma;
					if(valor){
						insertMat(m3, linha, coluna, valor);	
					}else{
						deletePos(m3, linha, coluna);
					}
				}else{
					insertMat(m3, linha, coluna, valor);
				}
				
				c = getNextLinha(c);
			}
		}
	}
	return m3;
}
/*funcao que deleta uma posicao da matriz*/
void deletePos(MAT *m, int linha, int coluna){

	CELL *anterior_linha =NULL;
	CELL *anterior_coluna = NULL;
	CELL *atual_linha = getHeadList(getList(m->vetorLinha, linha));
	CELL *atual_coluna = getHeadList(getList(m->vetorColuna, coluna));
	/*loop que percorre lista da linha ate chegar na posicao com a variavel atual_linha*/
	while(atual_linha){
		if(getLinha(atual_linha) == linha && getColuna(atual_linha) == coluna){
			/*loop que percorre lista da coluna ate chegar na posicao com a variavel atual_coluna*/
			while(atual_linha){
				if(getLinha(atual_coluna) == linha && getColuna(atual_coluna) == coluna){

						if(!anterior_linha && !proxCell(atual_linha,1)){
							setHeadList(getList(m->vetorLinha, linha), NULL);
							
							}else if(!anterior_linha && proxCell(atual_linha,1)){
								setHeadList(getList(m->vetorLinha, linha), getNextLinha(atual_linha));
								}else{
									setProxLinha(anterior_linha, getNextLinha(atual_linha));

								}

						if(!anterior_coluna && !proxCell(atual_coluna, 0)){
							setHeadList(getList(m->vetorColuna, coluna), NULL);

							}else if(!anterior_coluna && proxCell(atual_coluna,0)){
								setHeadList(getList(m->vetorColuna, coluna), getNextColuna(atual_coluna));
								
								}else{
									setProxColuna(anterior_coluna, getNextColuna(atual_coluna));
								}

						if(atual_linha == atual_coluna){
							freeCell(atual_linha);	
						}
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

float search(MAT *m, int linha, int coluna, int flag){

	if(flag){
		for(int i = 0; i< getSizeMat(m); i++){
			if(getList(m->vetorLinha, i)){
				CELL *c = getHeadList(getList(m->vetorLinha, i));
				while(c){
					if(getLinha(c) == linha && getColuna(c) == coluna){
						return getVal(c);
					}
					c = getNextLinha(c);
				}
			}
		}
	}else{
		for(int i = 0; i< getSizeMat(m); i++){
			if(getList(m->vetorColuna, i)){
				CELL *c = getHeadList(getList(m->vetorColuna, i));
				while(c){
					if(getLinha(c) == linha && getColuna(c) == coluna){
						return getVal(c);
					}
					c = getNextColuna(c);
				}
			}
		}
	}
	return 0.0;
}
