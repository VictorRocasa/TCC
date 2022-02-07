#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h" 
#include "merge_sort.h"
#include "insertion_sort.h"

int conta_digitos(unsigned long long n);//funcao para contar o numero de digitos de um numero
no * ler_entrada(char * arq);//funcao para ler uma entrada de a partir de um arquivo com seu endereco passado por parâmetro
void entradas_aleatorias();//executa os algoritmos usando entradas aleatorias
void entradas_crescentes();//executa os algoritmos usando entradas crescentes
void entradas_decrescentes();//executa os algoritmos usando entradas decrescentes
void entradas_iguais();//executa os algoritmos usando entradas iguais
void entradas_pior_caso();//executa os algoritmos usando entradas pior caso

int main(){//teste.txt
	entradas_aleatorias();
	
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

void entradas_aleatorias(){
	printf("Teste tempo:\n");
	unsigned long long tamanho;
	unsigned long long qtd_digitos;
	clock_t inicio = clock();
	no * teste = ler_entrada(".\\entradas_pior_caso\\pior_caso_6.txt");
	clock_t fim = clock();
	double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
	printf("Tempo total leitura: %lf\n", tempo_execucao);
	inicio = clock();
	insertion(&teste);
	fim = clock();
	tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
	printf("Tempo total insertionSort: %lf\n", tempo_execucao);
	desaloca_lista(teste);
	teste = ler_entrada(".\\entradas_pior_caso\\pior_caso_6.txt");
	inicio = clock();
	quickSort(&teste);
	fim = clock();
	tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
	printf("Tempo total quickSort: %lf\n", tempo_execucao);
	desaloca_lista(teste);
	teste = ler_entrada(".\\entradas_pior_caso\\pior_caso_6.txt");
	inicio = clock();
	MergeSort(&teste);
	fim = clock();
	tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
	printf("Tempo total merge: %lf\n", tempo_execucao);
	desaloca_lista(teste);
}

void entradas_crescentes(){
	
}

void entradas_decrescentes(){
	
}

void entradas_iguais(){
	
}

void entradas_pior_caso(){
	
}

