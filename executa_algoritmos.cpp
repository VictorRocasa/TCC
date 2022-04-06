#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <psapi.h>
#include <list>
#include "lista.h"
#include "maximos.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "radixsort_lista.h"

int ler_entrada(lista * l, char * arq);//funcao para ler uma entrada de a partir de um arquivo com seu endereco passado por parâmetro
void provaDeOrdenacao();//Mostra que a saída de todos os algoritmos são iguais e ordenadas
void gera_relatorios(int tamanhoRequerido, char * tipoRequerido);//executa os algoritmos usando um tipo de entrada dentro de um diretorio passados por parametro
int lerEntradaCPP(std::list<unsigned long long>& entradaCPP, char * arq);//le entrada para a lista nativa do C++
void cppSortAux(std::list<unsigned long long>& entradaCPP, lista * l);//auxiliar para marcar o tempo do std::sort
void normalizarResultados();//funcao que gera relatorios com as medias dos relatorios gerados pelas diversas execucoes da funcao anterior
int comparaString(char * str1, char * str2);//funcao auxiliar para comparar duas strings passadas por parametro

int main(){//teste.txt
	//provaDeOrdenacao();
	//for(int i = 0; i < 10; i++){//loop para gerar 10 relatorios
		//printf("Iteracao %d\n", i+1);
		//gera_relatorios(1000000, NULL);//executa todas as entradas de tamanho = 1000000
		//gera_relatorios(10000000, NULL);//executa todas as entradas de tamanho = 10000000
		//gera_relatorios(100000000, (char *)"complexa");//executa todas as entradas complexas de tamanho = 100000000
		//gera_relatorios(100000000, (char *)"crescente");//executa todas as entradas complexas de tamanho = 100000000
		//gera_relatorios(100000000, (char *)"decrescente");//executa todas as entradas complexas de tamanho = 100000000
		//gera_relatorios(100000000, (char *)"igual");//executa todas as entradas complexas de tamanho = 100000000
		//gera_relatorios(100000000, (char *)"aleatoria");//executa todas as entradas complexas de tamanho = 100000000
		//printf("Iteracao %d concluida, a proxima iniciara em 10 segundos\n", i+1);
		//Sleep(10000);
	//}
	normalizarResultados();

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

void gera_relatorios(int tamanhoRequerido, char * tipoRequerido){	
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
		if((tamanho == tamanhoRequerido || tamanhoRequerido == 0) && (comparaString(tipoRequerido,tipo) || tipoRequerido == NULL)){//executa apenas as entradas de tamanho e tipo especificado. 0 ignora tamanho e NULL tipo
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
			fprintf(p, "1;%d;%lf\n", qtd_digitos, entrada->tempo);
			
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
				fprintf(p, "2;%d;%lf\n",qtd_digitos, entrada->tempo);
			}
			else
				fprintf(p, "%2;d;%lf\n", qtd_digitos, 0.0);
			
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
			fprintf(p, "3;%d;%lf\n", qtd_digitos, entrada->tempo);
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

void normalizarResultados(){
	printf("Normalizando resultados...\n");
	CreateDirectory("Final", NULL);//cria o diretorio de relatorios finais se não existe
	for(unsigned long long tamanho = MINT; tamanho <= MAXT; tamanho *=10){
		char * arq = (char*)malloc(256*sizeof(char*));//variavel para ler arquivos
		char * linha = (char*)malloc(256*sizeof(char*));//variavel para ler linhas de arquivos
	    char * tipo = (char*)malloc(128*sizeof(char*));//nome dodo tipo da entrada para gerar o endereco
	    
	    /**Normaliza entradas aleatorias**/
		sprintf(tipo, "aleatoria");
		printf("Lendo resultados da entrada %s de tamanho %llu.\n", tipo, tamanho);
		sprintf(arq, ".\\dados\\Relatorio_comparacao_%s_%llu.txt", tipo, tamanho);
		FILE * p = fopen(arq, "r");
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
			sprintf(arq, ".\\Final\\Relatorio_comparacao_%s_%llu.txt", tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
			FILE * p = fopen(arq, "w");	
			fprintf(p, "Entrada %s de tamanho %llu\n\n", tipo, tamanho);
			for(int i = 0; i < 20; i++){
				fprintf(p, "Digitos do maior numero = %d\n", i+1);
				fprintf(p, "Mergesort: %lf\n", tempo[0][i]/media[0][i]);
				fprintf(p, "Quicksort: %lf\n", tempo[1][i]/media[1][i]);
				fprintf(p, "Introsort(std::sort): %lf\n", tempo[2][i]/media[2][i]);
				fprintf(p, "Radixsort(d = 1): %lf\n\n", tempo[3][i]/media[3][i]);
			}
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
			double tempo[7][20];//4 algoritmos e 20 digitos para salvar o tempo medio de cada algoritmo
			double memoria[7][20];//4 algoritmos e 20 digitos para salvar o tempo medio de cada algoritmo
			int media[7][20];//Conta o numero de vezes que determinada combinacao foi registrada para tirar media ao fim
			for(int i = 0; i < 7; i++)//zera a matriz e o vetor
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
			sprintf(arq, ".\\Final\\Relatorio_radix_%s_%llu.txt", tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
			FILE * p = fopen(arq, "w");	
			fprintf(p, "Entrada %s de tamanho %llu\n\n", tipo, tamanho);
			for(int i = 0; i < 20; i++){
				fprintf(p, "Digitos do maior numero = %d\n", i+1);
				for(int j = 0; j < 7; j++)
					fprintf(p, "Radixsort(d = %d): %lf, usando %lfMB\n", j+1, tempo[j][i]/media[j][i], memoria[j][i]/media[j][i]);
				fprintf(p, "\n");
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
				sprintf(arq, ".\\Final\\Relatorio_comparacao_%s_%llu.txt", tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
				FILE * p = fopen(arq, "w");	
				fprintf(p, "Entrada %s de tamanho %llu\n\n", tipo, tamanho);
				fprintf(p, "Digitos do maior numero = %d\n", qtd_digitos);
				fprintf(p, "Mergesort: %lf\n", tempo[0]/media[0]);
				fprintf(p, "Quicksort: %lf\n", tempo[1]/media[1]);
				fprintf(p, "Introsort(std::sort): %lf\n", tempo[2]/media[2]);
				fprintf(p, "Radixsort(d = 1): %lf\n\n", tempo[3]/media[3]);
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
				double tempo[7];//4 algoritmos e 20 digitos para salvar o tempo medio de cada algoritmo
				double memoria[7];//4 algoritmos e 20 digitos para salvar o tempo medio de cada algoritmo
				int media[7];//Conta o numero de vezes que determinada combinacao foi registrada para tirar media ao fim
				for(int i = 0; i < 7; i++)//zera a matriz e o vetor
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
				sprintf(arq, ".\\Final\\Relatorio_radix_%s_%llu.txt", tipo, tamanho);//cria um relatorio csv com dados das execucoes dos algoritmos para cada entrada de um certo tipo e tamanho: Algoritmo;DigitosMaiorNumero;Tempo
				FILE * p = fopen(arq, "w");	
				fprintf(p, "Entrada %s de tamanho %llu\n\n", tipo, tamanho);
				fprintf(p, "Digitos do maior numero = %d\n", qtd_digitos);
					for(int j = 0; j < 7; j++)
						fprintf(p, "Radixsort(d = %d): %lf, usando %lfMB\n", j+1, tempo[j]/media[j], memoria[j]/media[j]);
					fprintf(p, "\n");
				fclose(p);	
			}
		if(f == 0)
			sprintf(tipo, "igual");	
		else if(f == 1)
			sprintf(tipo, "crescente");
		else if(f == 2)
			sprintf(tipo, "decrescente");
		else if(f==3)
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
