#ifndef LISTA_H
#define LISTA_H

typedef struct Lista{
    unsigned long long n;
    struct Lista * prox;
}item;
item * aloca_no(unsigned long long n);
void adiciona_no(item * raiz, unsigned long long n);
item * desaloca_lista(item * raiz);

#endif /*LISTA_H*/
