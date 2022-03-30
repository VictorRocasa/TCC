#include <stdlib.h>
#include "quick_sort.h"
#include "lista.h"
#include <stdio.h>
#include <windows.h>
#include <psapi.h>

pivor * novo(no * elemento, pivor * pai){
	pivor * p = (pivor *) malloc(sizeof(pivor));
	if(p == NULL)
		return NULL;
	p->elemento = elemento;//no da lista
	p->ultimoPivor = elemento;
	p->esq = NULL;//inicia sublista para os elementos menores
	p->dir = NULL;//inicia sublista para os elementos maiores
	p->pai = pai;//aponta para o pivor pai
	return p;
}

void quickSort(lista * l){
	if(l->raiz == NULL)//lista vazia
		return;
	pivor * p = novo(l->raiz,NULL);//primeiro pivor(primeiro elemento por questoes de otimizacao para a lista usada)
	l->raiz = NULL;//;raiz para de apontar para a lista por enquanto
		
	//Variaveis para contar o tempo
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    
    //variaveis para contar o uso memoria
    PROCESS_MEMORY_COUNTERS pmc;//variavel para acessar os dados da memoria primaria
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));//Coleta os dados da memoria do processo
	    
	no * ultimoGeral;//variavel para reinserir elementos na lista no futuro
	do{	
		//apos olhar pecorrer a direita retorna ao pai
		if(p->elemento == NULL){//se o elemento estiver como nulo, ele foi movido para raiz
		
    		double memoria = (double) pmc.WorkingSetSize/1000000;//Calcula a memoria antes de desalocar esse pivor 
		 	if(memoria > l->memoria)//caso ela seja maior que a salva atualmente, se torna a nova salva
		 		l->memoria = memoria;
		 		
			pivor * aux = p;//aux para salvar a referencia atual
			p = p->pai;//pivor retorna para o pai
			free(aux);//desaloca pivor atual
			if(p == NULL){//se pai for NULL, a lista esta ordenada
				QueryPerformanceCounter(&end);
				l->tempo = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;//salva o tempo em segundos
				return;
			}
		}
		else if(p->elemento->prox != NULL){//se o pivor aponta para outros elementos, os move para a esquerda ou direita
			no * prox = p->elemento->prox;//prox comeca no elemento apos o pivor
			p->elemento->prox = NULL;//isola pivor
			no * ultimoEsq;//variavel para mover os elementos para o fim da sublista da esquerda
			no * ultimoDir;//variavel para mover os elementos para o fim da sublista da direita	
			while(prox!=NULL){//pecorre toda a sublista atual
				if(prox->n < p->elemento->n){//elementos menores movidos para a esquerda
					if(p->esq == NULL){//logica para alocar ao fim da sublista
						p->esq = prox;
						ultimoEsq = prox; 
					}
					else{
						ultimoEsq->prox = prox;
						ultimoEsq = prox;
					}
					prox = prox->prox;
					ultimoEsq->prox = NULL;
				}
				else if(prox->n == p->elemento->n){//elementos iguais sao colados no pivor por questoes de otimizacao(comentar para desenpenho tradicional)
					p->ultimoPivor->prox = prox;
					p->ultimoPivor = prox;
					prox = prox->prox;
					p->ultimoPivor->prox = NULL;
				}
				else{//elementos maiores ou iguais ao pivor movidos para a direita
					if(p->dir == NULL){//logica para alocar ao fim da sublista
						p->dir = prox;
						ultimoDir = prox;
					}
					else{
						ultimoDir->prox = prox;
						ultimoDir = prox;
					}
					prox = prox->prox;
					ultimoDir->prox = NULL;
				}			
			}
		}
		if(p->esq!=NULL){//se tiverem elementos menores que o pivor
			pivor * aux = p;//aux para salvar a referencia atual
			p = novo(p->esq,p);//aloca novo pivor passando a sublista esquerda e o pivor atual como pai
			aux->esq = NULL;//apaga a referemcia para a esquerda
		}
		else{//se nao houverem elementos na esquerda, mover pivor para a lista e depois olhar na direita
			if(p->elemento != NULL){
				if(l->raiz == NULL){//logica para alocar ao fim da lista
					l->raiz = p->elemento;
					ultimoGeral = p->ultimoPivor;
				}
				else{
					ultimoGeral->prox = p->elemento;
					ultimoGeral = p->ultimoPivor;				
				} 
				p->elemento = NULL;
			}
			if(p->dir!=NULL){//se tiverem elementos menores que o pivor
				pivor * aux = p;//aux para salvar a referencia atual
				p = novo(p->dir,p);//aloca novo pivor passando a sublista direita e o pivor atual como pai
				aux->dir = NULL;//apaga a referemcoa para a direita
			}
		}
	}while(1);
}
