#include <stdlib.h>
#include "gfg_merge.h"
#include "lista.h"
#include <stdio.h>
#include <windows.h>
#include <psapi.h>
  
/* sorts the linked list by changing next pointers (not data) */
double MergeSort(struct No** headRef)
{
	//printf("Erro no MergeSort\n");
    struct No* head = (*headRef);
    struct No* a;
    struct No* b;

    /* Base case -- length 0 or 1 */
    if (head == NULL) {
	    PROCESS_MEMORY_COUNTERS pmc;//variavel para acessar os dados da memoria primaria
	    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));//Coleta os dados da memoria do processo
	    return (double) pmc.WorkingSetSize/1000000;
    }
    if(head->prox == NULL){	    
		PROCESS_MEMORY_COUNTERS pmc;//variavel para acessar os dados da memoria primaria
	    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));//Coleta os dados da memoria do processo
	    return (double) pmc.WorkingSetSize/1000000;
	}

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    double amem = MergeSort(&a);
    double bmem = MergeSort(&b);
    
    

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
    if(amem > bmem)//retorna a maior memoria usada
    	return amem;
    else
    	return bmem;
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
struct No* SortedMerge(struct No* a, struct No* b)
{
	//printf("Erro no SortedMerge1\n");
    struct No* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
	//printf("Erro no SortedMerge2\n");

    /* Pick either a or b, and recur */
    if (a->n <= b->n) {
        result = a;
        result->prox = SortedMerge(a->prox, b);
    }
    else {
        result = b;
        result->prox = SortedMerge(a, b->prox);
    }
	//printf("Erro no SortedMerge3\n");
    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct No* source, struct No** frontRef, struct No** backRef)
{
	//printf("Erro no FrontBackSplit\n");
    struct No* fast;
    struct No* slow;
    slow = source;
    fast = source->prox;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->prox;
        if (fast != NULL) {
            slow = slow->prox;
            fast = fast->prox;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->prox;
    slow->prox = NULL;
}

///////////////////////////////////////////////////////////////////////////////////
