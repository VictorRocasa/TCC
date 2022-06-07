#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <psapi.h>
#include <iterator>
#include <list>
#include "lista.h"
#include "maximos.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "radixsort_lista.h"
#include <math.h>

int ler_entrada(lista * l, char * arq);//funcao para ler uma entrada de a partir de um arquivo com seu endereco passado por par�metro
void provaDeOrdenacao(char * arq);//Mostra que a sa�da de todos os algoritmos s�o iguais e ordenadas
void gera_relatorios(unsigned long long tamanhoRequerido, char * tipoRequeridom, int rep);//executa os algoritmos usando um tipo de entrada dentro de um diretorio passados por parametro
int lerEntradaCPP(std::list<unsigned long long>& entradaCPP, char * arq);//le entrada para a lista nativa do C++
void cppSortAux(std::list<unsigned long long>& entradaCPP, lista * l);//auxiliar para marcar o tempo do std::sort
void normalizarResultados(int aleatorias);//funcao que gera relatorios com as medias dos relatorios gerados pelas diversas execucoes da funcao anterior
int comparaString(char * str1, char * str2);//funcao auxiliar para comparar duas strings passadas por parametro

int main(){//teste.txt
	/*planop de testes final:
	dia 1 - todas as entradas nao aleatorias
	dia 2 e 3 - 5 entradas aleatorias de tamanhos 10^6 e 10^7
	dia 4 a 14 - entradas aleatorias de tamanho 10^8
	*/
	/*dia 1
	for(int i = 1; i <= 10; i++){//loop para gerar 10 relatorios
		gera_relatorios(0llu, (char*)"igual", i);//executa todas as entradas complexas de tamanho = 100000000/
		gera_relatorios(0llu, (char*)"crescente", i);//executa todas as entradas complexas de tamanho = 100000000/
		gera_relatorios(0llu, (char*)"decrescente", i);//executa todas as entradas complexas de tamanho = 100000000/
		gera_relatorios(0llu, (char*)"complexa", i);//executa todas as entradas complexas de tamanho = 100000000/
	}*/
	/*dia 2 - 3
	for(int i = 1; i <= 5; i++){
		gera_relatorios(1000000llu, (char*)"aleatoria", i);//executa todas as entradas complexas de tamanho = 100000000/
		gera_relatorios(10000000llu, (char*)"aleatoria", i);//executa todas as entradas complexas de tamanho = 100000000/
	}
  	system("c:\\windows\\system32\\shutdown /s");*/
  	//normalizarResultados(1);
  	//provaDeOrdenacao((char *)".\\entradas_aleatorias\\entrada_aleatoria_100.txt");
  	//provaDeOrdenacao((char *)".\\entradas_crescentes\\entrada_crescente_1.txt");
  	normalizarResultados(0);
    return 0;
}

int ler_entrada(lista * l, char * arq){
	if(l->raiz!=NULL)
		desaloca_lista(l);
    printf("Lendo entrada...");
	FILE * p;
	p = fopen(arq, "r");
	if(p == NULL)//retorna -1 se o arquivo n�o existir
		return -1;
	char * n = (char*) malloc(22*sizeof(char));//22 tamanho maximo da entrada 20 do llu + \n + \0
	no * anterior = NULL;//no auxiliar que aponta para o �ltimo adicionado, para salvar tempo na hora de ler a entrada(adiciona novos n�s direto no fim da lista)
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

void provaDeOrdenacao(char * arq){
	//lista * e1 = inicia_lista();
	//lista * e2 = inicia_lista();
	lista * e3 = inicia_lista();
	printf("Lendo entrada para testes\n");
	/*if(ler_entrada(e1,arq) != 1)//erro de referencia para as entradas existentes ou a mem�ria do computador
	{
		printf("Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
		free(arq);
		finalizaLista(e1);
		exit(1);
	}
	printf("Quicksort...\n");
	quickSort(e1);
	if(ler_entrada(e2,arq) != 1)//erro de referencia para as entradas existentes ou a mem�ria do computador
	{
		printf("Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
		finalizaLista(e1);
		finalizaLista(e2);
		free(arq);
		exit(1);
	}
	printf("Mergesort...\n");
	mergeSort(e2);
	*/if(ler_entrada(e3,arq) != 1)//erro de referencia para as entradas existentes ou a mem�ria do computador
	{
		printf("Erro ao carregar a lista, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
		//finalizaLista(e1);
		//finalizaLista(e2);
		free(arq);
		exit(1);
	}
	printf("Radixsort...\n");
	radix_lista(e3,8);
	
	std::list<unsigned long long> entradaCPP;
	lerEntradaCPP(entradaCPP, arq);
	printf("Mergesort2(std::sort)...");
	entradaCPP.sort();
	no * prox = e3->raiz;
	int i = 1; 
    std::list<unsigned long long>::iterator j = entradaCPP.begin();
	while(prox!=NULL){
		if(prox->n != *j){
			printf("Erro no indice %d!\n", i);
			printf("%llu != %llu", prox->n, *j);
			getchar();
		}
		prox = prox->prox;
		j++;
		i++;
	}
	entradaCPP.clear();
	
	
	/*no * prox1 = e1->raiz;
	no * prox2 = e2->raiz;
	no * prox3 = e3->raiz;
	while(prox1!=NULL){		
		if(prox1->n != prox2->n && prox1->n != prox3->n && prox2->n != prox3->n){
			printf("\n3 resultados diferentes\n");
			exit(1);
		}
		else if(prox1->n == prox2->n && prox1->n != prox3->n && prox2->n != prox3->n){
			printf("\nRadix incorreto\n");
			printf("%llu != %llu e %llu", prox3->n, prox2->n, prox1->n);
			getchar();
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
	finalizaLista(e2);*/
	finalizaLista(e3);
}

void gera_relatorios(unsigned long long tamanhoRequerido, char * tipoRequerido, int rep){	
	printf("Ordenando entradas:\n");
	
    FILE * info = fopen("cabecalho.txt", "r");//abre os cabe�alhos
    if(info == NULL){//se n�o existe o arquivo sai do programa
    	printf("Entradas ainda n�o criadas, favor executar o gera entradas!\n");
    	fclose(info);
    	exit(0);
	}
	CreateDirectory("dados", NULL);//cria o diretorio de relatorios se n�o existe
	int sucesso;
    FILE * p;//arquivo do relatorio dos algoritmos por compara��o
    FILE * pr;//arquivo do relatorio dos algoritmos por compara��o
    char * cab = (char*)malloc(256*sizeof(char));//string do cabecalho
    char * diretorio = (char*)malloc(128*sizeof(char));//nome do diretorio do tipo da entrada para gerar o endereco
    char * tipo = (char*)malloc(128*sizeof(char));//nome dodo tipo da entrada para gerar o endereco
    char * arq = (char*)malloc(256*sizeof(char));//string de arquivo
    unsigned long long tamanho;//tamanho da entrada
    int qtd_digitos;
	int i;//numero da entrada
    lista * entrada = inicia_lista();//cabeca da lista que ser� usada para guardar as entradas e depois ser ordenada. Serve para coletar informacoes das funcoes	
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
		
		sscanf(cab, "%s %s %d %llu %d", diretorio, tipo, &i, &tamanho, &qtd_digitos);
		if((tamanho == tamanhoRequerido || tamanhoRequerido == 0) && (comparaString(tipoRequerido,tipo) || tipoRequerido == NULL)){//executa apenas as entradas de tamanho e tipo especificado. 0 ignora tamanho e NULL tipo
		    sprintf(arq, ".\\dados\\Relatorio_comparacao_%s_%llu.txt", tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
			p =  fopen(arq,"a");//abre o arquivo para adicionar dados da execucao
		    sprintf(arq, ".\\dados\\Relatorio_radix_%s_%llu.txt", tipo, tamanho);//cria um relatorio csv com dados das execucoes do radix para cada entrada de um certo tipo e tamanho: DigitosRadix;DigitosMaiorNumero;Tempo;Memoria
			pr =  fopen(arq,"a");//abre o arquivo para adicionar dados da execucao
			if(p == NULL){//caso o arquivo n�o possa ser criado qualquer motivo
				printf("1. Erro ao gerar o arquivo de relat�rio, tente novamente mais tarde. Se o problema persistir contate um desenvolvedor!\n");
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
			if(ler_entrada(entrada,arq) != 1)//erro de referencia para as entradas existentes ou a mem�ria do computador
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
			printf("Iteracao %d, entrada %s %d; Tamanho: %llu; Quantidade de digitos: %d;\n", rep, tipo, i, tamanho, qtd_digitos);//cabecalho
					
			/**MERGESORT**/
			printf("Mergesort...");
			mergeSort(entrada);
			printf("Tempo total: %lf segundos\n", entrada->tempo);
			fprintf(p, "1;%d;%lf\n", qtd_digitos, entrada->tempo);
			
			/**QUICKSORT: nao executa para entradas crescentes e decrescentes**/
			if(!(comparaString(tipo, (char *)"crescente") || comparaString(tipo, (char *)"decrescente"))){
				if(ler_entrada(entrada,arq) != 1)//acabaram as entradas existentes ou a mem�ria do computador
					if(ler_entrada(entrada,arq) != 1)//erro de referencia para as entradas existentes ou a mem�ria do computador
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
				fprintf(p, "2;%d;%lf\n",qtd_digitos, entrada->tempo);
			}
			else
				fprintf(p, "2;d;%lf\n", qtd_digitos, 0.0);
			
			/**Mergesort2(std::sort) - utiliza estruturas do C++**/
			desaloca_lista(entrada);//limpa a entrada atual
			std::list<unsigned long long> entradaCPP;
			if(lerEntradaCPP(entradaCPP, arq) != 1)//acabaram as entradas existentes ou a mem�ria do computador
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
			printf("Mergesort2(std::sort)...");
			cppSortAux(entradaCPP, entrada);
			printf("Tempo total: %lf segundos\n", entrada->tempo);
			fprintf(p, "3;%d;%lf\n", qtd_digitos, entrada->tempo);
			entradaCPP.clear();
			
			
			/**RADIXSORT: executa com quantidades de digito variando de 1 a 7.**/
			int d;//numero de digitos do Radixsort
			for(d = 1; d <=8; d++){//de 1 a 7 digitos - melhor caso na pior entrada possivel(valor calculado manualmente atrav�s da f�rmula de desenpenho)
				if(ler_entrada(entrada,arq) != 1)//acabaram as entradas existentes ou a mem�ria do computador
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
					fprintf(p, "4;%d;%lf\n", qtd_digitos, entrada->tempo);
				printf("Tempo total: %lf segundos; Memoria usada: %lfMB\n", entrada->tempo, entrada->memoria);
				fprintf(pr, "%d;%d;%lf;%lf\n", d, qtd_digitos, entrada->tempo, entrada->memoria);
			}
		    fclose(p);
		    fclose(pr);
		    printf("\n");
		}
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
	if(p == NULL)//retorna -1 se o arquivo n�o existir
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

void normalizarResultados(int aleatorias){
	printf("Normalizando resultados...\n");
	for(unsigned long long tamanho = MINT; tamanho <= MAXT; tamanho *=10){
		char * arq = (char*)malloc(256*sizeof(char*));//variavel para ler arquivos
		char * linha = (char*)malloc(256*sizeof(char*));//variavel para ler linhas de arquivos
	    char * tipo = (char*)malloc(128*sizeof(char*));//nome dodo tipo da entrada para gerar o endereco
	    char * diretorio = (char*)malloc(128*sizeof(char*));//nome dodo tipo da entrada para gerar o endereco
		sprintf(diretorio, "Final_%llu", tamanho);//cria um diretorio para cada tamanho
		CreateDirectory(diretorio, NULL);//cria o diretorio de relatorios finais se n�o existe
	    /**Normaliza entradas aleatorias**/
		sprintf(tipo, "aleatoria");
		printf("Lendo resultados da entrada %s de tamanho %llu.\n", tipo, tamanho);
		sprintf(arq, ".\\dados\\Relatorio_comparacao_%s_%llu.txt", tipo, tamanho);
		FILE * p = fopen(arq, "r");
	    
		if(!aleatorias)//pula a normalizacao das entradas aleatorias
	    	goto skip;
		if(p == NULL){
			printf("Nao existem dados para a entrada %s de tamanho %llu, favor executar o algoritmo de relatorio!\n", tipo, tamanho);
			fclose(p);
			free(linha);
			free(arq);
			free(tipo);
			return;
		}
		else{
			printf("Gerando relatorio normalizado para algoritmos de comparacao...");
			double tempo[4][20];//4 algoritmos e 20 digitos para salvar o tempo medio de cada algoritmo
			int media[4][20];//Conta o numero de vezes que determinada combinacao foi registrada para tirar media ao fim
			for(int i = 0; i < 4; i++)//zera a matriz e o vetor
				for(int j = 0; j < 20; j++){
					tempo[i][j] = 0.0;
					media[i][j] = 0;
				}
			while(1){//pecorre o arquivo salvando os tempos registrados por combinacao e a quantidade de vezes que cada combinacao ocorre
				if(fgets(linha,256,p)==NULL || linha[0] == '\n')
					break;
				double tempoAtual;//tempo do algoritmo atual
				int qtd_digitos;//quantidade de digitos do maior numero da entrada atual
				int algoritmo;//algoritmo usado
				sscanf(linha, "%d;%d;%lf", &algoritmo, &qtd_digitos, &tempoAtual);
				tempo[algoritmo-1][qtd_digitos-1] += tempoAtual;
				media[algoritmo-1][qtd_digitos-1]++;
			}
			printf("\n");
			fclose(p);	
			sprintf(arq, ".\\%s\\Relatorio_comparacao_%s_%llu.txt", diretorio, tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
			FILE * p = fopen(arq, "w");	
			fprintf(p, "Entrada %s de tamanho %llu\n\n", tipo, tamanho);
			for(int i = 0; i < 20; i++){
				fprintf(p, "Digitos do maior numero = %d, tamanho da amostra = %d\n", i+1, media[3][i]);
				fprintf(p, "Quicksort: %lf\n", tempo[1][i]/media[1][i]);
				fprintf(p, "Mergesort1: %lf\n", tempo[0][i]/media[0][i]);
				fprintf(p, "Mergesort2: %lf\n", tempo[2][i]/media[2][i]);
				fprintf(p, "Radix-base: %lf\n\n", tempo[3][i]/media[3][i]);
			}
			fprintf(p, "\nTabela comparacao aleatorias:\n");
			for(int i = 0; i < 20; i++){
				fprintf(p, "%d & ", i+1);
				fprintf(p, "%lf & ", tempo[1][i]/media[1][i]);
				fprintf(p, "%lf & ", tempo[0][i]/media[0][i]);
				fprintf(p, "%lf & ", tempo[2][i]/media[2][i]);
				fprintf(p, "%lf & ", tempo[3][i]/media[3][i]);
				fprintf(p, "0.00000 \\\\\n");
			}
			fprintf(p, "\n\nCoordenadas Latex Mergesort:\n");
			for(int i = 0; i < 20; i++){
				fprintf(p, "(%d,%lf)", i+1, tempo[0][i]/media[0][i]);
				if((i+1)%4==0)
					fprintf(p, "\n");
			}
			if(!comparaString(tipo, (char*)"crescente") && !comparaString(tipo, (char*)"decrescente")){
				fprintf(p, "\n\nCoordenadas Latex Quicksort:\n");
				for(int i = 0; i < 20; i++){
					fprintf(p, "(%d,%lf)", i+1,  tempo[1][i]/media[1][i]);
					if((i+1)%4==0)
						fprintf(p, "\n");
				}
			}
			fprintf(p, "\n\nCoordenadas Latex Mergesort2:\n");
			for(int i = 0; i < 20; i++){
				fprintf(p, "(%d,%lf)", i+1,  tempo[2][i]/media[2][i]);
				if((i+1)%4==0)
					fprintf(p, "\n");
			}
			fprintf(p, "\n\nCoordenadas Latex Radixsort:\n");
			for(int i = 0; i < 20; i++){
				fprintf(p, "(%d,%lf)", i+1, tempo[3][i]/media[3][i]);
				if((i+1)%4==0)
					fprintf(p, "\n");
			}
			fprintf(p, "\n\n");
			fclose(p);	
		}
	    /**Normaliza entradas aleatorias do radixsort**/
		sprintf(arq, ".\\dados\\Relatorio_radix_%s_%llu.txt", tipo, tamanho);
		p = fopen(arq, "r");
		if(p == NULL){
			printf("Nao existem dados para a entrada %s de tamanho %llu, favor executar o algoritmo de relatorio!\n", tipo, tamanho);
			fclose(p);
			free(linha);
			free(arq);
			free(tipo);
			return;
		}
		else{
			printf("Gerando relatorio normalizado para execucoes do Radixsort...");
			double tempo[8][20];//8 digitos e 20 digitos para salvar o tempo medio de cada algoritmo
			double memoria[8][20];//8 digitos e 20 digitos para salvar o tempo medio de cada algoritmo
			int media[8][20];//Conta o numero de vezes que determinada combinacao foi registrada para tirar media ao fim
			for(int i = 0; i < 8; i++)//zera a matriz e o vetor
				for(int j = 0; j < 20; j++){
					tempo[i][j] = 0.0;
					memoria[i][j] = 0.0;
					media[i][j] = 0;
				}
			while(1){//pecorre o arquivo salvando os tempos registrados por combinacao e a quantidade de vezes que cada combinacao ocorre
				if(fgets(linha,256,p)==NULL || linha[0] == '\n')
					break;
				double tempoAtual;//tempo do algoritmo atual
				double memoriaAtual;//memoria do algoritmo atual
				int qtd_digitos;//quantidade de digitos do maior numero da entrada atual
				int algoritmo;//algoritmo usado
				sscanf(linha, "%d;%d;%lf;%lf", &algoritmo, &qtd_digitos, &tempoAtual, &memoriaAtual);
				tempo[algoritmo-1][qtd_digitos-1] += tempoAtual;
				memoria[algoritmo-1][qtd_digitos-1] += memoriaAtual;
				media[algoritmo-1][qtd_digitos-1]++;
			}
			printf("\n");
			fclose(p);	
			sprintf(arq, ".\\%s\\Relatorio_radix_%s_%llu.txt", diretorio, tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
			FILE * p = fopen(arq, "w");	
			fprintf(p, "Entrada %s de tamanho %llu\n\n", tipo, tamanho);
			for(int i = 0; i < 20; i++){
				fprintf(p, "Digitos do maior numero = %d, tamanho da amostra = %d\n", i+1, media[6][i]);
				for(int j = 0; j < 8; j++){
					fprintf(p, "Radixsort(d = %d): %lf, usando %lfMB\n", j+1, tempo[j][i]/media[j][i], memoria[j][i]/media[j][i]);
				}
				fprintf(p, "\n");
			}
				
			fprintf(p, "\nTabela tempo:\nk & d = 1 & d = 2 & d = 3 &  d = 4 &  d = 5 &  d = 6 &  d = 7 & d = 8 \\\\\n\\midrule");		
			for(int i = 0; i < 20; i++)	{
				fprintf(p, "\n%d", i+1);
				for(int j = 0; j < 8; j++)
					fprintf(p, " & %lf", tempo[j][i]/media[j][i]);
				fprintf(p, " \\\\");
			}
				
			fprintf(p, "\n\nTabela memoria:\nk & d = 1 & d = 2 & d = 3 &  d = 4 &  d = 5 &  d = 6 &  d = 7 & d = 8 \\\\\n\\midrule");		
			for(int i = 0; i < 20; i++)	{
				fprintf(p, "\n%d", i+1);
				for(int j = 0; j < 8; j++)
					fprintf(p, " & %.1lf", memoria[j][i]/media[j][i]);
				fprintf(p, " \\\\");
			}
			
			fclose(p);	
		}
		
	    skip: 
	    /**Normaliza entradas iguais**/
		sprintf(tipo, "igual");
		printf("Lendo resultados da entrada %s de tamanho %llu.\n", tipo, tamanho);
		sprintf(arq, ".\\dados\\Relatorio_comparacao_%s_%llu.txt", tipo, tamanho);
		p = fopen(arq, "r");
		if(p == NULL){
			printf("Nao existem dados para a entrada %s de tamanho %llu, favor executar o algoritmo de relatorio!\n", tipo, tamanho);
			fclose(p);
			free(linha);
			free(arq);
			free(tipo);
			return;
		}
		else{
			printf("Gerando relatorio normalizado para algoritmos de comparacao...");
			double tempo[4][2];//4 algoritmos e 20 digitos para salvar o tempo medio de cada algoritmo
			int media[4][2];//Conta o numero de vezes que determinada combinacao foi registrada para tirar media ao fim
			int real = 20;//referencia da posicao do vetor
			for(int i = 0; i < 4; i++)//zera a matriz e o vetor
				for(int j = 0; j < 2; j++){
					tempo[i][j] = 0.0;
					media[i][j] = 0;
				}
			while(1){//pecorre o arquivo salvando os tempos registrados por combinacao e a quantidade de vezes que cada combinacao ocorre
				if(fgets(linha,256,p)==NULL || linha[0] == '\n')
					break;
				double tempoAtual;//tempo do algoritmo atual
				int qtd_digitos;//quantidade de digitos do maior numero da entrada atual
				int algoritmo;//algoritmo usado
				int ref;//referencia da posicao do vetor
				sscanf(linha, "%d;%d;%lf", &algoritmo, &qtd_digitos, &tempoAtual);
				if(qtd_digitos < 20){
					ref = 0;
					real = qtd_digitos;
				}
				else
					ref = 1;
					
				tempo[algoritmo-1][ref] += tempoAtual;
				media[algoritmo-1][ref]++;
			}
			
			printf("\n");
			fclose(p);	
			sprintf(arq, ".\\%s\\Relatorio_comparacao_%s_%llu.txt", diretorio, tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
			FILE * p = fopen(arq, "w");	
			fprintf(p, "Entrada %s de tamanho %llu\n\n", tipo, tamanho);
			for(int i = 0; i < 2; i++){
				fprintf(p, "Digitos do maior numero = %d, tamanho da amostra = %d\n", real, media[3][i]);
				fprintf(p, "Mergesort: %lf\n", tempo[0][i]/media[0][i]);
				fprintf(p, "Quicksort: %lf\n", tempo[1][i]/media[1][i]);
				fprintf(p, "Mergesort2(std::sort): %lf\n", tempo[2][i]/media[2][i]);
				fprintf(p, "Radixsort(d = 1): %lf\n\n", tempo[3][i]/media[3][i]);
					
				fprintf(p, "\nTabela latex da entrada de k = %d:\n", real);
				fprintf(p, "\\textit{Quicksort} & %lf \\\\\n", tempo[1][i]/media[1][i]);
				fprintf(p, "\\textit{Mergesort1} & %lf \\\\\n", tempo[0][i]/media[0][i]);
				fprintf(p, "\\textit{Mergesort2} & %lf \\\\\n",  tempo[2][i]/media[2][i]);
				fprintf(p, "\\textit{Radix-base} & %lf \\\\\n\n\n\n", tempo[3][i]/media[3][i]);
				real = 20;
			}
		}
		
	    /**Normaliza entradas iguais do radixsort**/
		sprintf(arq, ".\\dados\\Relatorio_radix_%s_%llu.txt", tipo, tamanho);
		p = fopen(arq, "r");
		if(p == NULL){
			printf("Nao existem dados para a entrada %s de tamanho %llu, favor executar o algoritmo de relatorio!\n", tipo, tamanho);
			fclose(p);
			free(linha);
			free(arq);
			free(tipo);
			return;
		}
		else{
			printf("Gerando relatorio normalizado para execucoes do Radixsort...");
			double tempo[8][2];//8 valores para d e 20 digitos para salvar o tempo medio de cada algoritmo
			double memoria[8][2];//8 valores para d e 20 digitos para salvar o tempo medio de cada algoritmo
			int real = 20;//referencia da posicao do vetor
			int media[8][2];//Conta o numero de vezes que determinada combinacao foi registrada para tirar media ao fim
			for(int i = 0; i < 8; i++)//zera a matriz e o vetor
				for(int j = 0; j < 2; j++){
					tempo[i][j] = 0.0;
					memoria[i][j] = 0.0;
					media[i][j] = 0;
				}
			while(1){//pecorre o arquivo salvando os tempos registrados por combinacao e a quantidade de vezes que cada combinacao ocorre
				if(fgets(linha,256,p)==NULL || linha[0] == '\n')
					break;
				double tempoAtual;//tempo do algoritmo atual
				double memoriaAtual;//memoria do algoritmo atual
				int ref;//referencia da posicao do vetor
				int qtd_digitos;//quantidade de digitos do maior numero da entrada atual
				int algoritmo;//algoritmo usado
				sscanf(linha, "%d;%d;%lf;%lf", &algoritmo, &qtd_digitos, &tempoAtual, &memoriaAtual);
				if(qtd_digitos < 20){
					ref = 0;
					real = qtd_digitos;
				}
				else
					ref = 1;
				tempo[algoritmo-1][ref] += tempoAtual;
				memoria[algoritmo-1][ref] += memoriaAtual;
				media[algoritmo-1][ref]++;
			}
			printf("\n");
			fclose(p);	
			sprintf(arq, ".\\%s\\Relatorio_radix_%s_%llu.txt", diretorio, tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
			FILE * p = fopen(arq, "w");	
			fprintf(p, "Entrada %s de tamanho %llu\n\n", tipo, tamanho);
			for(int i = 0; i < 2; i++){
				fprintf(p, "Digitos do maior numero = %d, tamanho da amostra = %d\n", real, media[6][i]);
				for(int j = 0; j < 8; j++){
					fprintf(p, "Radixsort(d = %d): %lf, usando %lfMB\n", j+1, tempo[j][i]/media[j][i], memoria[j][i]/media[j][i]);
				}
				fprintf(p, "\nTabela latex da entrada de k = %d:\n", real);
				fprintf(p, "%d & $10^%d$ & %d & %lf & - \\\\\n", 1, 1, (int)ceil(real/1), tempo[0][i]/media[0][i]);
				for(int j = 1; j < 8; j++)
					fprintf(p, "%d & $10^%d$ & %d & %lf & %.2lf \\\\\n", j+1, j+1, (int)ceil(real/(j+1.0)), tempo[j][i]/media[j][i], (tempo[0][i]/media[0][i])/(tempo[j][i]/media[j][i]));
				real = 20;
				fprintf(p, "\n\n\n\n");
			}			
			fclose(p);	
		}    
		
	    /**Normaliza outras entradas**/
	    int f = 0;
		sprintf(tipo, "complexa");
	    while(1){
			printf("Lendo resultados da entrada %s de tamanho %llu.\n", tipo, tamanho);
			sprintf(arq, ".\\dados\\Relatorio_comparacao_%s_%llu.txt", tipo, tamanho);
			FILE * p = fopen(arq, "r");
			int qtd_digitos;//quantidade de digitos do maior numero da entrada atual
			if(p == NULL){
				printf("Nao existem dados para a entrada %s de tamanho %llu, favor executar o algoritmo de relatorio!\n", tipo, tamanho);
				fclose(p);
				free(linha);
				free(arq);
				free(tipo);
				return;
			}
			else{
				printf("Gerando relatorio normalizado para algoritmos de comparacao...");
				double tempo[4];//4 algoritmos e 20 digitos para salvar o tempo medio de cada algoritmo
				int media[4];//Conta o numero de vezes que determinada combinacao foi registrada para tirar media ao fim
				for(int i = 0; i < 4; i++)//zera a matriz e o vetor
				{
					tempo[i] = 0.0;
					media[i] = 0;
				}
				while(1){//pecorre o arquivo salvando os tempos registrados por combinacao e a quantidade de vezes que cada combinacao ocorre
					if(fgets(linha,256,p)==NULL || linha[0] == '\n')
						break;
					double tempoAtual;//tempo do algoritmo atual
					int algoritmo;//algoritmo usado
					sscanf(linha, "%d;%d;%lf", &algoritmo, &qtd_digitos, &tempoAtual);
					tempo[algoritmo-1] += tempoAtual;
					media[algoritmo-1]++;
				}
				printf("\n");
				fclose(p);	
				sprintf(arq, ".\\%s\\Relatorio_comparacao_%s_%llu.txt", diretorio, tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
				FILE * p = fopen(arq, "w");	
				fprintf(p, "Entrada %s de tamanho %llu\n\n", tipo, tamanho);
				fprintf(p, "Digitos do maior numero = %d, tamanho da amostra = %d\n", qtd_digitos, media[3]);
				fprintf(p, "Mergesort: %lf\n", tempo[0]/media[0]);
				if(comparaString(tipo, (char*)"complexa"))
					fprintf(p, "Quicksort: %lf\n", tempo[1]/media[1]);
				fprintf(p, "Mergesort2(std::sort): %lf\n", tempo[2]/media[2]);
				fprintf(p, "Radixsort(d = 1): %lf\n\n", tempo[3]/media[3]);
				
				fprintf(p, "\nTabela latex da entrada");
				if(comparaString(tipo, (char*)"complexa"))
					fprintf(p, "\n\\textit{Quicksort} & %lf \\\\\n", tempo[1]/media[1]);
				else
					fprintf(p, "\n\\textit{Quicksort} & -  \\\\\n");
				fprintf(p, "\\textit{Mergesort1} & %lf \\\\\n", tempo[0]/media[0]);
				fprintf(p, "\\textit{Mergesort2} & %lf \\\\\n",  tempo[2]/media[2]);
				fprintf(p, "\\textit{Radix-base} & %lf \\\\\n\n\n\n", tempo[3]/media[3]);
				
				fprintf(p, "\n\n");
				fclose(p);	
			}
			
		    /**Normaliza entradas do radixsort**/
			sprintf(arq, ".\\dados\\Relatorio_radix_%s_%llu.txt", tipo, tamanho);
			p = fopen(arq, "r");
			if(p == NULL){
				printf("Nao existem dados para a entrada %s de tamanho %llu, favor executar o algoritmo de relatorio!\n", tipo, tamanho);
				fclose(p);
				free(linha);
				free(arq);
				free(tipo);
				return;
			}
			else{
				printf("Gerando relatorio normalizado para execucoes do Radixsort...");
				double tempo[8];//8 digitos por iteracao e 20 digitos para salvar o tempo medio de cada algoritmo
				double memoria[8];//4 algoritmos e 20 digitos para salvar o tempo medio de cada algoritmo
				int media[8];//Conta o numero de vezes que determinada combinacao foi registrada para tirar media ao fim
				for(int i = 0; i < 8; i++)//zera a matriz e o vetor
				{
						tempo[i] = 0.0;
						memoria[i] = 0.0;
						media[i] = 0;
				}
				while(1){//pecorre o arquivo salvando os tempos registrados por combinacao e a quantidade de vezes que cada combinacao ocorre
					if(fgets(linha,256,p)==NULL || linha[0] == '\n')
						break;
					double tempoAtual;//tempo do algoritmo atual
					double memoriaAtual;//memoria do algoritmo atual
					int qtd_digitos;//quantidade de digitos do maior numero da entrada atual
					int algoritmo;//algoritmo usado
					sscanf(linha, "%d;%d;%lf;%lf", &algoritmo, &qtd_digitos, &tempoAtual, &memoriaAtual);
					tempo[algoritmo-1] += tempoAtual;
					memoria[algoritmo-1] += memoriaAtual;
					media[algoritmo-1] ++;
				}
				printf("\n");
				fclose(p);	
				sprintf(arq, ".\\%s\\Relatorio_radix_%s_%llu.txt", diretorio, tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
				FILE * p = fopen(arq, "w");	
				fprintf(p, "Entrada %s de tamanho %llu\n\n", tipo, tamanho);
				fprintf(p, "Digitos do maior numero = %d, tamanho da amostra = %d\n", qtd_digitos, media[3]);
				if(qtd_digitos > 20)
					qtd_digitos = conta_digitos(qtd_digitos-1);
				for(int j = 0; j < 8; j++)
					fprintf(p, "Radixsort(d = %d): %lf, usando %lfMB\n", j+1, tempo[j]/media[j], memoria[j]/media[j]);
				fprintf(p, "\n\nTabela latex:\n");
				fprintf(p, "%d & $10^%d$ & %d & %lf & - \\\\\n", 1, 1, (int)ceil(qtd_digitos/1), tempo[0]/media[0]);
				for(int j = 1; j < 8; j++)
					fprintf(p, "%d & $10^%d$ & %d & %lf & %.2lf \\\\\n", j+1, j+1, (int)ceil(+qtd_digitos/(j+1.0)), tempo[j]/media[j], (tempo[0]/media[0])/(tempo[j]/media[j]));
				fprintf(p, "\n\n");
				fclose(p);	
			}
			if(f == 0)
				sprintf(tipo, "crescente");
			else if(f == 1)
				sprintf(tipo, "decrescente");
			else if(f == 2)
				break;
			f++;
		}
		free(linha);
		free(arq);
		free(tipo);
	}		
}

int comparaString(char * str1, char * str2){
	if(str1 == NULL || str2 == NULL)
		return 0;
	int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
    	if(str1[i] != str2[i])
    		return 0;
    	i++;
	}
	return 1;
}
