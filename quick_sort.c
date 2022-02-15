#include <stdlib.h>
#include "lista.h"

// Returns the last No of the list
struct No* getTail(struct No* cur)
{
    while (cur != NULL && cur->prox != NULL)
        cur = cur->prox;
    return cur;
}
 
// Partitions the list taking the last element as the pivot
struct No* partition(struct No* head, struct No* end,struct No** newHead,struct No** newEnd)
{
    struct No* pivot = end;
    struct No *prev = NULL, *cur = head, *tail = pivot;
 
    // During partition, both the head and end of the list
    // might change which is updated in the newHead and
    // newEnd variables
    while (cur != pivot) {
        if (cur->n < pivot->n) {
            // First No that has a value less than the
            // pivot - becomes the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;
 
            prev = cur;
            cur = cur->prox;
        }
        else // If cur No is greater than pivot
        {
            // Move cur No to prox of tail, and change
            // tail
            if (prev)
                prev->prox = cur->prox;
            struct No* tmp = cur->prox;
            cur->prox = NULL;
            tail->prox = cur;
            tail = cur;
            cur = tmp;
        }
    }
 
    // If the pivot n is the smallest element in the
    // current list, pivot becomes the head
    if ((*newHead) == NULL)
        (*newHead) = pivot;
 
    // Update newEnd to the current last No
    (*newEnd) = tail;
 
    // Return the pivot No
    return pivot;
}
 
// here the sorting happens exclusive of the end No
struct No* quickSortRecur(struct No* head,
                            struct No* end)
{
    // base condition
    if (!head || head == end)
        return head;
 
    struct No *newHead = NULL, *newEnd = NULL;
 
    // Partition the list, newHead and newEnd will be
    // updated by the partition function
    struct No* pivot
        = partition(head, end, &newHead, &newEnd);
 
    // If pivot is the smallest element - no need to recur
    // for the left part.
    if (newHead != pivot) {
        // Set the No before the pivot No as NULL
        struct No* tmp = newHead;
        while (tmp->prox != pivot)
            tmp = tmp->prox;
        tmp->prox = NULL;
 
        // Recur for the list before pivot
        newHead = quickSortRecur(newHead, tmp);
 
        // Change prox of last No of the left half to
        // pivot
        tmp = getTail(newHead);
        tmp->prox = pivot;
    }
 
    // Recur for the list after the pivot element
    pivot->prox = quickSortRecur(pivot->prox, newEnd);
 
    return newHead;
}
 
// The main function for quick sort. This is a wrapper over
// recursive function quickSortRecur()
no * quickSort(struct No** headRef)
{
    (*headRef)
        = quickSortRecur(*headRef, getTail(*headRef));
    return (*headRef);
}
