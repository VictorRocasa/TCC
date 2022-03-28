#ifndef GFGQUICK_H
#define GFGQUICK_H
#include "lista.h"

struct No* getTail(struct No* cur);
struct No* partition(struct No* head, struct No* end, struct No** newHead, struct No** newEnd);
struct No* quickSortRecur(struct No* head, struct No* end);
no * quickSort(struct No** headRef);

#endif /* GFGQUICK_H*/
