#include <stdlib.h>
#include "merge_sort.h"
#include "lista.h"
#include <stdio.h>
#include <windows.h>
#include <psapi.h>

janela * novaJanela(no * elemento, janela * pai){
	janela * j = (janela *)malloc(sizeof(janela));
	elemento->prox = NULL;
	j->elemento = elemento;
	j->prox = NULL;
	j->pai = pai;
	j->tamanho = 1;
	return j;
}

void mergeSort(lista * l){
	//Variaveis para contar o tempo
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    
	if(l->raiz == NULL)//lista vazia
		return;
	if(l->raiz->prox == NULL)//1 elemento
		return;
	no * prox = l->raiz->prox;//prox comeca no primeiro elemento depois da raiz
	janela * esquerda = novaJanela(l->raiz, NULL);//primeira janela comeca na raiz
	l->raiz = NULL;//raiz recebe NULL para parar de apontar para a lista
	no * atual = prox;//salva a referencia ao elemento atual
	prox = prox->prox;//anda um elemento na frente para nao perder a referencia ao resto da lista
	janela * direita = novaJanela(atual, NULL);//segunda janela comeca no segundo elemento
	while(1){
		if(direita == NULL){//quando a janela esquerda for a primeira janela
			atual = prox;//salva a referencia ao elemento atual
			if(atual == NULL){//se o atual for NULL, lista ordenada
				l->raiz = esquerda->elemento;//move de volta para a raiz os elementos
				free(esquerda);//libera a ultima janela
				
				QueryPerformanceCounter(&end);
				l->tempo = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;//salva o tempo em segundos
				
				return;
			}
			prox = prox->prox;//anda um elemento na frente para nao perder a referencia ao resto da lista
			direita = novaJanela(atual, esquerda);//cria uma nova janela na direita
		}
		else if(esquerda->tamanho == direita->tamanho || prox==NULL){//merge
			no * merge;//lista resultado do merge
			no * ultimoMerge;//variavel para colocar elementos no fim da lista
			if(esquerda->elemento->n <= direita->elemento->n){//se esquerda e menor ou igual insere no comeco do merge
				merge = esquerda->elemento;
				esquerda->elemento = esquerda->elemento->prox;
			}
			else{//se direita e menor ou igual insere no comeco do merge
				merge = direita->elemento;
				direita->elemento = direita->elemento->prox;
			}
			ultimoMerge = merge;
			ultimoMerge->prox = NULL;
			while(1){
				if(esquerda->elemento == NULL){//se esquerda se tornar NULL, move o resto da janela direita para o merge e sai do loop
					ultimoMerge->prox = direita->elemento;
					break;
				}
				else if(direita->elemento == NULL){//se direita se tornar NULL, move o resto da janela esquerda para o merge e sai do loop
					ultimoMerge->prox  = esquerda->elemento;
					break;					
				}
				else{
					if(esquerda->elemento->n <= direita->elemento->n){//se esquerda e menor ou igual insere no merge
						ultimoMerge->prox  = esquerda->elemento;
						esquerda->elemento = esquerda->elemento->prox;
						ultimoMerge = ultimoMerge->prox;
					}
					else{//se direita e menor ou igual insere no comeco do merge
						ultimoMerge->prox = direita->elemento;
						direita->elemento = direita->elemento->prox;
						ultimoMerge = ultimoMerge->prox;
					}
					ultimoMerge->prox = NULL;
				}
			}
			esquerda->elemento = merge;
			esquerda->tamanho *= 2;
			janela * aux = direita;
			if(esquerda->pai!=NULL){//volta para a esquerda
				direita = esquerda;
				esquerda = esquerda->pai;
			}
			else
				direita = NULL;
			free(aux);
		}
		else{			
			//move as janelas para a direita
			esquerda = direita;
			atual = prox;//salva a referencia ao elemento atual
			prox = prox->prox;//anda um elemento na frente para nao perder a referencia ao resto da lista
			direita = novaJanela(atual, esquerda);//cria uma nova janela na direita
		}
	}	
}  
