#ifndef MAXIMOS_H
#define MAXIMOS_H

#define TEST 0
#if !TEST
	#if _WIN64
		#define MAXT 100000000llu //tamanho m�ximo do vetor escolhido para 64bits
	#else
		#define MAXT 10000000llu //tamanho m�ximo do vetor escolhido para 32bits
	#endif
	#define MAXN 18446744073709551615llu //maior n�mero poss�vel(unsigned long long 32bit) - grande o bastante
#else
	#define MAXT 1000000llu //teste: tr�s itera��es apenas
	#define MAXN 1000001llu //numero "pequeno" para poucas itera��es
#endif
#define REP  3 //entradas diferentes geradas para aleatorias e pior caso
#define MINT 1000000llu //menor tamanho possivel
#define MINN 10llu //menor numero possivel

#endif /*MAXIMOS_H*/

