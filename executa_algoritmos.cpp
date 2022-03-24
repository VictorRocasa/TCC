#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h"
#include "merge_sort.h"
#include "insertion_sort.h"
#include "maximos.h"
#include "radixsort_lista.h"
#include <windows.h>

int ler_entrada(lista * l, char * arq);//funcao para ler uma entrada de a partir de um arquivo com seu endereco passado por parâmetro
void gera_relatorios();//executa os algoritmos usando um tipo de entrada dentro de um diretorio passados por parametro

int main(){//teste.txt
	gera_relatorios();

    return 0;
}

int ler_entrada(lista * l, char * arq){
	if(l->raiz!=NULL)
		desaloca_lista(l);
    printf("Lendo entrada...");
	FILE * p;
	p = fopen(arq, "r");
	if(p == NULL)//retorna -1 se o arquivo não existir
		return -1;
	char * n = (char*) malloc(22*sizeof(char));//22 tamanho maximo da entrada 20 do llu + \n + \0
	no * anterior = NULL;//no auxiliar que aponta para o último adicionado, para salvar tempo na hora de ler a entrada(adiciona novos nós direto no fim da lista)
	while(fgets(n,22,p)!=NULL){
		if(n[0]=='\n')//caso a linha esteja vazia sai do loop
			break;
		anterior = adiciona_no(l, anterior, strtoull(n,NULL,10));
		if(anterior == NULL){
			fclose(p);
			return 0;//caso a memoria acabe retorna 0
		}
	}
	fclose(p);
	return 1;//retorna 1 para sucesso
}

void gera_relatorios(){
	
    FILE * info = fopen("cabecalho.txt", "r");//abre os cabeçalhos
    if(info == NULL){//se não existe o arquivo sai do programa
    	printf("Entradas ainda não criadas, favor executar o gera entradas!\n");
    	exit(0);
	}
	CreateDirectory("dados", NULL);//cria o diretorio de relatorios se não existe
	int sucesso;
    FILE * p;//arquivo do relatorio
    lista * entrada;//lista que será usada para guardar as entradas e depois ser ordenada
    char * cab = (char*)malloc(256*sizeof(char));//string do cabecalho
    char * diretorio = (char*)malloc(128*sizeof(char));//nome do diretorio do tipo da entrada para gerar o endereco
    char * tipo = (char*)malloc(128*sizeof(char));//nome dodo tipo da entrada para gerar o endereco
    char * arq = (char*)malloc(256*sizeof(char));//string de arquivo
    unsigned long long tamanho;//tamanho da entrada
    unsigned long long maior_numero;//numero de digitos do maior numero da entrada
	int i = 0;//numero da entrada
	
	while(1){		
		if(fgets(cab,256,info)==NULL)
			return;
			
		sscanf(cab, "%s %s %d %llu %llu", diretorio, tipo, &i, &tamanho, &maior_numero);
		lista * entrada = cria_lista(tamanho, conta_digitos(maior_numero-1));
	    sprintf(arq, ".\\dados\\relatorio_%s_%d.txt", diretorio, i);//cria um relatorio para cada entrada(armazenara os dados por algoritmo)
	    p =  fopen(arq,"w");//recria o arquivo
		p =  fopen(arq,"a");
		if(p == NULL){//caso o arquivo não possa ser criado qualquer motivo
			printf("ERRO DE LEITURA DE ARQUIVO RELATORIO NA FUNCAO DE RELATORIO DE ENTRADAS ALEATORIAS!");
			exit(1);
		}
		
		printf("Entrada %s %d\n", tipo, i);
		sprintf(arq, ".\\entradas_%s\\entrada_%s_%d.txt", diretorio, tipo, i);//le todas as entradas de um dado tipo
		if(ler_entrada(entrada,arq) != 1)//acabaram as entradas existentes ou a memória do computador
		{
			printf("O computador não possui memória para comportar a entrada lida, tente novamente mais tarde\n");
			free(cab);
			free(arq);
			free(diretorio);
			free(tipo);
			finalizaLista(entrada);
			fclose(info);
			exit(1);
		}
		
		fprintf(p, "Entrada %s %d; Tamanho: %llu; Digitos do maior numero: %d;\n", tipo, i, entrada->tamanho, entrada->digitos_maior_numero);//cabecalho relatorio
		
		/**OUTROS ALGORITMOS**/
		
		int d = 1;//numero de digitos do Radixsort
	    double primeiro = -1;//variável para salvar o tempo da primeira iteração do Radixsort
		while(1){
			/*
				le entrada de novo
			}*/
			printf("Executando Radixsort para lista com d = %d...\n", d);
	    	sucesso = radix_lista(entrada,d);//executa o radix de lista para a entrada
			if(!sucesso)//sai do loop quando o radix falhar por falta de memoria
				break;
			fprintf(p, "Tempo radix lista com d = %d: %lf; Memoria usada(MB): %lfMB;\n", d, entrada->tempo, entrada->memoria);
			if(primeiro == -1)//salva o tempo da execucao com um digito
				primeiro = entrada->tempo;
			else if(primeiro < entrada->tempo)//se ouver perda de desempenho em relacao a execucao com um digito, sai do loop
				break;
			d++;
		}
		i++;
		fclose(p);
		finalizaLista(entrada);
	}
	free(cab);
	free(arq);
	free(diretorio);
	free(tipo);
	fclose(info);
}
