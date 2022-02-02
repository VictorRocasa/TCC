#include <stdlib.h>
#include "lista.h"

// Returns the last Lista of the list
struct Lista* getTail(struct Lista* cur)
{
    while (cur != NULL && cur->prox != NULL)
        cur = cur->prox;
    return cur;
}
 
// Partitions the list taking the last element as the pivot
struct Lista* partition(struct Lista* head, struct Lista* end,struct Lista** newHead,struct Lista** newEnd)
{
    struct Lista* pivot = end;
    struct Lista *prev = NULL, *cur = head, *tail = pivot;
 
    // During partition, both the head and end of the list
    // might change which is updated in the newHead and
    // newEnd variables
    while (cur != pivot) {
        if (cur->n < pivot->n) {
            // First Lista that has a value less than the
            // pivot - becomes the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;
 
            prev = cur;
            cur = cur->prox;
        }
        else // If cur Lista is greater than pivot
        {
            // Move cur Lista to prox of tail, and change
            // tail
            if (prev)
                prev->prox = cur->prox;
            struct Lista* tmp = cur->prox;
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
 
    // Update newEnd to the current last Lista
    (*newEnd) = tail;
 
    // Return the pivot Lista
    return pivot;
}
 
// here the sorting happens exclusive of the end Lista
struct Lista* quickSortRecur(struct Lista* head,
                            struct Lista* end)
{
    // base condition
    if (!head || head == end)
        return head;
 
    struct Lista *newHead = NULL, *newEnd = NULL;
 
    // Partition the list, newHead and newEnd will be
    // updated by the partition function
    struct Lista* pivot
        = partition(head, end, &newHead, &newEnd);
 
    // If pivot is the smallest element - no need to recur
    // for the left part.
    if (newHead != pivot) {
        // Set the Lista before the pivot Lista as NULL
        struct Lista* tmp = newHead;
        while (tmp->prox != pivot)
            tmp = tmp->prox;
        tmp->prox = NULL;
 
        // Recur for the list before pivot
        newHead = quickSortRecur(newHead, tmp);
 
        // Change prox of last Lista of the left half to
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
void quickSort(struct Lista** headRef)
{
    (*headRef)
        = quickSortRecur(*headRef, getTail(*headRef));
    return;
}
