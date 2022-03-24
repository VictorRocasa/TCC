#ifndef LISTA_H
#define LISTA_H

typedef struct No{//estrutura da lista
    unsigned long long n;
    struct No * prox;
}no;

typedef struct Lista{//estrutura auxiliar para coletar dados de dentro dos algoritmos
    struct No * raiz;
    unsigned long long tamanho;
    int digitos_maior_numero;
	double tempo;  
    double memoria;  
}lista;

lista * cria_lista(unsigned long long tamanho,int digitos_maior_numero);//inicia uma nova estrutura auxiliar
no * aloca_no(unsigned long long n);//aloca e retorna um novo no
no * adiciona_no(lista * l, no * anterior, unsigned long long n);//adiciona um novo no apos o anterior e retorna esse novo no para ser o novo anterior
void desaloca_lista(lista * l);//desaloca a lista inteira e a estrutura auxiliar, retornando NULL
void imprimir_lista(lista * l);//imprime a lista na tela(para debug)
lista * finalizaLista(lista * l);//Desaloca a estrutura auxiliar

#endif /*LISTA_H*/

