#include <stdlib.h>
#include "merge_sort.h"
#include "lista.h"
#include <stdio.h>
  
/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct No** headRef)
{
	printf("Erro no MergeSort\n");
    struct No* head = (*headRef);
    struct No* a;
    struct No* b;

    /* Base case -- length 0 or 1 */
    if (head == NULL) {
        return;
    }
    if((head->prox == NULL)){
        return;
	}

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}

/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
function */
struct No* SortedMerge(struct No* a, struct No* b)
{
	printf("Erro no SortedMerge1\n");
    struct No* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
	printf("Erro no SortedMerge2\n");

    /* Pick either a or b, and recur */
    if (a->n <= b->n) {
        result = a;
        result->prox = SortedMerge(a->prox, b);
    }
    else {
        result = b;
        result->prox = SortedMerge(a, b->prox);
    }
	printf("Erro no SortedMerge3\n");
    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct No* source, struct No** frontRef, struct No** backRef)
{
	printf("Erro no FrontBackSplit\n");
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
