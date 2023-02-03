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
//#include "graph.h"

typedef struct{
    int bin[7];
    char letre;
    int freq;
}T_box;

char *getText(char c);

T_indirectHeap counting(T_indirectHeap t, char *c); //
//int *counting(char c);
T_indirectHeap initTree(T_indirectHeap t);
//char *initTree(int data[], char c);
T_indirectHeap numElt0(T_indirectHeap t);
//int numElt0(int *data);
T_indirectHeap *initHeap0(T_indirectHeap t, char *c);
//T_indirectHeap *initHeap0(int data[], char tree[], char c, int n);


//-----------------------------------------------------------------------//
//testing functions
void printCode0(T_indirectHeap *t);
void printText0(T_indirectHeap *t, char*c);
void decToBinary(int n);

//-----------------------------------------------------------------------//
T_box *initBoxes(T_box v[], int *occ);
void codage(T_box *v, int Ht[], int nbElt);

void printBoxes(T_box v[], int nbElt);

int nbElt(int *occ);
int *freq(char *texto, int *occ);

//-----------------------------------------------------------------------//



void insertTree(T_indirectHeap *p, int a, int b, int i);

void insertData(T_indirectHeap *p, int a, int b, int i);
void insertHuffTree(int Ht[], int a, int b, int i);

int *huffman(char *texto);

//-----------------------------------------------------------------------//

void completeDotFile(FILE* fp, T_indirectHeap *head, int *huffmanTree);
void generatePNG(char *filename, T_indirectHeap *head, int *huffmanTree);


#endif /* codage_h */
