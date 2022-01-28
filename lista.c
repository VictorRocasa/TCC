#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

no * aloca_no(unsigned long long n){
    no * no = malloc(sizeof(no));
    no->prox = NULL;
    no->n = n;
    return no;
}

void adiciona_no(no * raiz, unsigned long long n){
    no * prox = raiz->prox;
    while(prox->prox!=NULL){
        prox = prox->prox;
    }
    prox->prox = aloca_no(n);
}

no * desaloca_lista(no * raiz){
    no * atual = raiz;
    no * prox = raiz->prox;
    while(prox!=NULL){
        free(atual);
        atual = prox;
        prox = prox->prox;
    }
    return NULL;
}

void imprime(no * raiz){
	if(raiz == NULL)
		return;
	printf("%llu", raiz->n);
	no * prox = raiz -> prox;
	while(prox!=NULL){
		printf(" -> %llu", raiz->n);
		prox = prox->prox;
	}	
}

