#include <stdlib.h>
#include "merge_sort.h"
#include "lista.h"
  
/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct Lista** headRef)
{
    struct Lista* head = *headRef;
    struct Lista* a;
    struct Lista* b;

    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->prox == NULL)) {
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
struct Lista* SortedMerge(struct Lista* a, struct Lista* b)
{
    struct Lista* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (a->n <= b->n) {
        result = a;
        result->prox = SortedMerge(a->prox, b);
    }
    else {
        result = b;
        result->prox = SortedMerge(a, b->prox);
    }
    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(struct Lista* source, struct Lista** frontRef, struct Lista** backRef)
{
    struct Lista* fast;
    struct Lista* slow;
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
