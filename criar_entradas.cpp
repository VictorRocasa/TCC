#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "maximos.h"
#include <windows.h>


int conta_aleatoria = 0;
int ordenada_crescente = 0;
int ordenada_decrescente = 0;
int conta_igual = 0;
int conta_pior_caso = 0;

unsigned long long geraNumero(int maxDigitos);//Codigo para gerar um numero de ate 20 digitos
unsigned long long geraNumero20();//Codigo para gerar um numero de exatamente 20 digitos
void gravar_entrada_aleatoria(int t, int n);//gera 3 entradas com t elementos variando de 0 a n
void gravar_entrada_crescente(int t);//gera uma entrada com t elementos ordenados(crescente)
void gravar_entrada_decrescente(int t);//gera uma entrada com t elementos ordenados(decrescente)
void gravar_entrada_igual(int t, unsigned long long n);//Função para gerar uma entrada com t elementos equivalentes a n
void gravar_entrada_pior_caso(int t);//gera 3 entrada com t elementos variando de 10000000000000000000 a MAXT
FILE * criar_arquivo(char * arq);
FILE * info;
int sob = 1;


int main(){
    info =  fopen((char *)"cabecalho.txt","r");
    if(info!=NULL)
    	do{
	    	printf("Ja existem entradas, feche o programa para preserva-las. Caso contrario, deseja recriar o cabecalho? S/N\n");
	    	char escolha;
			scanf("%c", &escolha);
			if(escolha == 'S' || escolha == 's'){
				info = criar_arquivo((char *)"cabecalho.txt");
				break;
			}
			else if(escolha == 'N' || escolha == 'n'){
				sob = 0;
				break;
			}
			else{
				printf("Opcao invalida!\n");
			}    	
		}while(1);
	else
		info = criar_arquivo((char *)"cabecalho.txt");
	printf("Gravando entradas...\n");
	for(int t = MINT; t <= MAXT; t *= 10){//valor de t variando de 10000 a MAXT
        printf("Entradas de tamanho %d:\n", t);
		int n = MINN;
        for(; n <= MAXN; n++){//valor de n variando de <10 a <MAXN
        	printf("Digitos do maior numero %d\n", n);
            gravar_entrada_aleatoria(t,n);
        }
        printf("Maior numero 18446744073709551615llu...");
		gravar_entrada_igual(t,18446744073709551615llu);//entradas iguais com o maior numero possivel
        printf("Maior numero %d...", t-1);
		gravar_entrada_igual(t, (unsigned long long)t-1);//entradas iguais com t-1
        printf("Entrada com numeros de 20 digitos...", n);
		gravar_entrada_pior_caso(t);
        printf("0-%d...", t-1);
		gravar_entrada_crescente(t);
        printf("%d-0...", t-1);
		gravar_entrada_decrescente(t);
		printf("\n");
	fclose(info);
		return 0;
	}
	fclose(info);

    return 0;
}

unsigned long long geraNumero(int maxDigitos){
	int qtd = rand() % maxDigitos + 1;
	if(qtd >= 20)
		return geraNumero20();//se a quantidade for >= 20, gera um numero de exatamente 20 digitos
	unsigned long long n = rand() % 10;//comecando de um numero de 0 a 9
	unsigned long long potencia = 10;//potencia: gera dezena depois centena depois milhar...
	for(int i = 1; i < qtd; i++){
		n += (rand() % 10)*potencia;//a cada iteracao soma com outro de 0 a 9 multiplicado pela potencia
		potencia*=10;
	}
	
	return n;
}

unsigned long long geraNumero20(){
    unsigned long long n = geraNumero(19);
	if(n > 8446744073709551615)//maior numero possivel que ao somado a 10000000000000000000 não vai dar overflow
		n = 8446744073709551615;	
	return n + 10000000000000000000llu;
}

void gravar_entrada_aleatoria(int t, int n){
	int rep;//variavel para gerar multiplas entradas

	if(t == MINT)
		rep = 10;
	else if(t < MAXT)
		rep = 5;
	else if(t == MAXT)
		rep = 2;
	else
		rep = 1;
		
	unsigned long long j;//contador para gerar n numeros
	char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
	CreateDirectory("entradas_aleatorias", NULL);//cria o diretorio se nao existir
	srand(time(NULL));
	for(int i = 0; i < rep; i++){
	    conta_aleatoria++;
		sprintf(arq, ".\\entradas_aleatorias\\entrada_aleatoria_%d.txt", conta_aleatoria);//caminho da entrada
		FILE * p = criar_arquivo(arq);
		if(p!=NULL){//p = NULL, entrada já existe então pula
		    for(j = 0; j < t; j++)
		        fprintf(p, "%llu\n", geraNumero(n));//salva cada elemento gerado aleatóriamente seguido de ;
			fclose(p);
			if(sob)
		    	fprintf(info, "aleatorias aleatoria %d %d %d\n", conta_aleatoria, t, n);//salva entrada no arquivo que armazena as entradas criadas  	
			printf("Aleatoria %d salva\n", conta_aleatoria);//feedback visual
		}
	}
	free(arq);
}

void gravar_entrada_crescente(int t){
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    ordenada_crescente++;
	CreateDirectory("entradas_crescentes", NULL);//cria o diretorio se nao existir
    sprintf(arq, ".\\entradas_crescentes\\entrada_crescente_%d.txt", ordenada_crescente);
    FILE * p = criar_arquivo(arq);
    for(int i = 0; i < t; i++)
        fprintf(p, "%llu\n", i);//salva cada elemento seguido de ;
    fclose(p);
    if(sob)
        fprintf(info, "crescentes crescente %d %d %d\n", ordenada_crescente, t, t);//salva entrada no arquivo que armazena as entradas criadas
    printf("Crescente %d salva\n", ordenada_crescente);//feedback visual
    free(arq);
}

void gravar_entrada_decrescente(int t){
    unsigned long long k = t-1;
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    ordenada_decrescente++;
	CreateDirectory("entradas_decrescentes", NULL);//cria o diretorio se nao existir
    sprintf(arq, ".\\entradas_decrescentes\\entrada_decrescente_%d.txt", ordenada_decrescente);
    FILE * p = criar_arquivo(arq);
    for(int i = 0; i < t; i++){
        fprintf(p, "%llu\n", k);//salva cada elemento seguido de ;
        k--;
    }
    fclose(p);
    if(sob)
        fprintf(info, "decrescentes decrescente %d %d %d\n", ordenada_decrescente, t, t);//salva entrada no arquivo que armazena as entradas criadas
    printf("Decrescente %d salva\n", ordenada_decrescente);//feedback visual
    free(arq);
}

void gravar_entrada_igual(int t,unsigned long long n){
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
    conta_igual++;
	CreateDirectory("entradas_iguais", NULL);//cria o diretorio se nao existir
    sprintf(arq, ".\\entradas_iguais\\entrada_igual_%d.txt", conta_igual);
    FILE * p = criar_arquivo(arq);
    for(int i = 0; i < t; i++)
        fprintf(p, "%llu\n", n);//salva cada elemento seguido de \n
    fclose(p);
    
    int digitosMaior = 1;
	while(n > 1){
		n = n/10;
		digitosMaior++;
		
	}
	
    if(sob)
        fprintf(info, "iguais igual %d %llu %llu\n", conta_igual, t, digitosMaior);//salva entrada no arquivo que armazena as entradas criadas
    printf("Igual %d salva\n", conta_igual);//feedback visual
    free(arq);
}

void gravar_entrada_pior_caso(int t){
	srand(time(NULL));
    char * arq = (char*)malloc(256*sizeof(char));//string para guardar o caminho da entrada
	CreateDirectory("entradas_complexas", NULL);//cria o diretorio se nao existir
    conta_pior_caso++;
	sprintf(arq, ".\\entradas_complexas\\entrada_complexa_%d.txt", conta_pior_caso);
    FILE * p = criar_arquivo(arq);
    for(int j = 0; j < t; j++)
         fprintf(p, "%llu\n" , geraNumero20());//salva cada elemento gerado aleatóriamente seguido de ;
    fclose(p);
	if(sob)
    	fprintf(info, "complexas complexa %d %d 20\n", conta_pior_caso, t);//salva entrada no arquivo que armazena as entradas criadas
	printf("Pior caso %d salva\n", conta_pior_caso);//feedback visual
    free(arq);
}

FILE * criar_arquivo(char * arq){
    FILE * p;
    p =  fopen(arq,"w");
    return p;
}
