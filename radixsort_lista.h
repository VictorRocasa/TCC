#ifndef RADIXSORTV_L
#define RADIXSORTV_L
#include "lista.h"

int conta_digitos(unsigned long long n);//funcao para contar o numero de digitos de um numero
void troca_entre_raizes(no ** baldes_raiz, no ** baldes_aux, no ** final);//realiza a troca entre as raizes
void radix_lista(lista * l, int d);//funcao para executar o radixsort em uma lista passada por parametro para um numero d de digitos


#endif /* RADIXSORTV_L*/
