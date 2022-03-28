#include <stdlib.h>
#include "quick_sort.h"
#include "lista.h"
#include <stdio.h>
#include <windows.h>
#include <psapi.h>

pivor * novo(no * elemento, pivor * pai){
	pivor * p = (pivor *) malloc(sizeof(pivor));
	if(p == NULL)
		return NULL;
	p->elemento = elemento;//no da lista
	p->esq = NULL;//inicia sublista para os elementos menores
	p->dir = NULL;//inicia sublista para os elementos maiores
	p->pai = pai;//aponta para o pivor pai
	return p;
}

int quickSort(lista * l){
	if(l->raiz == NULL)//lista vazia
		return 1;
	pivor * p = novo(l->raiz,NULL);//primeiro pivor(primeiro elemento por questoes de otimizacao para a lista usada)
	l->raiz = NULL;//;raiz para de apontar para a lista por enquanto
	no * ultimoGeral;//variavel para reenserir elementos na lista no futuro
	do{
		if(p->elemento->prox != NULL){//caso base 2: 1 elemento
			no * prox = p->elemento->prox;//prox comeca no elemento apos o pivor
			no * ultimoEsq;//variavel para mover os elementos para o fim da sublista da esquerda
			no * ultimoDir;//variavel para mover os elementos para o fim da sublista da direita	
			while(prox!=NULL){//pecorre toda a sublista atual
				if(prox->n < p->elemento->n){//elementos menores movidos para a esquerda
					if(p->esq == NULL){
						p->esq = prox;
						ultimoEsq = prox; 
					}
					else{
						ultimoEsq->prox = prox;
						ultimoEsq = prox;
					}
					prox = prox->prox;
					ultimoEsq->prox = NULL;
				}
				else{//elementos maiores ou iguais ao pivor movidos para a esquerda
					if(p->dir == NULL){
						p->dir = prox;
						ultimoDir = prox;
					}
					else{
						ultimoDir->prox = prox;
						ultimoDir = prox;
					}
					prox = prox->prox;
					ultimoDir->prox = NULL;
				}			
			}
			if(p->esq!=NULL)
				p = novo(p->esq,p);
			else if(p->dir!=NULL)
				p = novo(p->dir,p);
		}
		else{
			if(l->raiz == NULL){
				l->raiz = p->elemento;
				ultimoGeral = p->elemento;
			}
			else{
				ultimoGeral->prox = p->elemento;
				ultimoGeral = p->elemento;				
			} 
			pivor * aux = p;
			p = p->pai;
			free(aux);
			if(p == NULL)
				return 1;
			if(p->esq != NULL)
				p->esq = NULL;
			else
				p->dir = NULL;
		}
	}while(1);
}
