#ifndef MAXIMOS_H
#define MAXIMOS_H

#define MINN 10llu //menor numero possivel
#if WIN64//gera entradas para windows 64, onde serao realizados os testes
	#define REP  1 //entradas diferentes geradas para aleatorias e pior caso
	#define MINT 10llu //menor tamanho possivel do vetor escolhido para 32bits
	#define MAXT 100000llu //tamanho máximo do vetor escolhido para 64bits
	#define MAXN 18446744073709551615llu //maior número possível(unsigned long long 32bit) - grande o bastante
#else//gera entradas para o computador do trabalho de 32 bits
	#define REP  1 //entradas diferentes geradas para aleatorias e pior caso
	#define MINT 10000llu //menor tamanho possivel do vetor escolhido para 32bits
	#define MAXT 1000000llu //tamanho máximo do vetor escolhido para 32bits
	#define MAXN 18446744073709551615llu //maior número possível(unsigned long long 32bit) - grande o bastante
#endif

#endif /*MAXIMOS_H*/

