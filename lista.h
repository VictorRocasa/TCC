#ifndef LISTA_H
#define LISTA_H

typedef struct Lista{
    int n;
    struct Lista * prox;
}item;
item * aloca_no(int n);
void adiciona_no(item * raiz, int n);
item * desaloca_lista(item * raiz);

#endif /*LISTA_H*/