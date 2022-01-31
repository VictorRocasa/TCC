#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h"

#define TEST 1
#if !TEST
	#if _WIN64
		#define MAXT 100000000llu //tamanho m�ximo do vetor escolhido para 64bits
	#else
		#define MAXT 10000000llu //tamanho m�ximo do vetor escolhido para 32bits
	#endif
	#define MAXN 18446744073709551615llu //maior n�mero poss�vel(unsigned long long 32bit) - grande o bastante
#else
	#define MAXT 1000000llu //teste: tr�s itera��es apenas
	#define MAXN 1000000llu //numero "pequeno" para poucas itera��es
#endif

int conta_aleatoria = 0;
int ordenada_crescente = 0;
int ordenada_decrescente = 0;
int conta_igual = 0;
int conta_pior_caso = 0;

void gravar_entrada_aleatoria(unsigned long long t, unsigned long long n);//gera 3 entradas com t elementos variando de 0 a n
void gravar_entrada_crescente(unsigned long long t);//gera uma entrada com t elementos ordenados(crescente)
void gravar_entrada_decrescente(unsigned long long t);//gera uma entrada com t elementos ordenados(decrescente)
void gravar_entrada_igual(unsigned long long t, unsigned long long n);//Fun��o para gerar uma entrada com t elementos equivalentes a n
void gravar_entrada_pior_caso(unsigned long long t);//gera 3 entrada com t elementos variando de 10000000000000000000 a MAXT
//void gravar_entrada_parcialmente_ordenada(unsigned long long t, unsigned long long n);//gera 3 entradas ordenadas variando de 0 a t, com alguns n�meros aleatorios no meio
FILE * criar_arquivo(char * arq);

int main(){
    unsigned long long t;
	unsigned long long maxn = MAXN/10;//criterio de parada
	for(t = 10000; t <= MAXT; t *= 10){//valor de t variando de 10000 a MAXT
	    unsigned long long n;
        for(n = 10; n < maxn; n *= 10){//valor de n variando de <10 a <MAXN
            gravar_entrada_aleatoria(t,n);
			gravar_entrada_igual(t,n-1);
        }
        gravar_entrada_aleatoria(t,MAXN);//valor de n = MAXN(sai do loop antes de chegar a MAXN)
		gravar_entrada_crescente(t);
		gravar_entrada_decrescente(t);
		gravar_entrada_pior_caso(t);
	}


    return 0;
}

void gravar_entrada_aleatoria(unsigned long long t,unsigned long long n){
    int i;//contador para criar 5 entradas
    unsigned long long j;//contador para gerar n numeros
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    srand(time(NULL));
    for(i = 0; i < 3; i++){
        conta_aleatoria++;
		sprintf(arq, ".\\entradas_aleatorias\\conta_aleatoria_%d.txt", conta_aleatoria);//caminho da entrada
    	FILE * p = criar_arquivo(arq);
        for(j = 0; j < t; j++)
            fprintf(p, "%llu\n", rand() * rand() * rand() % n);//salva cada elemento gerado aleat�riamente seguido de ;
    	fclose(p);
    	printf("Aleatoria %d salva\n", conta_aleatoria);//feedback visual
    }
    free(arq);
}

void gravar_entrada_crescente(unsigned long long t){
    unsigned long long i;
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    ordenada_crescente++;
    sprintf(arq, ".\\entradas_crescentes\\entrada_crescente_%d.txt", ordenada_crescente);
    FILE * p = criar_arquivo(arq);
    for(i = 0; i < t; i++)
        fprintf(p, "%llu\n", i);//salva cada elemento seguido de ;
    fclose(p);
    printf("Crescente %d salva\n", ordenada_crescente);//feedback visual
    free(arq);
}

void gravar_entrada_decrescente(unsigned long long t){
    unsigned long long i;
    unsigned long long k = t-1;
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    ordenada_decrescente++;
    sprintf(arq, ".\\entradas_decrescentes\\entrada_decrescente_%d.txt", ordenada_decrescente);
    FILE * p = criar_arquivo(arq);
    for(i = 0; i < t; i++){
        fprintf(p, "%llu\n", k);//salva cada elemento seguido de ;
        k--;
    }
    fclose(p);
    printf("Decrescente %d salva\n", ordenada_decrescente);//feedback visual
    free(arq);
}

void gravar_entrada_igual(unsigned long long t,unsigned long long n){
    unsigned long long i;
    unsigned long long * entrada = malloc(t*sizeof(unsigned long long));
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    conta_igual++;
    sprintf(arq, ".\\entradas_iguais\\entrada_igual_%d.txt", conta_igual);
    FILE * p = criar_arquivo(arq);
    for(i = 0; i < t; i++)
        fprintf(p, "%llu\n", n);//salva cada elemento seguido de ;
    fclose(p);
    printf("Igual %d salva\n", conta_igual);//feedback visual
    free(arq);
}

void gravar_entrada_pior_caso(unsigned long long t){
    int i;//contador para criar 5 entradas
    unsigned long long j;//contador para pecorrer o vetor de tamanho t
    srand(time(NULL));
    unsigned long long n = 8446744073709551615;//maior numero possivel que ao somado a 10000000000000000000 n�o vai dar overflow
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    for(i = 0; i < 3; i++){
        conta_pior_caso++;
		sprintf(arq, ".\\entradas_pior_caso\\pior_caso_%d.txt", conta_pior_caso);
	    FILE * p = criar_arquivo(arq);
        for(j = 0; j < t; j++)
             fprintf(p, "%llu\n" , 10000000000000000000llu + rand() *  rand() *  rand() % n);//salva cada elemento gerado aleat�riamente seguido de ;
        fclose(p);
		printf("Pior caso %d salva\n", conta_pior_caso);//feedback visual
    }
    free(arq);
}

FILE * criar_arquivo(char * arq){
    FILE * p;
    p =  fopen(arq,"w");
    p =  fopen(arq,"a");
    return p;
}
