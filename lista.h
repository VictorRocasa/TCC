#ifndef LISTA_H
#define LISTA_H

typedef struct Lista{
    unsigned long long n;
    struct Lista * prox;
}no;

no * aloca_no(unsigned long long n);
void adiciona_no(no * raiz, unsigned long long n);
no * desaloca_lista(no * raiz);
void imprime(no * raiz);

#endif /*LISTA_H*/
