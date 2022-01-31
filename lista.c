#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

no * aloca_no(unsigned long long n){//retorna um novo no
    no * novo = (no*) malloc(sizeof(no));
    novo->prox = NULL;
    novo->n = n;
    return novo;
}

int adiciona_no(no * raiz, unsigned long long n){//adiciona um novo no ao fim da lista passada por parametro em raiz
    no * prox = raiz;
    while(prox->prox!=NULL){
        prox = prox->prox;
    }
    prox->prox = aloca_no(n);
    if(prox->prox == NULL){//caso o novo no nao seja alocado, desaloca lista e retorna 0
    	desaloca_lista(raiz);
    	return 0;
	}
	return 1;//retorna 1 ao adicionar novo no com sucesso
}

no * desaloca_lista(no * raiz){//desaloca todos os nos da lista
    no * atual = raiz;
    no * prox = raiz->prox;
    do{
        free(atual);
        atual = prox;
        prox = prox->prox;
    }while(prox!=NULL);
    return NULL;
}

void imprimir_lista(no * raiz){//imprime todos os nos da lista
	if(raiz == NULL){
		printf("Lista vazia!\n");
		return;
	}
	printf("%llu\n", raiz->n);
	no * prox = raiz -> prox;
	while(prox!=NULL){
		printf("%llu\n", prox->n);
		prox = prox->prox;
	}	
}
