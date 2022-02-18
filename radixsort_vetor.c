#include "radixsort_vetor.h"
#include <stdlib.h>
#include <stdio.h>

unsigned long long getMax(unsigned long long * arr, unsigned long long n)
{
    unsigned long long mx = arr[0];
    unsigned long long i;
    for (i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(unsigned long long arr[], unsigned long long n, unsigned long long exp)
{
    unsigned long long * output = (unsigned long long*)malloc(n*sizeof(unsigned long long)); // output array
    unsigned long long i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1;; i--)
    {
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
        if(i == 0)
        	break;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(unsigned long long * arr, unsigned long long n)
{
    // Find the maximum number to know number of digits
    unsigned long long m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    unsigned long long exp;
	for (exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
