#ifndef MERGE_H
#define MERGE_H
#include "lista.h"

double MergeSort(struct No** headRef);
void FrontBackSplit(struct No* source, struct No** frontRef, struct No** backRef);
struct No* SortedMerge(struct No* a, struct No* b);

#endif /* MERGE_H*/
