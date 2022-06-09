#include "radixsort_lista.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <psapi.h>

int conta_digitos(unsigned long long n){
	unsigned int d;
	for(d = 0; n > 0; n /= 10)
		d++;
	return d;
}

int radix_lista(lista * l, int d)//d = numero de digitos por iteracao
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
    unsigned long long qtd_baldes = (unsigned long long) pow(10,d);//numero exato de hashes por iteracao
    no ** baldes_raiz = (no **)malloc(qtd_baldes*sizeof(no*));//vetor de baldes apontando para o inicio da sublista
    if(baldes_raiz == NULL)//sem memoria
    	return 0;//falha ao ordenar
    no ** baldes_final = (no **)malloc(qtd_baldes*sizeof(no*));//vetor de baldes apontando para o final da sublista
    if(baldes_final == NULL)//sem memoria
    {
    	free(baldes_raiz);
    	return 0;//falha ao ordenar
	}
    for(unsigned long long i = 0; i < qtd_baldes; i++)//inicia todos os baldes com NULL
    {
        baldes_raiz[i]=NULL;
        baldes_final[i]=NULL;
    }
    unsigned int modulador = qtd_baldes;//modulador para extrair os digitos
    no * prox = l->raiz;//ponteiro de iteração da lista
    l->raiz = NULL;//lista para de apontar para os nos antigos, vai receber os nos na nova ordem
    unsigned long long maior = prox->n;//maior numero
    while(prox!=NULL)//Coleta o maior elemento e faz a primeira iteracao ao mesmo tempo
	{
        unsigned long long n = (unsigned long long) prox->n%modulador;//variavel auxiliar para evitar a repetição da operação de extração do dígito
        if(baldes_raiz[n]==NULL)//se o balde tiver vazio adiciona no comeco
            baldes_raiz[n] = prox;
        else//senao encadeia no final
            baldes_final[n]->prox = prox;
        if(maior < prox->n)//ve se o numero atual e maior que o maior atual, atualizando o valor se verdade
            maior = prox->n;
        baldes_final[n] = prox;
        prox = prox->prox;
        baldes_final[n]->prox=NULL;//ultimo balde recebe NULL para que ele pare de apontar para a proxima posicao(fatia a lista original)
    }
    unsigned long long i = 0;//variavel para pecorrer os baldes
    while(1){//loop para achar a primeira posicao preenchida
    	if(baldes_raiz[i]!=NULL){//se o balde raiz nao estiver vazio
            l->raiz=baldes_raiz[i];//balde raiz se torna a raiz da lista
            prox = baldes_final[i];//prox se torna o ultimo no da lista
            baldes_raiz[i]=NULL;//iguala o balde raiz a null(economiza um loop de limpeza)
			i++;
            break;
		}
		i++;
	}
    for(; i < qtd_baldes; i++)//pecorre o restante dos baldes
        if(baldes_raiz[i]!=NULL)//para cada posicao nao vazia
        {
            prox->prox = baldes_raiz[i];//move a raiz para a posicao posterior ao no anterior
            prox = baldes_final[i];
            baldes_raiz[i]=NULL;
        }
    #if WIN64
    	unsigned __int128 divisor =  qtd_baldes;//divisor para extrair os digitos em sistemas de 64 bits
    #else
    	unsigned __int64 divisor = qtd_baldes;//divisor para extrair os digitos em sistemas de 32 bits
    #endif
    unsigned int qtd_digitos_maior_numero = conta_digitos(maior);
    for(int j = d; j < qtd_digitos_maior_numero; j+=d)//mesma coisa que o loop acima, exceto a parte de pegar o maior
    {
        prox = l->raiz;
        l->raiz = NULL;
        while(prox!=NULL)
        {
            unsigned long long n =  ((unsigned long long) prox->n/divisor)%modulador;
            if(baldes_raiz[n]==NULL)
                baldes_raiz[n] = prox;
            else
                baldes_final[n]->prox = prox;
            baldes_final[n] = prox;
            prox = prox->prox;
            baldes_final[n]->prox=NULL;
        }
        unsigned long long i = 0;
        while(1){
        	if(baldes_raiz[i]!=NULL){
                l->raiz=baldes_raiz[i];
                prox = baldes_final[i];
                baldes_raiz[i]=NULL;
				i++;
                break;
			}
			i++;
		}
        for(; i < qtd_baldes; i++)
            if(baldes_raiz[i]!=NULL)
            {
                prox->prox = baldes_raiz[i];
                prox = baldes_final[i];
                baldes_raiz[i]=NULL;
            }
        #if WIN64//executando em sistemas de 64bits
	    	if(j<(20-d))
		    	divisor *= qtd_baldes;//atualiza o divisor para a proxima iteracao d=2	
		    else
		    	unsigned __int128 divisor = (unsigned __int128) divisor*qtd_baldes;//divisor para extrair os digitos em sistemas de 32 bits
		#else//sistemas de 32bits que nao suportam inteiro de 128 e portanto a ordenação se limita a 14 digitos
		    	divisor *= qtd_baldes;//atualiza o divisor para a proxima iteracao d=2	
		#endif
    }
    
	for(unsigned long long i = 0; i < qtd_baldes; i++){//aponta os baldes final para NULL - raiz ja estao como NULL
		baldes_final[i] = NULL;
    }
    
    free(baldes_raiz);//desaloca raizes
    free(baldes_final);//desaloca finais
	QueryPerformanceCounter(&end);
	
	l->tempo = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;//salva o tempo em segundos
    return 1;//sucesso ao ordenar
}



