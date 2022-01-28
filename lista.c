#include "lista.h"
#include <stdlib.h>

item * aloca_no(unsigned long long n){
    item * no = malloc(sizeof(item));
    no->prox = NULL;
    no->n = n;
    return no;
}

void adiciona_no(item * raiz, unsigned long long n){
    item * prox = raiz->prox;
    while(prox->prox!=NULL){
        prox = prox->prox;
    }
    prox->prox = aloca_no(n);
}

item * desaloca_lista(item * raiz){
    item * atual = raiz;
    item * prox = raiz->prox;
    while(prox!=NULL){
        free(atual);
        atual = prox;
        prox = prox->prox;
    }
    return NULL;
}
