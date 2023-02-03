
#include "elt.h"
#include "test_utils.h"

#ifndef heapsort_h
#define heapsort_h


//#define MAXHEAP
#define MINHEAP

T_data heapSort_Aux(T_data d, int n); 
T_data heapSort(T_data d, int n);
void makeheap(T_elt arr[], int n, int i);

void swap(T_elt *a, T_elt *b);

void printArray(T_elt arr[], int n);
#endif /* heapsort_h */
