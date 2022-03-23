#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h"
#include "merge_sort.h"
#include "insertion_sort.h"
#include "maximos.h"
#include "radixsort_lista.h"
#include <windows.h>
#include "flag_sort.h"
#include <psapi.h>

lista * ler_entrada(char * arq);//funcao para ler uma entrada de a partir de um arquivo com seu endereco passado por parâmetro
unsigned long long * ler_entrada_vetor(char * arq);//funcao para ler uma entrada a partir de um arquivo e criar um vetor para ela
void gera_relatorio_radix(char * diretorio, char * tipo);//executa os algoritmos usando um tipo de entrada dentro de um diretorio passados por parametro

int main(){//teste.txt
	gera_relatorio_radix((char*) "aleatorias", (char*) "aleatoria");
	gera_relatorio_radix((char*) "crescentes", (char*) "crescente");
	gera_relatorio_radix((char*) "decrescentes", (char*) "decrescente");
	gera_relatorio_radix((char*) "iguais", (char*) "igual");
	gera_relatorio_radix((char*) "complexas", (char*) "complexa");

    return 0;
}

lista * ler_entrada(char * arq){
    printf("Lendo entrada...");
	FILE * p;
	p = fopen(arq, "r");
	if(p == NULL)
		return (lista *)-1;//Caso o arquivo não exista retorna NULL
	char * n = (char*) malloc(22*sizeof(char));//22 tamanho maximo da entrada 20 do llu + \n + \0
	lista * l = cria_lista();
	fgets(n,22,p);
	l->tamanho = strtoull(n,NULL,10);
	fgets(n,22,p);
	l->digitos_maior_numero = conta_digitos(strtoull(n,NULL,10)-1);//-1 pois o maior numero e o limite superior da rand()
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
	char * n = (char*) malloc(22*sizeof(char));//22 tamanho maximo da entrada 20 do llu + \n + \0
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

void gera_relatorio_radix(char * diretorio, char * tipo){
	double tempo_execucao;
    char * arq = (char*)malloc(256*sizeof(char));
	lista * entrada;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double tempo;
    double memoria;
	unsigned long long * ev;
	int sucesso;
	CreateDirectory("dados", NULL);//cria o diretorio de relatorios se nao existir
	int i = 1;//numero da entrada
    FILE * p;//arquivo do relatorio
	while(1){
	    sprintf(arq, ".\\dados\\relatorio_%s_%d.txt", diretorio, i);//cria um relatorio para cada entrada(armazenara os dados por algoritmo)
	    p =  fopen(arq,"w");//recria o arquivo
		p =  fopen(arq,"a");
		if(p == NULL){//caso o arquivo não possa ser criado qualquer motivo
			printf("ERRO DE LEITURA DE ARQUIVO RELATORIO NA FUNCAO DE RELATORIO DE ENTRADAS ALEATORIAS!");
			exit(1);
		}
		printf("Entrada %s %d\n", tipo, i);
		sprintf(arq, ".\\entradas_%s\\entrada_%s_%d.txt", diretorio, tipo, i);//le todas as entradas de um dado tipo
		entrada = ler_entrada(arq);
		if(entrada == (lista *)-1)//acabaram as entradas existentes ou a memória do computador
		{
			printf("Entrada inexistente!\n");
			break;
		}
		else if(entrada == NULL){
			printf("Memoria esgotada!\n");
			entrada = desaloca_lista(entrada);
			break;
		}
		fprintf(p, "Entrada %s %d; Tamanho: %llu; Digitos do maior numero: %d;\n", tipo, i, entrada->tamanho, entrada->digitos_maior_numero);//cabecalho relatorio
		printf("Executando mergesort para lista...\n");
	    QueryPerformanceFrequency(&frequency);
	    QueryPerformanceCounter(&start);
		MergeSort(&entrada->raiz);
		QueryPerformanceCounter(&end);
		fprintf(p, "Tempo mergesort lista: %lf;\n", tempo);
		/**OUTROS ALGORITMOS**/
		entrada = desaloca_lista(entrada);//desaloca para dar sequencia
		int d = 1;//numero de digitos do Radixsort
	    double primeiro = -1;
		while(1){
			entrada = ler_entrada(arq);
			if(entrada == (lista *)-1)//acabaram as entradas existentes ou a memória do computador
			{
				printf("Entrada inexistente!\n");
				delete(p);//apaga o ultimo relatorio por que sua entrada nao existe
				break;
			}
			else if(entrada == NULL){
				printf("Memoria esgotada!\n");
				delete(p);//apaga o ultimo relatorio por que sua entrada nao pode ser ordenada
				break;
			}
			printf("Executando Radixsort para lista com d = %d...\n", d);
		    QueryPerformanceFrequency(&frequency);
		    QueryPerformanceCounter(&start);
	    	sucesso = radix_lista(entrada,d);//executa o radix de lista para a entrada
		    QueryPerformanceCounter(&end);
			if(!sucesso)//sai do loop quando o radix falhar por falta de memoria
				break;
		    tempo = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
		    memoria = entrada->picoMemoria;
			fprintf(p, "Tempo radix lista com d = %d: %lf; Memoria usada(MB): %lfMB;\n", d, tempo, memoria);
			entrada = desaloca_lista(entrada);//desaloca para dar sequencia
			if(primeiro == -1)//salva o tempo da execucao com um digito
				primeiro = tempo;
			else if(primeiro < tempo)//se ouver perda de desempenho em relacao a execucao com um digito, sai do loop
				break;
			d++;
		}
		i++;
		fclose(p);
	}
	free(arq);
}
