#include "lista.h"
#include <stdlib.h>

struct Lista{
    int n;
    struct Lista * prox;
};

item * aloca_no(int n){
    item * no = malloc(sizeof(item));
    no->prox = NULL;
    no->n = n;
    return no;
}

void adiciona_no(item * raiz, int n){
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
