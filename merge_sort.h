#ifndef MERGE_H
#define MERGE_H
#include "lista.h"

void MergeSort(struct Lista** headRef);
void FrontBackSplit(struct Lista* source, struct Lista** frontRef, struct Lista** backRef);
struct Lista* SortedMerge(struct Lista* a, struct Lista* b);

#endif /* MERGE_H*/
