#ifndef LISTA_H
#define LISTA_H

struct Lista;
typedef struct Lista item;
item * aloca_no(int n);
void adiciona_no(item * raiz, int n);
item * desaloca_lista(item * raiz);

#endif /*LISTA_H*/
