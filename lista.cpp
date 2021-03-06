#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


lista * inicia_lista(){//inicia uma nova estrutura auxiliar
	lista * nova =  (lista *)malloc(sizeof(lista));
	nova->raiz = NULL;
	nova->memoria = 0;
	return nova;
}

no * aloca_no(unsigned long long n){//aloca e retorna um novo no
    no * novo = (no*) malloc(sizeof(no));
    novo->prox = NULL;
    novo->n = n;
    return novo;
}

no * adiciona_no(lista * l, no * anterior, unsigned long long n){//adiciona um novo no apos o anterior e retorna esse novo no para ser o novo anterior
    if(l->raiz == NULL){
    	l->raiz = aloca_no(n);
    	return l->raiz;
	}
    anterior->prox = aloca_no(n);
    if(anterior->prox == NULL){//caso o novo no nao seja alocado, desaloca lista e retorna NULL
    	desaloca_lista(l);
    	return NULL;
	}
	return anterior->prox;//retorna o novo no caso seja adicionado com sucesso
}

void desaloca_lista(lista * l){//desaloca a lista inteira e a estrutura auxiliar, retornando NULL
	no * atual = l->raiz;
    no * prox = atual->prox;
    do{
        free(atual);
        atual = prox;
        prox = prox->prox;
    }while(prox!=NULL);
    free(atual);  
    l->raiz = NULL;
}

void imprimir_lista(lista * l){//imprime a lista na tela(para debug)
    no * raiz = l->raiz;
	if(raiz == NULL){
		printf("Lista vazia!\n");
		getchar();
		return;
	}
	printf("%llu", raiz->n);
	no * prox = raiz -> prox;
	while(prox!=NULL){
		printf("->%llu", prox->n);
		prox = prox->prox;
	}	
	getchar();
	printf("\n");
	printf("\n");
}

lista * finalizaLista(lista * l){
	if(l->raiz != NULL)
		desaloca_lista(l);
	free(l);
	return NULL;
}
