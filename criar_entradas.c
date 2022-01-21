#include "lista.h" 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAXT 4000000000 //tamanho máximo do vetor
#define MAXN 4294967295 //maior número possível(unsigned int 32bit)

int conta_aleatoria = 1;
int conta_ordenada = 1;
int conta_igual = 1;

void gravar_entrada_aleatoria(unsigned int t, unsigned int n);//gera 5 entrada com t elementos variando de 0 a n
void gravar_entrada_ordenada(unsigned int t);//gera duas entrada com t elementos ordenados(crescente e decrescente)
void gravar_entrada_igual(unsigned int t, unsigned int n);//Função para gerar uma entrada com t elementos equivalentes a n

int main(){
    unsigned int t;
	for(t = 10000; t < MAXT; t *= 10){//valor de t variando de 10000 a MAXT
	    unsigned int n;
        for(n = 10; n < MAXN/10; n *= 10){//valor de n variando de <10 a <MAXN
            gravar_entrada_aleatoria(t,n);
			gravar_entrada_igual(t,n);
        }
        gravar_entrada_aleatoria(t,MAXN);//valor de n = MAXN
		gravar_entrada_ordenada(t);
	}
	gravar_entrada_ordenada(1000000000);


    return 0;
}

void gravar_entrada_aleatoria(unsigned int t,unsigned int n){
    int i;//contador para criar 5 entradas
    unsigned int j;//contador para pecorrer o vetor de tamanho t
    srand(time(NULL));
    for(i = 0; i < 5; i++){
        unsigned int * entrada = malloc(t*sizeof(unsigned int));//vetor de tamanho t
        for(j = 0; j < t; j++)
            entrada[j] = rand() % n;
        free(entrada);
        printf("Salvando aleatoria %d...t = %u e n = %u\n", conta_aleatoria, t, n);
        conta_aleatoria++;
    }
}

void gravar_entrada_ordenada(unsigned int t){
    unsigned int i;
    unsigned int * entrada = malloc(t*sizeof(unsigned int));
    for(i = 0; i < t; i++)
        entrada[i] = i;
    free(entrada);
    printf("Salvando ordenada crescente %d...t = %u\n", conta_ordenada, t);
    entrada = malloc(t*sizeof(unsigned int));
    for(i = t-1; i > 0; i--)
        entrada[i] = i;
    free(entrada);
    printf("Salvando ordenada decrescente %d...t = %u\n", conta_ordenada, t);
    conta_ordenada++;
}

void gravar_entrada_igual(unsigned int t,unsigned int n){
    unsigned int i;
    unsigned int * entrada = malloc(t*sizeof(unsigned int));
    for(i = 0; i < t; i++)
        entrada[i] = n;
    free(entrada);
    printf("Salvando igual  %d...t = %u e n = %u\n", conta_igual, t, n);
    conta_igual++;
}
    