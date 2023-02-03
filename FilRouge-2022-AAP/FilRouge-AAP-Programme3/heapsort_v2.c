
#include "heapsort_v2.h"

char *getText(char c){
    char text[1000];
    int i=0;
    while ((c = getchar()) != EOF & i<1000) {
        text[i]=c;
        i++;
    }
  return text;
    
}

T_indirectHeap counting(T_indirectHeap t, char *c) { // give us the vector initial of occurences (pré data)
    int size = strlen(c);
    for (int i=0;i<size;i++) {
        t.data[c[i]]++;
    
    }
  return t;
}

// initialize the tree
T_indirectHeap initTree(T_indirectHeap t) {
  int j = 0;
  for (int i = 0; i < 2 * MAXCARS - 1; i++) {
    if (t.data[i] != 0) {
      t.tree[j++] = i;
      //printf("%i \n", i);
    }
  }
  return t;
}

T_indirectHeap numElt0(T_indirectHeap t) {
  int nb_Elt=0;
  for (int i = 0; i < 2 * MAXCARS - 1; i++) {

    if (t.data[i] != 0) {
      nb_Elt++;
    }
  }
  t.nbElt = nb_Elt;
  return t;
}

T_indirectHeap *initHeap0(T_indirectHeap t, char *c) {
    T_indirectHeap *pAux=malloc(sizeof(T_indirectHeap));
    pAux = &t;
    for (int i = 0; i < 2 * MAXCARS - 1; i++) {
    t.data[i] = 0;
  }
  t = counting(t, c);
  t = initTree(counting(t, c));
  t = numElt0(counting(t, c));
    return pAux;
}


int *initHuffmanTree(void) {
    int *p;
    p = malloc(256*sizeof(int));
    for (int i = 0; i < 2 * MAXCARS - 1; i++) {
    p[i] = -256;
  
  }
  for(int i=0;i<2 * MAXCARS - 1; i++){
    if(p[i] != -256){
      printf("Valor incorreto inicializado");
      }
  }
    return p;
}



void insertData(T_indirectHeap *p, int a, int b, int i){
   int result = p->data[a] + p->data[b];
    p->data[(128+i)] = result;
}
void insertHuffTree(int Ht[], int a, int b, int i){
    Ht[a] = (128 + i);
    Ht[b] = (-1)*(128 + i);
}



//------------------------------------------------------------------------------------------------------------------------------------------------//
/*------------------------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------TRI--------------------------------------------------------------------FONCTIONS-----------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------------*/


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
    T_elt aux;
    assert(p!=NULL);
    aux = p->tree[i];
    p->tree[i] = p->tree[j];
    p->tree[j] = aux;
}

void siftDown(T_indirectHeap *p, int k) {
  int n;
    assert(p!=NULL);
    n = p->nbElt;
    int i;
    if (! isINTREE(k,n)) {
    return;}
     
    while ( ! isLEAF(k,n) ) {
        if (isINTREE(iRCHILD(k),n) && (eltCmp(p->data[VALP(p,iRCHILD(k))],p->data[VALP(p,iLCHILD(k))] < 0))) {
      i = iRCHILD(k);
      }
        else {
      i = iLCHILD(k);
      }
        
        if (eltCmp(p->data[VALP(p,k)],p->data[VALP(p,i)]) > 0) {
            swap(p, k, i);
            k = i;
        } else break;
        
    }
}
void siftUp(T_indirectHeap *p, int k) {
    assert(p!=NULL);
    while ( !isROOT(k) && (eltCmp(VALP(p,k),VALP(p,iPARENT(k))) < 0 ) ) {
        
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
    assert(p!=NULL);
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
    //printf("%c(i:%d)\n",toString(VALP(p,root)), root);
    printf("%c (%d)\n", root, p->data[root] );
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