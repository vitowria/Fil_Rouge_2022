#include "codage.h"



void decToBinary(int n){
    // array to store binary number
    int binaryNum[32];
  
    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
      }
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--)
        printf(" %d ", binaryNum[j]);
    printf("|\n ");
}
 
void printCode0(T_indirectHeap *t){ //print the matrix with the original encoding (testing)
    for(int i=0; i<t->nbElt;i++){
        printf("\n | %c (%d) | %d | ",t->tree[i], t->tree[i], t->data[(t->tree[i])]);
        decToBinary(i);
    }
}


void printText0(T_indirectHeap *t, char*c){ //print the text with the original encoding (testing)
    int size = strlen(c);
    for (int i=0; i<size; i++) {
        int j = search(t->tree, c[i]);
        decToBinary(j);
        printf("|\n ");
    }
}


int *freq(char *texto, int *occ){//Give us the array os frequences of each character 
    int size = strlen(texto);
    for(int k=0;k<MAXCARS;k++){
        occ[k]=0;
    }
    for (int i=0;i<size;i++) {
        occ[texto[i]]++;
    }
    return occ;
}

int nbElt(int *occ){//Give the number of elements distincts in the entry
    int nbElt=0;
    for (int k=0;k<MAXCARS;k++) {
        if(occ[k]!=0){
            nbElt++;
        }
    }
    return nbElt;
}

T_box *initBoxes(T_box v[], int *occ){//Initializes the boxes with the character, their frequence and bin[7]={-1};
    T_box *pBox=v;
    pBox=malloc(nbElt(occ)*sizeof(T_box));
    int l=0;
    for(int i=0;i<MAXCARS;i++){
        if(occ[i]!=0){
            pBox[l].letre = i;
            pBox[l].freq = occ[i];
            for(int k=0;k<7;k++){
                pBox[l].bin[k]=-1;
            }
            l++;
            //pBox++;
        }
    }
    return pBox;
}

void printBoxes(T_box v[], int nbElt){//For testing the boxes and their content
    for(int i=0;i<nbElt;i++){
        printf("\n| %c | %d | %d | ", v[i].letre, v[i].letre, v[i].freq);
        for(int j=0;j<7;j++){
            if(v->bin[j]!=-1){
                printf("%d", v[i].bin[j]);
            }
        }
        printf("\n");
        }
}





void codage(T_box *v, int Ht[], int nbElt){ 
    int indiceHt =v->letre;
    int indiceBin;
    
    for(indiceBin=0;indiceBin<7;indiceBin++){
        //printf(" %d %d %d\n ", indiceBin, indiceHt, Ht[indiceHt]);
        if(Ht[indiceHt]==126+nbElt){
            v->bin[indiceBin]=1;
            break;
        }
        if(Ht[indiceHt]==(-1)*(126+nbElt)){
            v->bin[indiceBin]=0;
            break;
        }
        else{
            if(Ht[indiceHt]>0){
                v->bin[indiceBin]=1;
                indiceHt=Ht[indiceHt];
            }
            else{
                v->bin[indiceBin]=0;
                indiceHt=-Ht[indiceHt];
            }
        }
    }
    
    
}





int *huffman(char *texto){
    
    //int *p;
    //char *texto;
    
    T_indirectHeap t;
    T_indirectHeap *Mi=NULL;
    
    Mi = initHeap0(t,texto); // Initializes the initial minimier

		//createDotPOT(Mi, 2*MAXCARS - 1, "teste");
		
    int const ntotale = Mi->nbElt; //Needed for the loop
   
    printf("Inicializando Huffman Tree \n");
   
    int *Ht=initHuffmanTree();
    
    printf("Huffman tree inicializada \n"); // Initialisation de l’arbre de codage
    printf("Inicializando heapSort \n");
    //showHeap(Mi);
    buildHeap(Mi); // Réorganisation du minimier

		//createDotPOT(Mi, 2*MAXCARS - 1 , "teste");
    
    for(int k=0; k<Mi->nbElt;k++){
        printf("%d ", Mi->tree[k]);
    }
    
    printf("%d\n", Mi->nbElt);
    int i=0;
    while(Mi->nbElt>1){
        unsigned char f = 128 + i;
        T_elt C1 = removeMax(Mi); // Extraire et réorganiser
        buildHeap(Mi);
        printf("Tirou C1\n");
        for(int k=0; k<Mi->nbElt;k++){
            printf("%d ", Mi->tree[k]);
        }
               printf("\n");
        T_elt C2 = removeMax(Mi); // Extraire et réorganiser
        printf("Tirou C2\n");

				//createDotPOT(Mi, 2*MAXCARS - 1 , "teste");
			
        for(int k=0; k<Mi->nbElt;k++){
            printf("%d ", Mi->tree[k]);
        }
               printf("\n");
        buildHeap(Mi);
        printf("bouild heap\n");
        for(int k=0; k<Mi->nbElt;k++){
            printf("%d ", Mi->tree[k]);
        }
               printf("\n");
        insertHuffTree(Ht, C1, C2, i);// Ajout dans l’arbre de codage

				//createDotPOT(Ht, 2*MAXCARS - 1 , "teste");
			
        insertData(Mi, C1, C2, i); // Ajout dans tableau de frequences
        //printf("%d\n", Mi->data[128+i]);
        
        
        addElt(Mi, f); //Add the new element in the tree
        //buildHeap(Mi);
    
        i++;
    }

         return Ht;
  
}


