//
//  heapsort_v2.h
//  FilRouge_pt2
//
//  Created by Vitória Bastos on 31/12/22.
//
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>


#ifndef heapsort_v2_h
#define heapsort_v2_h

#include "traces.h"
#include "check.h"
#include "elt.h"

//#define MAXTAB 80

//#define DEBUG
#define MAXCARS 128
////--------------------------------------------------------------/////
#define HEAP_ALLOCATION_OFFSET 5

#define iPARENT(i)               (i-1)/2
#define iLCHILD(i)               (2*i)+1
#define iRCHILD(i)               (2*i)+2
#define iLASTINTERNAL(n)    n/2 -1
#define isINTERNAL(i,n)     (2*i<(n-1))
#define isLEAF(i,n)             (2*i>=(n-1))
#define isINTREE(i,n)          (i<n)
#define isROOT(i)                  (i==0)
#define nbINTERNALS(n)         n/2
#define nbLEAVES(n)             ceil((double)n/2)
#define VALP(pHeap, i)        pHeap->tree[i]
#define VAL(heap, i)            heap.tree[i]
////--------------------------------------------------------------/////



typedef struct {
   unsigned int nbElt; //number effective of the nods
   unsigned char tree[MAXCARS]; //organization of the nods
   int data[2*MAXCARS-1]; // table that contains the occurences
} T_indirectHeap;






int *initHuffmanTree(void);


int searchInt(int *vector, int a);
int search(char *vector, char a);
void swap(T_indirectHeap *t, int a, int b);

void siftDown(T_indirectHeap *p, int k);
void siftUp(T_indirectHeap *p, int k);
void addElt(T_indirectHeap *p, unsigned char e);
T_elt getMax(const T_indirectHeap *p);
T_elt removeMax(T_indirectHeap *p);
void buildHeap(T_indirectHeap *p);
void showHeap_rec(T_indirectHeap *p, int root, int indent);
void showHeap(T_indirectHeap *p);
void heapsort_aux(T_indirectHeap *d);

T_indirectHeap *newHeap(void);


#endif /* heapsort_v2_h */
