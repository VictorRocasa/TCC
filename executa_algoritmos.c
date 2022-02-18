#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h" 
#include "merge_sort.h"
#include "insertion_sort.h"
#include "maximos.h"
#include "radixsort_lista.h"

int conta_digitos(unsigned long long n);//funcao para contar o numero de digitos de um numero
lista * ler_entrada(char * arq);//funcao para ler uma entrada de a partir de um arquivo com seu endereco passado por parâmetro
unsigned long long * ler_entrada_vetor(char * arq);//funcao para ler uma entrada a partir de um arquivo e criar um vetor para ela
void entradas_aleatorias();//executa os algoritmos usando entradas aleatorias
void entradas_crescentes();//executa os algoritmos usando entradas crescentes
void entradas_decrescentes();//executa os algoritmos usando entradas decrescentes
void entradas_iguais();//executa os algoritmos usando entradas iguais
void entradas_pior_caso();//executa os algoritmos usando entradas pior caso

int main(){//teste.txt
	entradas_aleatorias();
	
    return 0;
}

lista * ler_entrada(char * arq){
	FILE * p;
	p = fopen(arq, "r");
	if(p == NULL)
		return NULL;//Caso o arquivo não exista retorna NULL
	char * n = malloc(22*sizeof(char));//22 tamanho maximo da entrada 20 do llu + \n + \0
	lista * l = cria_lista();
	fgets(n,22,p);
	l->tamanho = strtoull(n,NULL,10);
	fgets(n,22,p);
	l->digitos_maior_numero = conta_digitos(strtoull(n,NULL,10)) -1;
	no * anterior = NULL;//no auxiliar que aponta para o último adicionado, para salvar tempo na hora de ler a entrada(adiciona novos nós direto no fim da lista)
	while(fgets(n,22,p)!=NULL){
		if(n[0]=='\n')//caso a linha esteja vazia sai do loop
			break;
		anterior = adiciona_no(l, anterior, strtoull(n,NULL,10));
		if(anterior == NULL){
			fclose(p);			
			return NULL;//caso a memoria acabe retorna NULL
		}
	}
	fclose(p);
	return l;
}

unsigned long long * ler_entrada_vetor(char * arq){
	FILE * p;
	p = fopen(arq, "r");
	if(p == NULL)
		return NULL;//Caso o arquivo não exista retorna NULL
	char * n = malloc(22*sizeof(char));//22 tamanho maximo da entrada 20 do llu + \n + \0
	fgets(n,22,p);
	unsigned long long * entrada = (unsigned long long*)malloc(strtoull(n,NULL,10)*sizeof(unsigned long long));
	if(entrada == NULL){
		fclose(p);			
		return NULL;//caso a memoria acabe retorna NULL
	}
	fgets(n,22,p);
	unsigned long long i = 0;
	while(fgets(n,22,p)!=NULL){
		if(n[0]=='\n')//caso a linha esteja vazia sai do loop
			break;
		entrada[i] = strtoull(n,NULL,10);
		i++;
	}
	fclose(p);
	return entrada;
}

void entradas_aleatorias(){
	double tempo_execucao;
	// = clock(); //pegar o tempo de clock
	// = (double)(fim - inicio) / CLOCKS_PER_SEC; - tempo para double
    FILE * p;
    p =  fopen(".\\dados\\relatorio_aleatorias.txt","w");
    p =  fopen(".\\dados\\relatorio_aleatorias.txt","a");
    char * arq = (char*)malloc(256*sizeof(char));
	if(p == NULL){
		printf("ERRO DE LEITURA DE ARQUIVO NA FUNCAO DE ENTRADAS ALEATORIAS!");
		exit(1);
	}
	lista * entrada;
	int i = 1;//numero da entrada
	clock_t inicioI; 
	clock_t fimI; 
	clock_t inicioQ; 
	clock_t fimQ; 
	clock_t inicioRV; 
	clock_t fimRV; 
	clock_t inicioRL; 
	clock_t fimRL; 
	unsigned long long * ev;
	while(1){
		printf("Lendo entrada aleatoria %d...\n", i);
    	sprintf(arq, ".\\entradas_aleatorias\\entrada_aleatoria_%d.txt", i);//le todas as entradas de um dado tipo
		//printf("Executando Insertionsort..\n");
		//entrada = ler_entrada(arq);
		//if(entrada == NULL)//acabaram as entradas existentes ou a memória do computador
		//	break;
    	//inicioI = clock();
    	//entrada->raiz = insertion(&entrada->raiz);//executa o insertion para a entrada
		//fimI = clock();
		//entrada = desaloca_lista(entrada);//desaloca a lista para ler novamente
		//printf("Executando Quicksort..\n");
		//entrada = ler_entrada(arq);
		//if(entrada == NULL)//acabaram as entradas existentes ou a memória do computador
		//	break;
    	//inicioQ = clock();
    	//entrada->raiz = (no*)quickSort(&entrada->raiz);//executa o quick para a entrada
		//fimQ = clock();
		//entrada = desaloca_lista(entrada);//desaloca para dar sequencia
		//printf("Executando Radixsort para vetor..\n");
		//ev = ler_entrada_vetor(arq);
		//if(entrada == NULL)//acabaram as entradas existentes ou a memória do computador
		//	break;
    	//inicioRV = clock();
    	//radixsort(ev, entrada->tamanho);//executa o radix tradicional para a entrada
		//fimRV = clock();
		//free(ev);
		printf("Executando Radixsort para lista...\n");
		entrada = ler_entrada(arq);
		if(entrada == NULL)//acabaram as entradas existentes ou a memória do computador
			break;
    	inicioRL = clock();
    	radix_lista(entrada,5);//executa o radix de lista para a entrada
		fimRL = clock();
		fprintf(p, "Entrada aleatoria %d; Tamanho: %llu; Digitos do maior numero: %d;\n", i, entrada->tamanho, entrada->digitos_maior_numero);
		fprintf(p, /*"Tempo Insertion: %lf; Tempo quick: %lf; "Tempo radix vetor: %lf; */"Tempo radix lista: %lf;\n\n", /*(double)((fimI - inicioI) / CLOCKS_PER_SEC), (double)((fimQ - inicioQ) / CLOCKS_PER_SEC)), (double)((fimRV - inicioRV) / CLOCKS_PER_SEC), */(double)((fimRL - inicioRL) / CLOCKS_PER_SEC));     
		i++;
		entrada = desaloca_lista(entrada);//desaloca para dar sequencia
	}
	fclose(p);	
}

void entradas_crescentes(){
	
}

void entradas_decrescentes(){
	
}

void entradas_iguais(){
	
}

void entradas_pior_caso(){
	
}

