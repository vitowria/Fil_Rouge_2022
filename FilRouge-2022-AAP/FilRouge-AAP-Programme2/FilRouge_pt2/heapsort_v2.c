//
//  heapsort_v2.c
//  FilRouge_pt2
//
//  Created by Vitória Bastos on 31/12/22.
//
//
//  heapsort_v2.c
//  FilRouge_pt2
//
//  Created by Vitória Bastos on 31/12/22.
//

#include "heapsort_v2.h"






int searchInt(int *vector, int a){
    int j=0;
    for(int i=0; i<MAXCARS; i++){
        j++;
        if (vector[i]==a) {
            i=MAXCARS-1;
        }
    }
    return j;
}

int search(char *vector, char a){
    int j=0;
    for(int i=0; i<MAXCARS; i++){
        j++;
        if (vector[i]==a) {
            i=MAXCARS-1;
        }
    }
    return j;
}

void swap(T_indirectHeap *p, int i, int j) {
    unsigned char aux;
    assert(p!=NULL);
    aux = p->tree[i];
    p->tree[i] = p->tree[j];
    p->tree[j] = aux;
}

void siftDown(T_indirectHeap * p, int k) {
    int n;
    assert(p!=NULL);
    n = p->nbElt; //stats.nbOperations ++;
    int i;

    //stats.nbComparisons ++;
    if (!isINTREE(k,n)) return;
     
    while (!isLEAF(k,n) ) { //stats.nbComparisons ++;

        //stats.nbComparisons ++;
        //stats.nbOperations ++;
        if (isINTREE(iRCHILD(k),n)){
            //stats.nbComparisons ++;
            if ((p->data[VALP(p,iRCHILD(k))]) - (p->data[VALP(p,iLCHILD(k))]) == 0) {
                //stats.nbComparisons ++;
                if (VALP(p,iRCHILD(k)) < 128 && VALP(p,iLCHILD(k)) < 128) {
                    if((VALP(p,iRCHILD(k)) - VALP(p,iLCHILD(k))) < 0) i = iLCHILD(k);
                    else i = iRCHILD(k);
                }
                else {
                    if((VALP(p,iRCHILD(k)) - VALP(p,iLCHILD(k))) < 0) i = iRCHILD(k);
                    else i = iLCHILD(k);
                }
            }
            else {
                //stats.nbComparisons ++;
                if ((p->data[VALP(p,iRCHILD(k))]) - (p->data[VALP(p,iLCHILD(k))]) < 0)
                i = iRCHILD(k);
                else i = iLCHILD(k);
            }
        }
        else i = iLCHILD(k);
        
        if ((p->data[VALP(p,k)]) - (p->data[VALP(p,i)]) > 0) {
            swap(p, k, i);
            k = i;
        }
        else {
            if ((p->data[VALP(p,k)]) - (p->data[VALP(p,i)]) == 0) {
    
                if (VALP(p,k) < 128 && VALP(p,i) < 128) {
                    if((VALP(p,k) - VALP(p,i)) < 0) {
                        swap(p, k, i);
                        k = i;
  
                    } else break;
                }
                else {
                    if(p->data[VALP(p,k)] - p->data[VALP(p,i)] > 0) {
                        swap(p, k, i);
                        k = i;
                        //stats.nbOperations ++;
                    } else break;
                }
            } else break;
        }
        
    }
}
void siftUp(T_indirectHeap *p, int k) {
    assert(p!=NULL);
    while ( !isROOT(k) && (eltCmp(p->data[VALP(p,k)],p->data[VALP(p,iPARENT(k))]) < 0 ) ) {
        
        swap(p,  k,  iPARENT(k));
        k = iPARENT(k);
    }
}

T_indirectHeap * newHeap(void){
  T_indirectHeap* pAux;
    CHECK_IF(pAux = malloc(sizeof(T_indirectHeap)), NULL, "erreur malloc");
    //CHECK_IF(pAux->tree = malloc(MAXCARS * sizeof(T_elt)), NULL, "erreur malloc");
    pAux->nbElt = 0;
    
    //pAux->nbMaxElt = nbMaxElt;
    return pAux;

}

void freeHeap(T_indirectHeap *p) {
    assert(p!=NULL);
    free(p->tree);
    free(p);
}


T_indirectHeap *initHeap(T_elt t[], int n, int *occ) {
    T_indirectHeap *pAux = newHeap();
    memcpy(pAux->tree, t, n*sizeof(T_elt));
    memcpy(pAux->data, occ, (2*MAXCARS-1)*sizeof(int));
    //pAux->nbMaxElt = MAXCARS;
    pAux->nbElt = n;
    return pAux;
}






void addElt(T_indirectHeap *p, unsigned char e) {
    assert(p!=NULL);
    p->tree[p->nbElt] = e;
    p->nbElt++;
    siftUp(p,p->nbElt-1);
    buildHeap(p);
}


T_elt getMax(const T_indirectHeap *p){
    assert(p!=NULL);
    return p->tree[0];
}

T_elt removeMax(T_indirectHeap *p) {
    T_elt aux;
    assert(p!=NULL);
    //aux = p->tree[p->nbElt-1];
    aux = p->tree[0];
    swap(p,0,p->nbElt-1);//get the first
    p->nbElt--;
    siftDown(p,0);
    return aux;
}



void buildHeap(T_indirectHeap *p){
    int k;
    int n;
    //assert(p!=NULL);
    n = p->nbElt;
    for(k=iLASTINTERNAL(n); k>=0; k--) {
        siftDown(p,k);
    }
}



void showHeap_rec(T_indirectHeap *p, int root, int indent) {
    // affiche récursivement en mode pseudo graphique
    // ordre de récurrence  : taille du sous-arbre
    int i;
    assert(p!=NULL);
    if (! isINTREE(root,p->nbElt)) return;
    
    showHeap_rec(p, iRCHILD(root), indent+1);
    for(i=0;i<indent;i++) {
        printf("\t");
    }
    printf("(%c)[%d] %d\n",VALP(p,root), p->data[VALP(p,root)], root);
    //printf("%c (%d)\n", root, p->data[root] );
    showHeap_rec(p, iLCHILD(root), indent+1);
}
void showHeap(T_indirectHeap *p) {
    assert(p!=NULL);
    printf("Affichage du tas (nbElt : %d)\n",p->nbElt);
    showHeap_rec(p,0,0);
}

void heapsort_aux(T_indirectHeap *d) {
    assert((d)!=NULL);
    buildHeap(d);
    while((d)->nbElt>1) {
        removeMax(d);
    }
}
