#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "lista.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "maximos.h"
#include "radixsort_lista.h"
#include <windows.h>
#include <psapi.h>
#include <list>

int ler_entrada(lista * l, char * arq);//funcao para ler uma entrada de a partir de um arquivo com seu endereco passado por parâmetro
void provaDeOrdenacao();//Mostra que a saída de todos os algoritmos são iguais e ordenadas
void gera_relatorios();//executa os algoritmos usando um tipo de entrada dentro de um diretorio passados por parametro
int lerEntradaCPP(std::list<unsigned long long>& entradaCPP, char * arq);//le entrada para a lista nativa do C++
void cppSortAux(std::list<unsigned long long>& entradaCPP, lista * l);//auxiliar para marcar o tempo do std::sort
int comparaString(char * str1, char * str2);//funcao auxiliar para comparar duas strings passadas por parametro

int main(){//teste.txt
	//provaDeOrdenacao();
	for(int i = 0; i < 10; i++){
		printf("Iteracao %d\n", i+1);
		gera_relatorios();
		Sleep(5000);
	}

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

void provaDeOrdenacao(){
	lista * e1 = inicia_lista();
	lista * e2 = inicia_lista();
	lista * e3 = inicia_lista();
	printf("Lendo entrada aleatoria 1 para testes\n");
	char * arq = (char *)".\\entradas_aleatorias\\entrada_aleatoria_1.txt";
	if(ler_entrada(e1,arq) != 1)//erro de referencia para as entradas existentes ou a memória do computador
	{
		printf("Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
		free(arq);
		finalizaLista(e1);
		exit(1);
	}
	printf("Quicksort...\n");
	quickSort(e1);
	if(ler_entrada(e2,arq) != 1)//erro de referencia para as entradas existentes ou a memória do computador
	{
		printf("Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
		finalizaLista(e1);
		finalizaLista(e2);
		free(arq);
		exit(1);
	}
	printf("Mergesort...\n");
	mergeSort(e2);
	if(ler_entrada(e3,arq) != 1)//erro de referencia para as entradas existentes ou a memória do computador
	{
		printf("Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
		finalizaLista(e1);
		finalizaLista(e2);
		free(arq);
		exit(1);
	}
	printf("Radixsort...\n");
	radix_lista(e3,1);
	no * prox1 = e1->raiz;
	no * prox2 = e2->raiz;
	no * prox3 = e3->raiz;
	while(prox1!=NULL){		
		if(prox1->n != prox2->n && prox1->n != prox3->n && prox2->n != prox3->n){
			printf("\n3 resultados diferentes\n");
			exit(1);
		}
		else if(prox1->n == prox2->n && prox1->n != prox3->n && prox2->n != prox3->n){
			printf("\nRadix incorreto\n");
			exit(1);
		}
		else if(prox1->n != prox2->n && prox1->n == prox3->n && prox2->n != prox3->n){
			printf("\nMerge incorreto\n");
			exit(1);
		}
		else if(prox1->n != prox2->n && prox1->n != prox3->n && prox2->n == prox3->n){
			printf("\nQuick incorreto\n");
			exit(1);
		}
		prox1 = prox1->prox;
		prox2 = prox2->prox;
		prox3 = prox3->prox;
	}
	printf("Algoritmos apresentaram a mesma saida, prova de ordenacao concluida!\n\n");
	finalizaLista(e1);
	finalizaLista(e2);
	finalizaLista(e3);
}

int comparaString(char * str1, char * str2){
	int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
    	if(str1[i] != str2[i])
    		return 0;
    	i++;
	}
	return 1;
}

void gera_relatorios(){	
	printf("Ordenando entradas:\n");
	
    FILE * info = fopen("cabecalho.txt", "r");//abre os cabeçalhos
    if(info == NULL){//se não existe o arquivo sai do programa
    	printf("Entradas ainda não criadas, favor executar o gera entradas!\n");
    	fclose(info);
    	exit(0);
	}
	CreateDirectory("dados", NULL);//cria o diretorio de relatorios se não existe
	int sucesso;
    FILE * p;//arquivo do relatorio dos algoritmos por comparação
    FILE * pr;//arquivo do relatorio dos algoritmos por comparação
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
		if(fgets(cab,256,info)==NULL || cab[0] == '\n'){
			free(cab);
			free(arq);
			free(diretorio);
			free(tipo);
			finalizaLista(entrada);
	    	fclose(info);
			return;
		}
		
		sscanf(cab, "%s %s %d %llu %llu", diretorio, tipo, &i, &tamanho, &maior_numero);
		qtd_digitos = conta_digitos(maior_numero-1);//maior numero é o limite superior da rand, logo -1 ex: 1000 = 3 e 1001 = 4
	    sprintf(arq, ".\\dados\\Relatorio_comparacao_%s_%llu.txt", tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
		p =  fopen(arq,"a");//abre o arquivo para adicionar dados da execucao
	    sprintf(arq, ".\\dados\\Relatorio_radix_%s_%llu.txt", tipo, tamanho);//cria um relatorio csv com dados das execucoes do radix para cada entrada de um certo tipo e tamanho: DigitosRadix;DigitosMaiorNumero;Tempo;Memoria
		pr =  fopen(arq,"a");//abre o arquivo para adicionar dados da execucao
		if(p == NULL){//caso o arquivo não possa ser criado qualquer motivo
			printf("1. Erro ao gerar o arquivo de relatório, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
			free(cab);
			free(arq);
			free(diretorio);
			free(tipo);
			finalizaLista(entrada);
	    	fclose(info);
	    	fclose(p);
	    	fclose(pr);
			exit(1);
		}
		
		sprintf(arq, ".\\entradas_%s\\entrada_%s_%d.txt", diretorio, tipo, i);//le todas as entradas de um dado tipo
		if(ler_entrada(entrada,arq) != 1)//erro de referencia para as entradas existentes ou a memória do computador
		{
			printf("2. Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
			free(cab);
			free(arq);
			free(diretorio);
			free(tipo);
			finalizaLista(entrada);
	    	fclose(info);
	    	fclose(p);
	    	fclose(pr);
			exit(1);
		}		
		printf("Entrada %s %d; Tamanho: %llu; Digitos do maior numero: %d;\n", tipo, i, tamanho, qtd_digitos);//cabecalho
				
		/**MERGESORT**/
		printf("Mergesort...");
		mergeSort(entrada);
		printf("Tempo total: %lf segundos\n", entrada->tempo);
		fprintf(p, "Mergesort;%d;%lf\n", qtd_digitos, entrada->tempo);
		
		/**QUICKSORT: nao executa para entradas crescentes e decrescentes**/
		if(!(comparaString(tipo, (char *)"crescente") || comparaString(tipo, (char *)"decrescente"))){
			if(ler_entrada(entrada,arq) != 1)//acabaram as entradas existentes ou a memória do computador
				if(ler_entrada(entrada,arq) != 1)//erro de referencia para as entradas existentes ou a memória do computador
				{
					printf("3. Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
					free(cab);
					free(arq);
					free(diretorio);
					free(tipo);
					finalizaLista(entrada);
			    	fclose(info);
			    	fclose(p);
	    			fclose(pr);
					exit(1);
				}			
			printf("Quicksort...");
			quickSort(entrada);
			printf("Tempo total: %lf segundos\n", entrada->tempo);
			fprintf(p, "Quicksort;%d;%lf\n",qtd_digitos, entrada->tempo);
		}
		else
			fprintf(p, "%Quicksort;d;%lf\n", qtd_digitos, 0.0);
		
		/**INTROSORT(std::sort) - utiliza estruturas do C++**/
		desaloca_lista(entrada);//limpa a entrada atual
		std::list<unsigned long long> entradaCPP;
		if(lerEntradaCPP(entradaCPP, arq) != 1)//acabaram as entradas existentes ou a memória do computador
		{
			printf("4. Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
			free(cab);
			free(arq);
			free(diretorio);
			free(tipo);
			finalizaLista(entrada);
			fclose(info);
			fclose(p);
	    	fclose(pr);
			exit(1);
		}
		printf("Introsort(std::sort)...");
		cppSortAux(entradaCPP, entrada);
		printf("Tempo total: %lf segundos\n", entrada->tempo);
		fprintf(p, "%Introsort(std::sort);%d;%lf\n", qtd_digitos, entrada->tempo);
		entradaCPP.clear();
		
		
		/**RADIXSORT: executa com quantidades de digito variando de 1 a 7.**/
		int d;//numero de digitos do Radixsort
		for(d = 1; d <=7; d++){//de 1 a 7 digitos - melhor caso na pior entrada possivel(valor calculado manualmente através da fórmula de desenpenho)
			if(ler_entrada(entrada,arq) != 1)//acabaram as entradas existentes ou a memória do computador
			{
				printf("5. Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
				free(cab);
				free(arq);
				free(diretorio);
				free(tipo);
				finalizaLista(entrada);
				fclose(info);
    			fclose(p);
	    		fclose(pr);
				exit(1);
			}
			printf("Radixsort para lista com d = %d...", d);
	    	sucesso = radix_lista(entrada,d);//executa o radix de lista para a entrada
			if(!sucesso){//sai do loop quando o radix falhar por falta de memoria
				printf("Falta de memoria\n");
				break;
			}
			if(d==1)//salva o radix com 1 digito no relatorio de comparacao com os algoritmos
				fprintf(p, "Radix;%d;%lf\n", qtd_digitos, entrada->tempo);
			printf("Tempo total: %lf segundos; Memoria usada: %lfMB\n", entrada->tempo, entrada->memoria);
			fprintf(pr, "%d;%d;%lf;%lf\n", d, qtd_digitos, entrada->tempo, entrada->memoria);
		}
	    fclose(p);
	    fclose(pr);
	    printf("\n");
	}
	free(cab);
	free(arq);
	free(diretorio);
	free(tipo);
	fclose(info);
	finalizaLista(entrada);
}

int lerEntradaCPP(std::list<unsigned long long>& entradaCPP, char * arq){
    printf("Lendo entrada...");
	FILE * p;
	p = fopen(arq, "r");
	if(p == NULL)//retorna -1 se o arquivo não existir
		return -1;
	char * n = (char*) malloc(22*sizeof(char));//22 tamanho maximo da entrada 20 do llu + \n + \0
	while(fgets(n,22,p)!=NULL){
		if(n[0]=='\n')//caso a linha esteja vazia sai do loop
			break;
		entradaCPP.push_back(strtoull(n,NULL,10));
	}
	free(n);
	fclose(p);		
	
	return 1;//retorna 1 para sucesso
}

void cppSortAux(std::list<unsigned long long>& entradaCPP, lista * l){
	//Variaveis para contar o tempo
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    
	entradaCPP.sort();
				
	QueryPerformanceCounter(&end);
	l->tempo = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;//salva o tempo em segundos
}	
