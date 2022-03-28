#ifndef GFGMERGE_H
#define GFGMERGE_H
#include "lista.h"

double MergeSort(struct No** headRef);
void FrontBackSplit(struct No* source, struct No** frontRef, struct No** backRef);
struct No* SortedMerge(struct No* a, struct No* b);

#endif /* GFGMERGE_H*/
