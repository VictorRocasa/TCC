#ifndef QUICK_H
#define QUICK_H
#include "lista.h"

struct Lista* getTail(struct Lista* cur);
struct Lista* partition(struct Lista* head, struct Lista* end, struct Lista** newHead, struct Lista** newEnd);
struct Lista* quickSortRecur(struct Lista* head, struct Lista* end);
void quickSort(struct Lista** headRef);

#endif /* QUICK_H*/
