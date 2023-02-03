#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h> 

#ifndef codage_h
#define codage_h

#include "traces.h"
#include "check.h"
#include "elt.h"
#include "heapsort_v2.h"
//#include "grafico.c"


typedef struct{
    int bin[7];
    char letre;
    int freq;
	  char bin_str[7];
}T_box;

//-----------------------------------------------------------------------//

void printCode0(T_indirectHeap *t);
void printText0(T_indirectHeap *t, char*c);
void decToBinary(int n);

//-----------------------------------------------------------------------//

//void initBoxes(T_box v[], char ltr[], int n);
T_box *initBoxes(T_box v[], int *occ);
//T_box *codage(T_box v[], T_indirectHeap *t, int Ht[]);
//T_box *codage(T_box v[], int Ht[], int nbElt);
void codage(T_box *v, int Ht[], int nbElt);

void printBoxes(T_box v[], int nbElt);

int nbElt(int *occ);
int *freq(char *texto, int *occ);

//----------------------------------------------------------------------

//-----------------------------------------------------------------------//

void insertTree(T_indirectHeap *p, int a, int b, int i);
int *huffman(char *texto);

//-----------------------------------------------------------------------//


#endif /* codage_h */
