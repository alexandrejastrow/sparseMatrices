#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"
#include "arq.h"

int main(int argc, char **argv){

	/*variaveis*/
	MAT *mat[argc];
	float val;
	int topo, lin, col;

	/*loop para criacao das matrizes dos arquivos fornecidos*/
	for(int i=1 ; i<argc; i++){


		FILE *arq = open_arq(argv[i]);
		if(arq != NULL){
			/*pega o tamanho da matriz*/	
			topo = pega_topo(arq);
			/*cria a matriz*/
			mat[i-1] = createMat(topo);

			if(mat[i-1] == NULL) return 1;

			/*loop para pegar todas as informacoes do arquivo*/
			while(!feof(arq)){
				/*funcao que recebe os valores de linha, coluna, e valor do arquivo*/
				pega_linha(arq, &lin, &col, &val);
				/*se os valores obitidos estiverem de acordo com esperado*/
				if((lin>=0 && lin <= topo) && (col>=0 && col <= topo)){
					/*insere na matriz*/
					insertMat(mat[i-1], lin-1, col-1, val);
				}
			}
		}
	}
	/*soma a matriz0 com a matriz1 na matriz2*/
	mat[2] = somaMat(mat[0], mat[1]);
	/*imprime a soma da matriz*/
	printMat(mat[2]);
	
	return 0;
}