#ifndef QUICK_H
#define QUICK_H
#include "lista.h"

typedef struct Pivor{//lista de pivores para simular a recursao
	no * elemento;//no da lista que representa o pivor
	no * esq;//sublista para os elementos menores
	no * dir;//sublista para os elementos maiores
	struct Pivor * pai;//aponta para o pivor pai
}pivor;

pivor * novo(no * elemento);
int quickSort(lista * l);
void iteraEsquerda(no * esq);
void iteraDireita(no * dir);

#endif /* QUICK_H*/
