#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TEST 1
#if !TEST
	#if _WIN64
		#define MAXT 500000000llu //tamanho máximo do vetor escolhido para 64bits, gira em torno de 8GB na forma de lista, mais uns 3 auxiliar
	#else
		#define MAXT 50000000llu //tamanho máximo do vetor escolhido para 32bits, gira em torno de 800MB na forma de lista mais uns 300 auxiliar
	#endif
	#define MAXN 18446744073709551615llu //maior número possível(unsigned long long 32bit) - grande o bastante
#else
	#define MAXT 1000000llu //teste: três iterações apenas
	#define MAXN 1000000llu //numero "pequeno" para poucas iterações
#endif

int conta_aleatoria = 0;
int ordenada_crescente = 0;
int ordenada_decrescente = 0;
int conta_igual = 0;
int conta_pior_caso = 0;

void gravar_entrada_aleatoria(unsigned long long t, unsigned long long n);//gera 5 entrada com t elementos variando de 0 a n
void gravar_entrada_crescente(unsigned long long t);//gera uma entrada com t elementos ordenados(crescente)
void gravar_entrada_decrescente(unsigned long long t);//gera uma entrada com t elementos ordenados(decrescente)
void gravar_entrada_igual(unsigned long long t, unsigned long long n);//Função para gerar uma entrada com t elementos equivalentes a n
void gravar_entrada_pior_caso(unsigned long long t);//gera 5 entrada com t elementos variando de 10000000000000000000 a MAXT
FILE * criar_arquivo(char * arq);

int main(){
    unsigned long long t;
	for(t = 10000; t < MAXT; t *= 10){//valor de t variando de 10000 a MAXT
	    unsigned long long n;
	    unsigned long long maxn = MAXN/10;//criterio de parada
        for(n = 10; n < maxn; n *= 10){//valor de n variando de <10 a <MAXN
            gravar_entrada_aleatoria(t,n);
			gravar_entrada_igual(t,n-1);
        }
        gravar_entrada_aleatoria(t,MAXN);//valor de n = MAXN
		gravar_entrada_crescente(t);
		gravar_entrada_decrescente(t);
		gravar_entrada_pior_caso(t);
	}
        gravar_entrada_aleatoria(MAXT,MAXN);//valor de t = MAXT e de n = MAXN
		gravar_entrada_crescente(MAXT);//valor de t = MAXT
		gravar_entrada_decrescente(MAXT);//valor de t = MAXT
		gravar_entrada_pior_caso(MAXT);//valor de t = MAXT


    return 0;
}

void gravar_entrada_aleatoria(unsigned long long t,unsigned long long n){
    int i;//contador para criar 5 entradas
    unsigned long long j;//contador para pecorrer o vetor de tamanho t
    char * arq = (char*)malloc(256*sizeof(char));
    srand(time(NULL));
    for(i = 0; i < 5; i++){
        conta_aleatoria++;
		sprintf(arq, ".\\entradas_aleatorias\\conta_aleatoria_%d.txt", conta_aleatoria);
    	FILE * p = criar_arquivo(arq);
        fprintf(p, "%llu;%llu\n", t, n);
        for(j = 0; j < t; j++)
            fprintf(p, "%llu;", rand() * rand() * rand() % n);
    	fclose(p);
    	printf("Aleatoria %d salva\n", conta_aleatoria);
    }
    free(arq);
}

void gravar_entrada_crescente(unsigned long long t){
    unsigned long long i;
    char * arq = (char*)malloc(256*sizeof(char));
    ordenada_crescente++;
    sprintf(arq, ".\\entradas_crescentes\\entrada_crescente_%d.txt", ordenada_crescente);
    FILE * p = criar_arquivo(arq);
    fprintf(p, "%llu\n", t);
    for(i = 0; i < t; i++)
        fprintf(p, "%llu;", i);
    fclose(p);
    printf("Crescente %d salva\n", ordenada_crescente);
    free(arq);
}

void gravar_entrada_decrescente(unsigned long long t){
    unsigned long long i;
    unsigned long long k = t-1;
    char * arq = (char*)malloc(256*sizeof(char));
    ordenada_decrescente++;
    sprintf(arq, ".\\entradas_decrescentes\\entrada_decrescente_%d.txt", ordenada_decrescente);
    FILE * p = criar_arquivo(arq);
    fprintf(p, "%llu\n", t);
    for(i = 0; i < t; i++){
        fprintf(p, "%llu;", k);
        k--;
    }
    fclose(p);
    printf("Decrescente %d salva\n", ordenada_decrescente);
    free(arq);
}

void gravar_entrada_igual(unsigned long long t,unsigned long long n){
    unsigned long long i;
    unsigned long long * entrada = malloc(t*sizeof(unsigned long long));
    char * arq = (char*)malloc(256*sizeof(char));
    conta_igual++;
    sprintf(arq, ".\\entradas_iguais\\entrada_igual_%llu.txt", conta_igual);
    FILE * p = criar_arquivo(arq);
    fprintf(p, "%llu;%llu\n", t, n);
    for(i = 0; i < t; i++)
        fprintf(p, "%llu;", n);
    fclose(p);
    printf("Igual %d salva\n", conta_igual);
    free(arq);
}

void gravar_entrada_pior_caso(unsigned long long t){
    int i;//contador para criar 5 entradas
    unsigned long long j;//contador para pecorrer o vetor de tamanho t
    srand(time(NULL));
    unsigned long long n = 8446744100000000000;//maior numero possivel que ao somado a 10000000000000000000 não vai dar overflow
    char * arq = (char*)malloc(256*sizeof(char));
    for(i = 0; i < 5; i++){
        conta_pior_caso++;
		sprintf(arq, ".\\entradas_pior_caso\\pior_caso_%d.txt", conta_pior_caso);
	    FILE * p = criar_arquivo(arq);
	    fprintf(p, "%llu\n", t);
        for(j = 0; j < t; j++)
             fprintf(p, "%llu;" , 10000000000000000000llu + rand() *  rand() *  rand() % n);
        fclose(p);
		printf("Pior caso %d salva\n", conta_pior_caso);
    }
    free(arq);
}

FILE * criar_arquivo(char * arq){
    FILE * p;
    p =  fopen(arq,"w");
    p =  fopen(arq,"a");
    return p;
}
