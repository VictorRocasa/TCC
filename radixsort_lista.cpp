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
    unsigned long long qtd_baldes = pow(10,d);//numero exato de hashes por iteracao
    unsigned long long divisor = qtd_baldes;//divisor para extrair os digitos
    unsigned long long modulador = 1;//modulador para extrair os digitos
    no ** baldes_raiz = (no **)malloc(qtd_baldes*sizeof(no*));//vetor de baldes apontando para o inicio da sublista
    no ** baldes_final = (no **)malloc(qtd_baldes*sizeof(no*));//vetor de baldes apontando para o final da sublista
    if(baldes_raiz == NULL || baldes_final == NULL)//sem memoria
    	return 0;//falha ao ordenar
    for(unsigned long long i = 0; i < qtd_baldes; i++)//inicia todos os baldes com NULL
    {
        baldes_raiz[i]=NULL;
        baldes_final[i]=NULL;
    }
    unsigned long long n;//variavel auxiliar para evitar a repetição da operação de extração do dígito
    no * prox = l->raiz;//ponteiro de iteração da lista
    l->raiz = NULL;//lista para de apontar para os nos antigos, vai receber os nos na nova ordem
    unsigned long long maior = prox->n;//maior numero
    while(prox!=NULL)//Coleta o maior elemento e faz a primeira iteracao ao mesmo tempo
	{
        n = (prox->n%divisor)/modulador;
        if(baldes_raiz[n]==NULL)//se o balde tiver vazio adiciona no comeco
        {
            baldes_raiz[n] = prox;
            baldes_final[n] = prox;
        }
        else//senao encadeia no final
        {
            baldes_final[n]->prox = prox;
            baldes_final[n] = prox;
        }
        if(maior < prox->n)//ve se o numero atual e maior que o maior atual, atualizando o valor se verdade
            maior = prox->n;
        prox = prox->prox;
        baldes_final[n]->prox=NULL;//ultimo balde recebe NULL para que ele pare de apontar para a proxima posicao(fatia a lista original)
    }
    for(unsigned long long i = 0; i < qtd_baldes; i++)
        if(baldes_raiz[i]!=NULL)//se o balde estiver preenchido
        {
            if(l->raiz==NULL)//caso a lista ainda esteja vazia
            {
                l->raiz=baldes_raiz[i];//torna o primeiro balde preenchido na nova raiz 
                prox = baldes_final[i];//torna o prox o ultimo no do balde
            }
            else//caso a lista nao esteja vazia
            {
                prox->prox = baldes_raiz[i];//o prox(ultima posicao da sublista anterior) passa a apontar para a primeira da sublista autal
                prox = baldes_final[i];//torna o prox o ultimo no do balde
            }
            baldes_raiz[i]=NULL;//"limpa" os baldes de raiz dentro da iteracao
        }
    int qtd_digitos_maior_numero = conta_digitos(maior);
    int j = 1;
    while(j < qtd_digitos_maior_numero)//mesma coisa que o loop acima, exceto a parte de pegar o maior
    {
	    divisor *= qtd_baldes;//atualiza o divisor para a proxima iteracao
	    modulador *= qtd_baldes;//atualiza o modulador para a proxima iteracao
        prox = l->raiz;
        l->raiz = NULL;
        while(prox!=NULL)
        {
            n = (prox->n%divisor)/modulador;
            if(baldes_raiz[n]==NULL)
            {
                baldes_raiz[n] = prox;
                baldes_final[n] = prox;
            }
            else
            {
                baldes_final[n]->prox = prox;
                baldes_final[n] = prox;
            }
            prox = prox->prox;
            baldes_final[n]->prox=NULL;
        }
        for(unsigned long long i = 0; i < qtd_baldes; i++)
            if(baldes_raiz[i]!=NULL)
            {
                if(l->raiz==NULL)
                {
                     l->raiz=baldes_raiz[i];
                    prox = baldes_final[i];
                }
                else
                {
                    prox->prox = baldes_raiz[i];
                    prox = baldes_final[i];
                }
                baldes_raiz[i]=NULL;
            }
        j+=d;
    }
    PROCESS_MEMORY_COUNTERS pmc;//variavel para acessar os dados da memoria primaria
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));//Coleta os dados da memoria do processo
    l->memoria = (double) pmc.WorkingSetSize/1000000;//Salva a memória alocada por essa entrada antes de ser liberada
	for(unsigned long long i = 0; i < qtd_baldes; i++){//aponta os baldes final para NULL
		baldes_final[i] = NULL;
    }
    free(baldes_raiz);//desaloca raizes
    free(baldes_final);//desaloca finais
	QueryPerformanceCounter(&end);
	l->tempo = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;//salva o tempo em segundos
    return 1;//sucesso ao ordenar
}



