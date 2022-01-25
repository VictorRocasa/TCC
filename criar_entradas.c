﻿#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define EMULADOR 1//Se o codigo está sendo executado no onlinegdb
#define MAXT 1000//1000000000 //tamanho máximo do vetor
#define MAXN 4294967295 //maior número possível(unsigned int 32bit)

int conta_aleatoria = 0;
int ordenada_crescente = 0;
int ordenada_decrescente = 0;
int conta_igual = 0;
int conta_pior_caso = 0;

void gravar_entrada_aleatoria(unsigned int t, unsigned int n);//gera 5 entrada com t elementos variando de 0 a n
void gravar_entrada_crescente(unsigned int t);//gera uma entrada com t elementos ordenados(crescente)
void gravar_entrada_decrescente(unsigned int t);//gera uma entrada com t elementos ordenados(decrescente)
void gravar_entrada_igual(unsigned int t, unsigned int n);//Função para gerar uma entrada com t elementos equivalentes a n
void gravar_entrada_pior_caso(unsigned int t);//gera 5 entrada com t elementos variando de 1000000000 a MAXT
void gravar_entrada(char * arq, unsigned int tamanho, unsigned int * v);

int main(){
    unsigned int t;
	for(t = 1; t <= MAXT; t *= 10){//valor de t variando de 10000 a MAXT
	    unsigned int n;
        for(n = 10; n < MAXN/10; n *= 10){//valor de n variando de <10 a <MAXN
            gravar_entrada_aleatoria(t,n);
			gravar_entrada_igual(t,n);
        }
        gravar_entrada_aleatoria(t,MAXN);//valor de n = MAXN
		gravar_entrada_crescente(t);
		gravar_entrada_decrescente(t);
		gravar_entrada_pior_caso(t);
	}


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
        char * arq = (char*)malloc(32*sizeof(char));
        if(EMULADOR)
            sprintf(arq, "entrada_aleatoria.txt");
        else
            sprintf(arq, "./entradas_aleatorias/entrada_aleatoria_%u.txt", conta_aleatoria);
        gravar_entrada(arq, t, entrada);
    }
}

void gravar_entrada_crescente(unsigned int t){
    unsigned int i;
    unsigned int * entrada = malloc(t*sizeof(unsigned int));
    for(i = 0; i < t; i++)
        entrada[i] = i;
    ordenada_crescente++;
    char * arq = (char*)malloc(32*sizeof(char));
    if(EMULADOR)
        sprintf(arq, "entrada_crescente.txt");
    else
        sprintf(arq, "./entradas_crescentes/entrada_crescente_%u.txt", ordenada_crescente);
    gravar_entrada(arq, t, entrada);
    free(arq);
}

void gravar_entrada_decrescente(unsigned int t){
    unsigned int i;
    unsigned int k = t-1;
    unsigned int * entrada = malloc(t*sizeof(unsigned int));
    for(i = 0; i < t; i++){
        entrada[i] = k;
        k--;
    }
    ordenada_decrescente++;
    char * arq = (char*)malloc(32*sizeof(char));
    if(EMULADOR)
        sprintf(arq, "entrada_decrescente.txt");
    else
        sprintf(arq, "./entradas_decrescentes/entrada_decrescente_%u.txt", ordenada_decrescente);
    gravar_entrada(arq, t, entrada);
    free(arq);
}

void gravar_entrada_igual(unsigned int t,unsigned int n){
    unsigned int i;
    unsigned int * entrada = malloc(t*sizeof(unsigned int));
    for(i = 0; i < t; i++)
        entrada[i] = n;
    conta_igual++;
    char * arq = (char*)malloc(32*sizeof(char));
    if(EMULADOR)
        sprintf(arq, "entrada_igual.txt");
    else
        sprintf(arq, "./entradas_iguais/entrada_igual_%u.txt", conta_igual);
    gravar_entrada(arq, t, entrada);
    free(arq);
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
    char * arq = (char*)malloc(32*sizeof(char));
    if(EMULADOR)
        sprintf(arq, "pior_caso.txt");
    else
        sprintf(arq, "./entradas_pior_caso/pior_caso_%u.txt", conta_pior_caso);
    gravar_entrada(arq, t, entrada);
    free(arq);
    }
}

void gravar_entrada(char * arq, unsigned int tamanho, unsigned int * v){
    FILE * p;
    unsigned int i;
    unsigned int tamanhoKB = 16 * tamanho;
    char * output = malloc(16 * sizeof(char));
    if(EMULADOR)
        p =  fopen(arq,"a");
    else
        p =  fopen(arq,"w");
    fprintf(p, "%u;%u;\n", tamanho, tamanhoKB);
    for(i = 0; i < tamanho; i++){
        fprintf(p, "%u;", v[i]);
    }
    fputs("\n", p);
    fclose(p);
    free(v);
}