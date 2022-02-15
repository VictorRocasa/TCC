#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


lista * cria_lista(){
	lista * nova =  (lista *)malloc(sizeof(lista));
	nova->raiz = NULL;
	return nova;
}

no * aloca_no(unsigned long long n){//retorna um novo no
    no * novo = (no*) malloc(sizeof(no));
    novo->prox = NULL;
    novo->n = n;
    return novo;
}

no * adiciona_no(lista * l, no * anterior, unsigned long long n){//adiciona um novo no ao fim da lista passada por parametro
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

lista * desaloca_lista(lista * l){//desaloca todos os nos da lista
	no * atual = l->raiz;
    no * prox = atual->prox;
    do{
        free(atual);
        atual = prox;
        prox = prox->prox;
    }while(prox!=NULL);
    free(atual);  
    free(l);
    return NULL;
}

void imprimir_lista(lista * l){//imprime todos os nos da lista
    no * raiz = l->raiz;
	if(raiz == NULL){
		printf("No vazia!\n");
		return;
	}
	printf("%llu\n", raiz->n);
	no * prox = raiz -> prox;
	while(prox!=NULL){
		printf("%llu\n", prox->n);
		prox = prox->prox;
	}	
}
