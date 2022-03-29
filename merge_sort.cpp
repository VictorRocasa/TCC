#include <stdlib.h>
#include "merge_sort.h"
#include "lista.h"
#include <stdio.h>
#include <windows.h>
#include <psapi.h>

janela * novaJanela(no * elemento, janela * pai){
	janela * j = (janela *)malloc(sizeof(janela));
	j->elemento0 = elemento;
	j->prox = NULL;
	j->pai = pai;
	j->tamanho = 1;
	return j;
}

int mergeSort(lista * l){
	if(l->raiz == NULL)//lista vazia
		return 1;
	if(l->raiz->prox == NULL)//1 elemento
		return 1;
	janela * j = novaJanela(l->raiz, NULL);//primeira janela comeca na raiz
	no * prox = l->raiz->prox;//prox comeca no proximo elemento
	l->raiz = NULL;//raiz recebe NULL para parar de apontar para a lista
	while(prox!=NULL){
		for(unsigned long long i = 0; i < j->tamanho; i){
			j = novaJanela(prox,j);
			prox = prox->prox;
			if(prox == NULL)
				break;
		}
	}	
}  
