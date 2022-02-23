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

void radix_lista(lista * l, int d)//d = numero de digitos por iteracao
{
	if(d < 1)//menor digito possivel e 1
		exit(1);
    if(l->raiz == NULL)//Lista vazia
        return;
    if(l->raiz->prox == NULL)//1 elemento
    	return;
    unsigned long long qtd_baldes = pow(10,d);//numero exato de hashes por iteracao
    unsigned long long divisor = qtd_baldes;//divisor para extrair os digitos
    unsigned long long modulador = 1;//modulador para extrair os digitos
    no ** baldes_raiz = (no **)malloc(qtd_baldes*sizeof(no*));//vetor de baldes apontando para o inicio da sublista em iteracoes impares
    no ** baldes_aux = (no **)malloc(qtd_baldes*sizeof(no*));//vetor de baldes apontando para o inicio da sublista em iteracoes pares
    no ** baldes_final = (no **)malloc(qtd_baldes*sizeof(no*));//vetor de baldes apontando para o final da sublista
    if(baldes_raiz == NULL || baldes_aux == NULL || baldes_final == NULL)//sem memoria
    	return;
    unsigned long long i = 0;
    for(i = 0; i < qtd_baldes; i++)//inicia todos os baldes com NULL
    {
        baldes_raiz[i]=NULL;
        baldes_aux[i] = NULL;
        baldes_final[i]=NULL;
    }
    unsigned long long n;//variavel auxiliar para evitar a repetição da operação de extração do dígito
    no * prox = l->raiz;//ponteiro de iteração da lista
    unsigned long long maior = prox->n;//maior numero
    while(prox!=NULL)//Coleta o maior elemento e move a lista para baldes_raiz
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
    l->raiz = NULL;//lista para de apontar para os nos antigos, vai receber os nos na nova ordem ao final do codigo
    int aux = 0;//se a lista esta em aux ou nao
    int qtd_digitos_maior_numero = conta_digitos(maior);
    int j = 1;//j comeca em um pois a primeira iteracao ja foi feita
    while(j < qtd_digitos_maior_numero)//mesma coisa que o loop acima, exceto a parte de pegar o maior
    {
	    divisor *= qtd_baldes;//atualiza o divisor para a proxima iteracao
	    modulador *= qtd_baldes;//atualiza o modulador para a proxima iteracao
	    for(i = 0; i < qtd_baldes; i++)
	        if(baldes_raiz[i]!=NULL)//se o balde estiver preenchido
	        {
	        	prox = baldes_raiz[i];
	        	while(prox!=NULL){
	        		n = (prox->n%divisor)/modulador;
			        if(baldes_aux[n]==NULL)//se o balde tiver vazio adiciona no comeco
			        {
			            baldes_aux[n] = prox;
			            baldes_final[n] = prox;
			        }
			        else//senao encadeia no final
			        {
			            baldes_final[n]->prox = prox;
			            baldes_final[n] = prox;
			        }
	        		prox = prox->prox;
	        		baldes_final[n]->prox=NULL;
				}
	            baldes_raiz[i]=NULL;//"limpa" os baldes de raiz dentro da iteracao
	        }  	    	
        j+=d;
        if(j >= qtd_digitos_maior_numero){
        	aux = 1;//lista ordenada na raiz
        	break;
		}
        divisor *= qtd_baldes;
        modulador *= qtd_baldes;
	    for(i = 0; i < qtd_baldes; i++)
	        if(baldes_aux[i]!=NULL)//se o balde estiver preenchido
	        {
	        	prox = baldes_aux[i];
	        	while(prox!=NULL){
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
	        		prox = prox->prox;
	        		baldes_final[n]->prox=NULL;
				}
	            baldes_aux[i]=NULL;//"limpa" os baldes de raiz dentro da iteracao
	        }        
        j+=d;
    }
    PROCESS_MEMORY_COUNTERS pmc;//variavel para acessar os dados da memoria primaria
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));//Coleta os dados da memoria do processo
    l->picoMemoria = (double) pmc.WorkingSetSize/1000000;//Salva a memória alocada por essa entrada antes de ser liberada
    for(i = 0; i < qtd_baldes; i++){//repreenche a lista e desaloca a memoria alocada
    	if(aux){
    		if(baldes_aux[i]!=NULL){
	    		if(l->raiz == NULL)
	    			l->raiz = baldes_aux[i];
				else
					prox->prox = baldes_aux[i];
	    		prox = baldes_final[i];
	    		no * teste = baldes_aux[i];
	    		while(teste!=NULL){
	    			teste = teste->prox;
				}
			}
		}
		else{
    		if(baldes_raiz[i]!=NULL){
	    		if(l->raiz == NULL)
	    			l->raiz = baldes_raiz[i];
				else
					prox->prox = baldes_raiz[i];
	    		prox = baldes_final[i];
			}
		}
    }
    free(baldes_raiz);
	free(baldes_aux);
    free(baldes_final);
}

