#include "radixsort_lista.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <psapi.h>

int contaDigitos(unsigned long long n){
	unsigned int d;
	for(d = 0; n > 0; n /= 10)
		d++;
	return d;
}

int radixLista(lista * l, int d)//d = numero de digitos por iteracao
{
	//Variaveis para contar o tempo
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    
	if(d < 1)//menor digito possivel e 1
		exit(1);
    if(l->raiz == NULL)//Lista vazia
        return 1;
    if(l->raiz->prox == NULL)//1 elemento
    	return 1;
    unsigned long long qtdBaldes = (unsigned long long) pow(10,d);//numero exato de hashes por iteracao
    no ** baldesRaiz = (no **)malloc(qtdBaldes*sizeof(no*));//vetor de baldes apontando para o inicio da sublista
    if(baldesRaiz == NULL)//sem memoria
    	return 0;//falha ao ordenar
    no ** baldesFinal = (no **)malloc(qtdBaldes*sizeof(no*));//vetor de baldes apontando para o final da sublista
    if(baldesFinal == NULL)//sem memoria
    {
    	free(baldesRaiz);
    	return 0;//falha ao ordenar
	}
    for(unsigned long long i = 0; i < qtdBaldes; i++)//inicia todos os baldes com NULL
    {
        baldesRaiz[i]=NULL;
        baldesFinal[i]=NULL;
    }
    unsigned int modulador = qtdBaldes;//modulador para extrair os digitos
    no * prox = l->raiz;//ponteiro de iteração da lista
    l->raiz = NULL;//lista para de apontar para os nos antigos, vai receber os nos na nova ordem
    unsigned long long maior = prox->n;//maior numero
    while(prox!=NULL)//Coleta o maior elemento e faz a primeira iteracao ao mesmo tempo
	{
        unsigned long long n = (unsigned long long) prox->n%modulador;//variavel auxiliar para evitar a repetição da operação de extração do dígito
        if(baldesRaiz[n]==NULL)//se o balde tiver vazio adiciona no comeco
            baldesRaiz[n] = prox;
        else//senao encadeia no final
            baldesFinal[n]->prox = prox;
        if(maior < prox->n)//ve se o numero atual e maior que o maior atual, atualizando o valor se verdade
            maior = prox->n;
        baldesFinal[n] = prox;
        prox = prox->prox;
        baldesFinal[n]->prox=NULL;//ultimo balde recebe NULL para que ele pare de apontar para a proxima posicao(fatia a lista original)
    }
    unsigned long long i = 0;//variavel para pecorrer os baldes
    while(1){//loop para achar a primeira posicao preenchida
    	if(baldesRaiz[i]!=NULL){//se o balde raiz nao estiver vazio
            l->raiz=baldesRaiz[i];//balde raiz se torna a raiz da lista
            prox = baldesFinal[i];//prox se torna o ultimo no da lista
            baldesRaiz[i]=NULL;//iguala o balde raiz a null(economiza um loop de limpeza)
			i++;
            break;
		}
		i++;
	}
    for(; i < qtdBaldes; i++)//pecorre o restante dos baldes
        if(baldesRaiz[i]!=NULL)//para cada posicao nao vazia
        {
            prox->prox = baldesRaiz[i];//move a raiz para a posicao posterior ao no anterior
            prox = baldesFinal[i];
            baldesRaiz[i]=NULL;
        }
    #if WIN64
    	unsigned __int128 divisor =  qtdBaldes;//divisor para extrair os digitos em sistemas de 64 bits
    #else
    	unsigned __int64 divisor = qtdBaldes;//divisor para extrair os digitos em sistemas de 32 bits - nao ordena corretamente quando k > 20-d
    #endif
    unsigned int qtdDigitosMaiorNumero = contaDigitos(maior);
    for(int j = d; j < qtdDigitosMaiorNumero; j+=d)//mesma coisa que o loop acima, exceto a parte de pegar o maior
    {
        prox = l->raiz;
        l->raiz = NULL;
        while(prox!=NULL)
        {
            unsigned long long n =  ((unsigned long long) prox->n/divisor)%modulador;
            if(baldesRaiz[n]==NULL)
                baldesRaiz[n] = prox;
            else
                baldesFinal[n]->prox = prox;
            baldesFinal[n] = prox;
            prox = prox->prox;
            baldesFinal[n]->prox=NULL;
        }
        unsigned long long i = 0;
        while(1){
        	if(baldesRaiz[i]!=NULL){
                l->raiz=baldesRaiz[i];
                prox = baldesFinal[i];
                baldesRaiz[i]=NULL;
				i++;
                break;
			}
			i++;
		}
        for(; i < qtdBaldes; i++)
            if(baldesRaiz[i]!=NULL)
            {
                prox->prox = baldesRaiz[i];
                prox = baldesFinal[i];
                baldesRaiz[i]=NULL;
            }
		divisor *= qtdBaldes;//atualiza o divisor para a proxima iteracao
    }
    
	for(unsigned long long i = 0; i < qtdBaldes; i++){//aponta os baldes final para NULL - raiz ja estao como NULL
		baldesFinal[i] = NULL;
    }
    
    free(baldesRaiz);//desaloca raizes
    free(baldesFinal);//desaloca finais
	QueryPerformanceCounter(&end);
	
	l->tempo = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;//salva o tempo em segundos
    return 1;//sucesso ao ordenar
}



