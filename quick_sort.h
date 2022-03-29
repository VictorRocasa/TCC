#ifndef QUICK_H
#define QUICK_H
#include "lista.h"

typedef struct Pivor{//lista de pivores para simular a recursao
	no * elemento;//no da lista que representa o pivor
	no * esq;//sublista para os elementos menores
	no * dir;//sublista para os elementos maiores
	no * ultimoPivor;//ponteiro para mover elementos para o fim do pivor(melhora o desenpenho no caso de repeticoes na entrada)
	struct Pivor * pai;//aponta para o pivor pai
}pivor;

pivor * novo(no * elemento, pivor * pai);
int quickSort(lista * l);

#endif /* QUICK_H*/
