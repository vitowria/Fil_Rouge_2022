#include <stdio.h>


//#define CLEAR2CONTINUE
#include "traces.h"
#include "codage.h"
//#include "graph.h"

int *converterText(char *entrada, T_box *v, int nbelt, int size_string);
int nbChar(int *occ);
int searchBox(T_box *v, char a, int nbBoxes);
void taxes(float nbHf, float nbCode);
int sizeCode(int n, int nchar);
int sizeCodeHf(char *entrada, T_box *v, int nbelt, int size_string);

int main(int argc, char ** argv) {

    CLRSCR();
    WHOAMI();
    FILE *output;
    char c=0;
    char *entrada;
    int *Tout;
    int *Ht=NULL; //The huffman tree
   
    printf("Inicializando Heap \n");
    entrada = getText(c); //Obtain the text to compress and stores in entrada
    
    int *occ=malloc(MAXCARS*sizeof(int));
    occ = freq(entrada, occ);//Recreates the occurences vector
    
    int nbelt=nbElt(occ); //Number of diferent characters in the entry
    int size_string = nbChar(occ); //Number of characters in the entry text
    T_box *pcaixa; //The vector containing the result of the compression
    
    pcaixa=initBoxes(pcaixa, occ);
    Ht=huffman(entrada);
    
    output = fopen("saidas.txt", "w");
    if(output == NULL){
      printf("Erro na abertura do arquivo!");
    }
    
    for(int l=0; l<nbelt;l++){
        printf("\n");
        codage(&pcaixa[l], Ht, nbElt(occ));
        printf("\n | %c | %d | ", pcaixa[l].letre, pcaixa[l].freq);
        fprintf(output, "%c, %d,", pcaixa[l].letre, pcaixa[l].freq);
        for(int k=6;k>-1;k--){
            if(pcaixa[l].bin[k]!=-1){
                printf("%d ", pcaixa[l].bin[k]);
                fprintf(output,"%d", pcaixa[l].bin[k]);
            }
        }
        fprintf(output,"\n");
        printf("|\n");
        
    }
    fprintf(output,"END OF FILE,\n");
        
    //----------------------------------------------------------------------------------------------------------------
    
    printf("Le code de Huffman est: ");
    Tout=converterText(entrada, pcaixa,nbelt, size_string);
    int nbHf = sizeCodeHf(entrada, pcaixa,  nbelt,  size_string);
    int nbCode = sizeCode(nbelt, size_string);
    taxes(nbHf,  nbCode);
    
    for(int i=0;i<nbHf;i++){
        fprintf(output,"%d", Tout[i]);
    }
    
    fclose(output);
    
    //----------------------------------------------------------------------------------------------------------------
}

int *converterText(char *entrada, T_box *v, int nbelt, int size_string){
    
    int *saida;
    int l;
    int r=0;
    saida=malloc(7000*sizeof(int));
    
    for(int i=0;i<size_string;i++){
        l=searchBox(v, entrada[i] , nbelt);
        for (int j=6; j>-1; j--) {
            if(v[l].bin[j]!=-1){
                saida[r]=v[l].bin[j];
                printf("%d", v[l].bin[j]);
                //fprintf(output,"%d", v[l].bin[j]);
                r++;
                
            }
            //else{j--;}
        }
    }
        
    return saida;
}


int searchBox(T_box *v, char a, int nbBoxes){
    T_box *pv;
    int i;
    for(i=0;i<nbBoxes;i++){
        pv=&v[i];
        if(pv->letre==a) break;
    }
    return i;
}


int nbChar(int *occ){
    int nb=0;
    for(int i=0;i<128;i++){
        nb=nb+occ[i];
    }
    return nb;
}

void taxes(float nbHf, float nbCode){
    float tax = 100 * (nbHf)/(nbCode);
    printf("\nLongueur du code binaire : %.0f bits\n", nbCode);
    printf("Longueur du code de huffman : %.0f bits \n", nbHf);
    printf("Ratio de compression : %.2f \n", tax);
    
}

int sizeCode(int n, int nchar){
    int result=0;
    while (n > 0) {
        // storing remainder in binary array
        n = n / 2;
        result++;
    }
    return result*nchar;
}

int sizeCodeHf(char *entrada, T_box *v, int nbelt, int size_string){
    int l;
    int size=0;
    
    for(int i=0;i<size_string;i++){
        l=searchBox(v, entrada[i] , nbelt);
        for (int j=0; j<7; j++) {
            if(v[l].bin[j]!=-1){
                size++;
            }
            else{j++;}
        }
    }
        
    return size;
}
