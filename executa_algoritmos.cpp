#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h"
#include "gfg_merge.h"
//#include "merge_sort.h"
#include "quick_sort.h"
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
			free(n);
			return 0;//caso a memoria acabe retorna 0
		}
	}
	free(n);
	fclose(p);
	return 1;//retorna 1 para sucesso
}

void gera_relatorios(){
	
    FILE * info = fopen("cabecalho.txt", "r");//abre os cabeçalhos
    if(info == NULL){//se não existe o arquivo sai do programa
    	printf("Entradas ainda não criadas, favor executar o gera entradas!\n");
    	fclose(info);
    	exit(0);
	}
	CreateDirectory("dados", NULL);//cria o diretorio de relatorios se não existe
	int sucesso;
    FILE * p;//arquivo do relatorio
    char * cab = (char*)malloc(256*sizeof(char));//string do cabecalho
    char * diretorio = (char*)malloc(128*sizeof(char));//nome do diretorio do tipo da entrada para gerar o endereco
    char * tipo = (char*)malloc(128*sizeof(char));//nome dodo tipo da entrada para gerar o endereco
    char * arq = (char*)malloc(256*sizeof(char));//string de arquivo
    unsigned long long tamanho;//tamanho da entrada
    unsigned long long maior_numero;//numero de digitos do maior numero da entrada
    int qtd_digitos;
	int i;//numero da entrada
    lista * entrada = inicia_lista();//cabeca da lista que será usada para guardar as entradas e depois ser ordenada. Serve para coletar informacoes das funcoes	
	while(1){		
		if(fgets(cab,256,info)==NULL)
			return;
		sscanf(cab, "%s %s %d %llu %llu", diretorio, tipo, &i, &tamanho, &maior_numero);
		qtd_digitos = conta_digitos(maior_numero-1);//maior numero é o limite superior da rand, logo -1 ex: 1000 = 3 e 1001 = 4
	    sprintf(arq, ".\\dados\\relatorio_%s_%d.txt", diretorio, i);//cria um relatorio para cada entrada(armazenara os dados por algoritmo)
	    p =  fopen(arq,"w");//recria o arquivo
		p =  fopen(arq,"a");
		if(p == NULL){//caso o arquivo não possa ser criado qualquer motivo
			printf("Erro ao gerar o arquivo de relatório, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
			free(cab);
			free(arq);
			free(diretorio);
			free(tipo);
			finalizaLista(entrada);
	    	fclose(info);
	    	fclose(p);
			exit(1);
		}
		
		printf("Entrada %s %d\n", tipo, i);
		sprintf(arq, ".\\entradas_%s\\entrada_%s_%d.txt", diretorio, tipo, i);//le todas as entradas de um dado tipo
		if(ler_entrada(entrada,arq) != 1)//acabaram as entradas existentes ou a memória do computador
		{
			printf("Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
			free(cab);
			free(arq);
			free(diretorio);
			free(tipo);
			finalizaLista(entrada);
	    	fclose(info);
	    	fclose(p);
			exit(1);
		}
		
		fprintf(p, "Entrada %s %d; Tamanho: %llu; Digitos do maior numero: %d;\n", tipo, i, tamanho, qtd_digitos);//cabecalho relatorio
		
		/**OUTROS ALGORITMOS**/
		printf("Quicksort...");
		quickSort(entrada);
		printf("Tempo total: %lf segundos; Memoria: %lf\n", entrada->tempo, entrada->memoria);
		
		int d;//numero de digitos do Radixsort
	    //double primeiro = -1;//variável para salvar o tempo da primeira iteração do Radixsort
		for(d = 1; d <=7; d++){//de 1 a 7 digitos - melhor caso na pior entrada possivel(valor calculado manualmente através da fórmula de desenpenho)
			if(ler_entrada(entrada,arq) != 1)//acabaram as entradas existentes ou a memória do computador
			{
				printf("Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
				free(cab);
				free(arq);
				free(diretorio);
				free(tipo);
				finalizaLista(entrada);
				fclose(info);
    			fclose(p);
				exit(1);
			}
		
			printf("Radixsort para lista com d = %d...", d);
	    	sucesso = radix_lista(entrada,d);//executa o radix de lista para a entrada
			if(!sucesso){//sai do loop quando o radix falhar por falta de memoria
				printf("Falta de memoria\n");
				break;
			}
			printf("Tempo total: %lf segundos\n", entrada->tempo);
			fprintf(p, "Tempo radix lista com d = %d: %lf; Memoria usada(MB): %lfMB;\n", d, entrada->tempo, entrada->memoria);
		}
		fclose(p);
	}
	free(cab);
	free(arq);
	free(diretorio);
	free(tipo);
	fclose(info);
	finalizaLista(entrada);
}
