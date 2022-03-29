#ifndef MERGE_H
#define MERGE_H
#include "lista.h"

typedef struct Janela{//estrutura auxiliar para o merge
	no * elemento0;//primeiro elemento da janela
	struct Janela * prox;//proxima janela
	struct Janela * pai;//janela anterior
	unsigned long long tamanho;//tamanho da janela de comparacao(quantos elementos vao sofrer o merge nessa iteracao)
}janela;

janela * novaJanela(no * elemento, janela * pai);
int MergeSort(lista * l);

#endif /* MERGE_H*/
