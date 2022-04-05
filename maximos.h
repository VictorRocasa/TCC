#ifndef MAXIMOS_H
#define MAXIMOS_H

#define MINN 10llu //menor numero possivel
#if WIN64//gera entradas para windows 64 bits
	#define MINT 1000000llu //menor tamanho possivel do vetor escolhido para 32bits
	#define MAXT 100000000llu //tamanho máximo do vetor escolhido para 64bits
	#define MAXN 18446744073709551615llu //maior número possível(unsigned long long 32bit) - grande o bastante
#else//gera entradas para windows 32 bits
	#define MINT 10000llu //menor tamanho possivel do vetor escolhido para 32bits
	#define MAXT 1000000llu //tamanho máximo do vetor escolhido para 32bits
	#define MAXN 18446744073709551615llu //maior número possível(unsigned long long 32bit) - grande o bastante
#endif

#endif /*MAXIMOS_H*/

