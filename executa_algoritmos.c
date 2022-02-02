#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h" 
#include "merge_sort.h"

no * ler_entrada(char * arq);//funcao para ler uma entrada de a partir de um arquivo com seu endereco passado por parâmetro
void mergesort(no * entrada);//funcao para realizar o merge sorte na entrada e salvar seus dados
void quicksort(no * entrada);//funcao para realizar o quick sort na entrada e salvar seus dados
void insertionsort(no * entrada);//funcao para realizar o tim sort na entrada e salvar seus dados
void timsort(no * entrada);//funcao para realizar o tim sort na entrada e salvar seus dados
int conta_digitos(unsigned long long n);//funcao para contar o numero de digitos de um numero
void radixsort_vetor(no * entrada);//funcao para realizar o radix vetor sort na entrada e salvar seus dados
void radixsort_lista(no * entrada);//funcao para realizar o radix lista sort na entrada e salvar seus dados


int main(){
	printf("Desordenado: \n");
	no  * t = ler_entrada("teste.txt");
	imprimir_lista(t);
	printf("Merge: \n");
	MergeSort(&t);
	imprimir_lista(t);
	t = ler_entrada("teste.txt");
	printf("Quick: \n");
	quickSort(&t);
	imprimir_lista(t);
	
    return 0;
}

int conta_digitos(unsigned long long n){
	int d;
	for(d = 0; n > 0; n /= 10)
		d++;
	return d;
}

no * ler_entrada(char * arq){
	FILE * p;
	p = fopen(arq, "r");
	if(p == NULL){
		printf("ERRO DE LEITURA DE ARQUIVO NA FUNCAO DE ENTRADA!");
		exit(1);
	}
	char * n = malloc(22*sizeof(char));//22 tamanho maximo da entrada 20 do llu + \n + \0
	no * raiz;
	fgets(n,22,p);
	raiz = (no*)aloca_no(strtoull(n,NULL,10));
	while(fgets(n,22,p)!=NULL){
		if(n[0]=='\n')//caso a linha esteja vazia sai do loop
			break;
		if(!adiciona_no(raiz, strtoull(n,NULL,10)))
			return NULL;//caso a memoria acabe retorna NULL
	}
	fclose(p);
	return raiz;
}
