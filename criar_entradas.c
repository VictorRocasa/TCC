#include "lista.h" 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAXT 1000000000 //tamanho máximo do vetor
#define MAXN 4294967295 //maior número possível(unsigned int 32bit)

int conta_aleatoria = 0;
int ordenada_crescente = 0;
int ordenada_decrescente = 0;
int conta_igual = 0;
int conta_pior_caso = 0;

void gravar_entrada_aleatoria(unsigned int t, unsigned int n);//gera 5 entrada com t elementos variando de 0 a n
void gravar_entrada_ordenada(unsigned int t);//gera duas entrada com t elementos ordenados(crescente e decrescente)
void gravar_entrada_igual(unsigned int t, unsigned int n);//Função para gerar uma entrada com t elementos equivalentes a n
void gravar_entrada_pior_caso(unsigned int t);//gera 5 entrada com t elementos variando de 1000000000 a MAXT
void gravar_entrada(char * arq, int numero, unsigned int tamanho, unsigned int * v);

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
		gravar_entrada_pior_caso(t);
	}
	gravar_entrada_ordenada(MAXT);//tamanho maximo MAXT


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
        conta_aleatoria++;
        gravar_entrada("entrada_aleatoria.txt", conta_aleatoria, 16*t, entrada);
    }
}

void gravar_entrada_ordenada(unsigned int t){
    unsigned int i;
    
    unsigned int * entrada = malloc(t*sizeof(unsigned int));
    for(i = 0; i < t; i++)
        entrada[i] = i;
    ordenada_crescente++;
    gravar_entrada("ordenada_crescente.txt", ordenada_crescente, 16*t, entrada);

    entrada = malloc(t*sizeof(unsigned int));
    for(i = t-1; i > 0; i--)
        entrada[i] = i;
    ordenada_decrescente++;
    gravar_entrada("ordenada_decrescente.txt", ordenada_decrescente, 16*t, entrada);
}

void gravar_entrada_igual(unsigned int t,unsigned int n){
    unsigned int i;
    unsigned int * entrada = malloc(t*sizeof(unsigned int));
    for(i = 0; i < t; i++)
        entrada[i] = n;
    conta_igual++;
    gravar_entrada("entrada_igual.txt", conta_igual, 16*t, entrada);
}

void gravar_entrada_pior_caso(unsigned int t){
    int i;//contador para criar 5 entradas
    unsigned int j;//contador para pecorrer o vetor de tamanho t
    srand(time(NULL));
    int n = 3294967295;//maior numero possivel que ao somado a 1000000000 não vai dar overflow
    for(i = 0; i < 5; i++){
        unsigned int * entrada = malloc(t*sizeof(unsigned int));//vetor de tamanho t
        for(j = 0; j < t; j++)
            entrada[j] = 1000000000 + rand() % n;
        conta_pior_caso++;
        gravar_entrada("pior_caso.txt", conta_pior_caso, 16*t, entrada);
    }
}

void gravar_entrada(char * arq, int numero, unsigned int tamanho, unsigned int * v){
    printf("Salvando em %s, entrada numero %d, tamanho = %u mb\n", arq, numero, tamanho/1000000);
    free(v);
}