#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "maximos.h"
#include <windows.h>

int conta_aleatoria = 0;
int ordenada_crescente = 0;
int ordenada_decrescente = 0;
int conta_igual = 0;
int conta_pior_caso = 0;

void gravar_entrada_aleatoria(unsigned long long t, unsigned long long n);//gera 3 entradas com t elementos variando de 0 a n
void gravar_entrada_crescente(unsigned long long t);//gera uma entrada com t elementos ordenados(crescente)
void gravar_entrada_decrescente(unsigned long long t);//gera uma entrada com t elementos ordenados(decrescente)
void gravar_entrada_igual(unsigned long long t, unsigned long long n);//Função para gerar uma entrada com t elementos equivalentes a n
void gravar_entrada_pior_caso(unsigned long long t);//gera 3 entrada com t elementos variando de 10000000000000000000 a MAXT
FILE * criar_arquivo(char * arq);
FILE * info = criar_arquivo((char *)"cabecalho.txt");

int main(){
    unsigned long long t;
	unsigned long long maxn = MAXN/10;//criterio de parada
	for(t = MINT; t <= MAXT; t *= 10){//valor de t variando de 10000 a MAXT
        printf("Entradas de tamanho %llu:\n", t);
	    unsigned long long n;
		gravar_entrada_crescente(t);
		gravar_entrada_decrescente(t);
		gravar_entrada_pior_caso(t);
        for(n = MINN; n < maxn; n *= 10){//valor de n variando de <10 a <MAXN
        	printf("Maior numero %llu\n", n);
			gravar_entrada_igual(t,n-1);
            gravar_entrada_aleatoria(t,n);
        }
        gravar_entrada_aleatoria(t,MAXN);//valor de n = MAXN(sai do loop antes de chegar a MAXN)
		gravar_entrada_igual(t,MAXN);//valor de n = MAXN(sai do loop antes de chegar a MAXN)
		printf("\n");
	}
	fclose(info);

    return 0;
}

void gravar_entrada_aleatoria(unsigned long long t,unsigned long long n){
    int i;//contador para criar 5 entradas
    unsigned long long j;//contador para gerar n numeros
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    srand(time(NULL));
	CreateDirectory("entradas_aleatorias", NULL);//cria o diretorio se nao existir
    for(i = 0; i < REP; i++){
        conta_aleatoria++;
		sprintf(arq, ".\\entradas_aleatorias\\entrada_aleatoria_%d.txt", conta_aleatoria);//caminho da entrada
    	FILE * p = criar_arquivo(arq);
        for(j = 0; j < t; j++)
            fprintf(p, "%llu\n", rand() * rand() * rand() % n);//salva cada elemento gerado aleatóriamente seguido de ;
    	fclose(p);
        fprintf(info, "aleatorias aleatoria %d %llu %llu\n", conta_aleatoria, t, n);//salva entrada no arquivo que armazena as entradas criadas
    	printf("Aleatoria %d salva\n", conta_aleatoria);//feedback visual
    }
    free(arq);
}

void gravar_entrada_crescente(unsigned long long t){
    unsigned long long i;
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    ordenada_crescente++;
	CreateDirectory("entradas_crescentes", NULL);//cria o diretorio se nao existir
    sprintf(arq, ".\\entradas_crescentes\\entrada_crescente_%d.txt", ordenada_crescente);
    FILE * p = criar_arquivo(arq);
    for(i = 0; i < t; i++)
        fprintf(p, "%llu\n", i);//salva cada elemento seguido de ;
    fclose(p);
    fprintf(info, "crescentes crescente %d %llu %llu\n", ordenada_crescente, t, t);//salva entrada no arquivo que armazena as entradas criadas
    printf("Crescente %d salva\n", ordenada_crescente);//feedback visual
    free(arq);
}

void gravar_entrada_decrescente(unsigned long long t){
    unsigned long long i;
    unsigned long long k = t-1;
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    ordenada_decrescente++;
	CreateDirectory("entradas_decrescentes", NULL);//cria o diretorio se nao existir
    sprintf(arq, ".\\entradas_decrescentes\\entrada_decrescente_%d.txt", ordenada_decrescente);
    FILE * p = criar_arquivo(arq);
    for(i = 0; i < t; i++){
        fprintf(p, "%llu\n", k);//salva cada elemento seguido de ;
        k--;
    }
    fclose(p);
    fprintf(info, "decrescentes decrescente %d %llu %llu\n", ordenada_decrescente, t, t);//salva entrada no arquivo que armazena as entradas criadas
    printf("Decrescente %d salva\n", ordenada_decrescente);//feedback visual
    free(arq);
}

void gravar_entrada_igual(unsigned long long t,unsigned long long n){
    unsigned long long i;
    unsigned long long * entrada = (unsigned long long*) malloc(t*sizeof(unsigned long long));
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    conta_igual++;
	CreateDirectory("entradas_iguais", NULL);//cria o diretorio se nao existir
    sprintf(arq, ".\\entradas_iguais\\entrada_igual_%d.txt", conta_igual);
    FILE * p = criar_arquivo(arq);
    for(i = 0; i < t; i++)
        fprintf(p, "%llu\n", n);//salva cada elemento seguido de \n
    fclose(p);
    fprintf(info, "iguais igual %d %llu %llu\n", conta_igual, t, n+1);//salva entrada no arquivo que armazena as entradas criadas
    printf("Igual %d salva\n", conta_igual);//feedback visual
    free(arq);
}

void gravar_entrada_pior_caso(unsigned long long t){
    int i;//contador para criar 5 entradas
    unsigned long long j;//contador para pecorrer o vetor de tamanho t
    srand(time(NULL));
    unsigned long long n = 8446744073709551615;//maior numero possivel que ao somado a 10000000000000000000 não vai dar overflow
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
	CreateDirectory("entradas_complexas", NULL);//cria o diretorio se nao existir
    for(i = 0; i < REP; i++){
        conta_pior_caso++;
		sprintf(arq, ".\\entradas_complexas\\entrada_complexa_%d.txt", conta_pior_caso);
	    FILE * p = criar_arquivo(arq);
        for(j = 0; j < t; j++)
             fprintf(p, "%llu\n" , 10000000000000000000llu + rand() *  rand() *  rand() % n);//salva cada elemento gerado aleatóriamente seguido de ;
        fclose(p);
    	fprintf(info, "complexas complexa %d %llu %llu\n", conta_pior_caso, t, MAXN);//salva entrada no arquivo que armazena as entradas criadas
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
