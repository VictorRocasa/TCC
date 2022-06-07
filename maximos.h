#ifndef MAXIMOS_H
#define MAXIMOS_H

#define MINN 1 //menor numero possivel
	#define MINT 1000000 //menor tamanho possivel do vetor escolhido
#if WIN64//gera entradas para windows 64 bits
	#define MAXT 100000000 //tamanho m�ximo do vetor escolhido para 64bits
	#define MAXN 20 //maior n�mero de digitos poss�vel(unsigned long long)
#else//gera entradas para windows 32 bits
	#define MAXT 1000000 //tamanho m�ximo do vetor escolhido para 32bits
	#define MAXN 14 //maior n�mero de digitos poss�vel para 32bits
#endif

#endif /*MAXIMOS_H*/

