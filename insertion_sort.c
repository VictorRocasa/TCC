#include <stdlib.h>
#include "lista.h"
#include "insertion_sort.h"

//https://stackoverflow.com/questions/13443795/using-insertion-sort-on-a-singly-linked-list
void insertion(struct Lista **raiz) {
    if((*raiz)== NULL) 
       return;
    if((*raiz)->prox == NULL)
    	return;
    struct Lista *t1 = (*raiz)->prox;
    while(t1 != NULL) {
        unsigned long long sec_data = t1->n;
        unsigned long long found = 0;
        struct Lista *t2 = *raiz;
        while(t2 != t1) {
            if(t2->n > t1->n && found == 0) {
                sec_data = t2->n;
                t2->n = t1->n;
                found = 1;
                t2 = t2->prox;
            } else {
                if(found == 1) {
                    unsigned long long temp = sec_data;
                    sec_data = t2->n;
                    t2->n = temp;
                }
                t2 = t2->prox;
            }
       }
       t2->n = sec_data;
       t1 = t1->prox;
    }
}
