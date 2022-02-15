#ifndef LISTA_H
#define LISTA_H

typedef struct No{
    unsigned long long n;
    struct No * prox;
}no;

typedef struct Lista{
    struct No * raiz;
    unsigned long long tamanho;
    int digitos_maior_numero;
}lista;

lista * cria_lista();
no * aloca_no(unsigned long long n);
no * adiciona_no(lista * l, no * anterior, unsigned long long n);
lista * desaloca_lista(lista * l);
void imprimir_lista(lista * l);

#endif /*LISTA_H*/

