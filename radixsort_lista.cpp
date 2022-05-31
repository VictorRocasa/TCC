#include "radixsort_lista.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <psapi.h>

int conta_digitos(unsigned long long n){
	int d;
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
    unsigned __int128 divisor = qtd_baldes;//divisor para extrair os digitos
    unsigned __int128 modulador = 1;//modulador para extrair os digitos
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
    no * prox = l->raiz;//ponteiro de itera��o da lista
    l->raiz = NULL;//lista para de apontar para os nos antigos, vai receber os nos na nova ordem
    unsigned long long maior = prox->n;//maior numero
    while(prox!=NULL)//Coleta o maior elemento e faz a primeira iteracao ao mesmo tempo
	{
        unsigned long long n = (unsigned long long) (prox->n%divisor)/modulador;//variavel auxiliar para evitar a repeti��o da opera��o de extra��o do d�gito
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
    for(unsigned long long i = 0; i < qtd_baldes; i++)
        if(baldes_raiz[i]!=NULL)//se o balde estiver preenchido
        {
            if(l->raiz==NULL)//caso a lista ainda esteja vazia
                l->raiz=baldes_raiz[i];//torna o primeiro balde preenchido na nova raiz 
            else//caso a lista nao esteja vazia
                prox->prox = baldes_raiz[i];//o prox(ultima posicao da sublista anterior) passa a apontar para a primeira da sublista autal
            prox = baldes_final[i];//torna o prox o ultimo no do balde
            baldes_raiz[i]=NULL;//"limpa" os baldes de raiz dentro da iteracao
        }
    int qtd_digitos_maior_numero = conta_digitos(maior);
    for(int j = d; j < qtd_digitos_maior_numero; j+=d)//mesma coisa que o loop acima, exceto a parte de pegar o maior
    {
	    divisor *= qtd_baldes;//atualiza o divisor para a proxima iteracao d=2	8000010461812853982
	    modulador *= qtd_baldes;//atualiza o modulador para a proxima iteracao
        prox = l->raiz;
        l->raiz = NULL;
        while(prox!=NULL)
        {
            unsigned long long n = (unsigned long long) (prox->n%divisor)/modulador;
            if(baldes_raiz[n]==NULL)
                baldes_raiz[n] = prox;
            else
                baldes_final[n]->prox = prox;
            baldes_final[n] = prox;
            prox = prox->prox;
            baldes_final[n]->prox=NULL;
        }
        for(unsigned long long i = 0; i < qtd_baldes; i++)
            if(baldes_raiz[i]!=NULL)
            {
                if(l->raiz==NULL)
                    l->raiz=baldes_raiz[i];
                else
                    prox->prox = baldes_raiz[i];
                prox = baldes_final[i];
                baldes_raiz[i]=NULL;
            }
    }
    
    
    PROCESS_MEMORY_COUNTERS pmc;//variavel para acessar os dados da memoria primaria
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));//Coleta os dados da memoria do processo
    l->memoria = (double) pmc.WorkingSetSize/1000000;//Salva a mem�ria alocada por essa entrada antes de ser liberada
    
	for(unsigned long long i = 0; i < qtd_baldes; i++){//aponta os baldes final para NULL
		baldes_final[i] = NULL;
    }
    
    free(baldes_raiz);//desaloca raizes
    free(baldes_final);//desaloca finais
	QueryPerformanceCounter(&end);
	
	l->tempo = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;//salva o tempo em segundos
    return 1;//sucesso ao ordenar
}



