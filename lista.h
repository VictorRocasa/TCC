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
    double picoMemoria;
    
}lista;

lista * cria_lista();//inicia uma nova estrutura auxiliar
no * aloca_no(unsigned long long n);//aloca e retorna um novo no
no * adiciona_no(lista * l, no * anterior, unsigned long long n);//adiciona um novo no apos o anterior e retorna esse novo no para ser o novo anterior
lista * desaloca_lista(lista * l);//desaloca a lista inteira e a estrutura auxiliar, retornando NULL
void imprimir_lista(lista * l);//imprime a lista na tela(para debug)

#endif /*LISTA_H*/

