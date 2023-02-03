
#include <stdio.h>
#include <string.h>

#include "include/traces.h"
#include "heapsort.h"




void swap(T_elt *a, T_elt *b){
    T_elt temp = *b;
    *b = *a;
    *a = temp;
    ++stats.nbOperations;
}

void printArray(T_elt arr[], int n){
  for (int i = 0; i < n; ++i){
      printf("(%d)", arr[i]);
  }
printf("\n");
}

T_data heapSort_Aux(T_data d, int n){
    T_elt *arr = d.pElt;
    int lastNonLeafNode = (n / 2)-1 ;
    for (int i = lastNonLeafNode; i >= 0; i--){
        ++stats.nbComparisons;
        makeheap(arr, n, i);
    }
    return genData(0, arr);
}


T_data heapSort(T_data d, int n){
  //Here n = Number of elements +1
    T_data Aux2 = heapSort_Aux(d, n);
    T_elt *Aux1 = Aux2.pElt;
    T_elt *Finale;
    Finale = Aux1;
    
    for (int i=0; i<n; i++) {
        Finale[i] = Aux1[i];
        heapSort_Aux(genData(0, &Aux1[i]), n-(i));
   }
    return genData(0, Finale);
}


#ifdef MAXHEAP


// Size of heap is n

void makeheap(T_elt arr[], int n, int i){
    
int largest = i; // Initialize largest as root
int leftChild = 2 * i + 1; // left child = 2*i + 1
int rightChild = 2 * i + 2; // right child = 2*i + 2

// If left child is greater than root

    if (leftChild < n && arr[leftChild] > arr[largest]){
        largest = leftChild;
        ++stats.nbComparisons;
        //++stats.nbOperations;
    }

// If right child is greater than new largest

    if (rightChild < n && arr[rightChild] > arr[largest]){
        largest = rightChild;
        ++stats.nbComparisons;
        //++stats.nbOperations;
    }

// If largest is not the root

    if (largest != i){
// swap root with the new largest
        swap(&arr[i], &arr[largest]);
    }
}



#endif



#ifdef MINHEAP


void makeheap(T_elt arr[], int n, int i){
    
int largest = i; // Initialize largest as root
int leftChild = 2 * i + 1; // left child = 2*i + 1
int rightChild = 2 * i + 2; // right child = 2*i + 2

// If left child is greater than root

    if (leftChild < n && arr[leftChild] < arr[largest]){
        largest = leftChild;
        ++stats.nbComparisons;
       // ++stats.nbOperations;
    }

// If right child is greater than new largest

    if (rightChild < n && arr[rightChild] < arr[largest]){
        largest = rightChild;
        ++stats.nbComparisons;
        //++stats.nbOperations;
    }

// If largest is not the root

if (largest != i){
// swap root with the new largest
    swap(&arr[i], &arr[largest]);
}
}



#endif


