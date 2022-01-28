#include "lista.h" 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

no * ler_entrada(char * arq);//fun��o para ler uma entrada de um arquivo passado por par�metro

int contaDigitos(unsigned long long n);
void mergesort(no * entrada);//função para realizar o merge sorte na entrada e salvar seus dados
void quicksort(no * entrada);//função para realizar o quick sort na entrada e salvar seus dados
void timsort(no * entrada);//função para realizar o tim sort na entrada e salvar seus dados
void radixsort1d(no * entrada);//função para realizar o radix(1d) sort na entrada e salvar seus dados
void radixsortNd(no * entrada);//função para realizar o radix(Nd) sort na entrada e salvar seus dados


int main(){
    ler_entrada(".\\entradas_decrescentes\\entrada_decrescente_3.txt");
	
    return 0;
}

int contaDigitos(unsigned long long n){
	int d;
	for(d = 0; n > 0; n /= 10)
		d++;
	return d;
}

no * ler_entrada(char * arq){
	FILE * p;
	p = fopen(arq, "r");
	unsigned long long tam;
	unsigned long long maior;
	char * buf = malloc(256*sizeof(char));
	fgets(buf,256,p);
	printf("%s", buf);
	fgets(buf,256,p);
	printf("%s", buf);
	//printf("%d", contaDigitos(maior));
	fclose(p);
}

void ler_entradas_aleatorias(){
    FILE * p;
    p =  fopen("entrada_aleatoria.txt","a");
    fclose(p);
}

void ler_entradas_ordenadas(){
    FILE * p;
    p =  fopen("ordenada_crescente.txt.txt","a");
    
    p =  fopen("ordenada_decrescente.txt.txt","a");
    fclose(p);
}

void ler_entradas_iguais(){
    FILE * p;
    p =  fopen("entrada_igual.txt","a");
    fclose(p);
}

void ler_entradas_pior_caso(){
    FILE * p;
    p =  fopen("pior_caso.txt","a");
    fclose(p);
}
