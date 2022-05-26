#ifndef MAXIMOS_H
#define MAXIMOS_H

#define MINN 1 //menor numero possivel
//#if WIN64//gera entradas para windows 64 bits
#if 1//gera entradas para windows 64 bits
	#define MINT 1000000 //menor tamanho possivel do vetor escolhido para 32bits
	#define MAXT 100000000 //tamanho máximo do vetor escolhido para 64bits
	#define MAXN 20 //maior número de digitos possível(unsigned long long)
#else//gera entradas para windows 32 bits
	#define MINT 10000 //menor tamanho possivel do vetor escolhido para 32bits
	#define MAXT 1000000 //tamanho máximo do vetor escolhido para 32bits
	#define MAXN 20 //maior número possível(unsigned long long)
#endif

#endif /*MAXIMOS_H*/

