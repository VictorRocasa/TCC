#include "lista.h" 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void ler_entradas_aleatorias();//funcao para carregar entradas aleatorias
void ler_entradas_ordenadas();//funcao para carregar entradas ordenadas
void ler_entradas_iguais();//funcao para carregar entradas iguais
void ler_entradas_pior_caso();//funcao para carregar entradas pior caso

void mergesort(entrada)//função para realizar o merge sorte na entrada e salvar seus dados
void quicksort(entrada)//função para realizar o quick sort na entrada e salvar seus dados
void timsort(entrada)//função para realizar o tim sort na entrada e salvar seus dados
void radixsort1d(entrada)//função para realizar o radix(1d) sort na entrada e salvar seus dados
void radixsortNd(entrada)//função para realizar o radix(Nd) sort na entrada e salvar seus dados


int main(){
    

    return 0;
}

void ler_entradas_aleatorias(){
    FILE * p;
    p =  fopen("entrada_aleatoria.txt","a");
    fclose(p);
}

void ler_entradas_ordenadas(){
    FILE * p;
    p =  fopen("ordenada_crescente.txt.txt","a");
    
    p =  fopen("ordenada_decrescente.txt.txt","a");
    fclose(p);
}

void ler_entradas_iguais(){
    FILE * p;
    p =  fopen("entrada_igual.txt","a");
    fclose(p);
}

void ler_entradas_pior_caso(){
    FILE * p;
    p =  fopen("pior_caso.txt","a");
    fclose(p);
}


