#include "codage.h"

char *getText(char c){
    char entrada[1000];
    fgets(entrada, 1000, stdin);
    entrada[strlen(entrada) - 1] = '\0';
  return entrada;
    
}

T_indirectHeap counting(T_indirectHeap t, char *c) { // give us the vector initial of occurences (pré data)
    int size = strlen(c);
    for(int i=0;i<2*MAXCARS-1;i++){
        t.data[i]=0;
    }
    
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
 
void printCode0(T_indirectHeap *t){ //print the matrix with the original encoding
    for(int i=0; i<t->nbElt;i++){
        printf("\n | %c (%d) | %d | ",t->tree[i], t->tree[i], t->data[(t->tree[i])]);
        decToBinary(i);
    }
}


void printText0(T_indirectHeap *t, char*c){ //print the text with the original encoding
    int size = strlen(c);
    
    for (int i=0; i<size; i++) {
        
        int j = search(t->tree, c[i]);
        decToBinary(j);
        printf("|\n ");
    }
}



int *freq(char *texto, int *occ){//ok
    //int occ[MAXCARS];//={0};
    int size = strlen(texto);
    for(int k=0;k<MAXCARS;k++){
        occ[k]=0;
    }
    for (int i=0;i<size;i++) {
        occ[texto[i]]++;
    }
    return occ;
}

int nbElt(int *occ){//ok
    int nbElt=0;
    for (int k=0;k<MAXCARS;k++) {
        if(occ[k]!=0){
            nbElt++;
        }
    }
    return nbElt;
}

T_box *initBoxes(T_box v[], int *occ){//ok
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

void printBoxes(T_box v[], int nbElt){//ok
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
   
    T_indirectHeap t;
    T_indirectHeap *Mi=NULL;
    
    Mi = initHeap0(t,texto); // Initializes the initial minimier
    int const ntotale = Mi->nbElt; //Needed for the loop
    int *Ht=initHuffmanTree();
    
    
    buildHeap(Mi); // Réorganisation du minimier
    generatePNG("Dot_Inicial", Mi, Ht);

    int i=0;
    while(Mi->nbElt>1){
        unsigned char f = 128 + i;
        T_elt C1 = removeMax(Mi); // Extraire et réorganiser
        buildHeap(Mi);
        
        T_elt C2 = removeMax(Mi); // Extraire et réorganiser
        buildHeap(Mi);
        
        insertHuffTree(Ht, C1, C2, i);// Ajout dans l’arbre de codage
        insertData(Mi, C1, C2, i); // Ajout dans tableau de frequences
        addElt(Mi, f); //Add the new element in the tree
        buildHeap(Mi);
        i++;
    }
        generatePNG("Dot_Final", Mi, Ht);
         return Ht;
  
}


void completeDotFile(FILE* fp, T_indirectHeap *head, int *huffmanTree) {

    char configs[] = "digraph POT_test { \n node [fontname=\"Arial\", shape=\"circle\", width=0.5];\n";

    fprintf(fp, "%s", configs);

    char LABEL_BEGIN[] = " [label = \"";
    char COLOR_BEGIN[] = "\", color = \"";
    char LABEL_END[] = "\"];\n";
    char LABEL_BRANCH[] = " [label = \" ";
    char SW[] = ":sw -> ";
    char SE[] = ":se -> ";
    char BUFFER[100] = {0};
    char valeur_str[15];
    char tree_str[] = "00";
    char coleur1_str [] = "red";
    char coleur2_str [] = "green";

    int valeur_1, valeur_2, valeur_3, i, j;

    for (i=MAXCARS;i<2*MAXCARS-1;i++) {
            if(head->data[i] != 0) {
                valeur_1=i;
                for (j=0;j<2*MAXCARS-1;j++) {
                    if(huffmanTree[j] == -i) valeur_2=j;
                    if(huffmanTree[j] == i) valeur_3=j;
                }
    
          sprintf(valeur_str, "%d", valeur_1);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, tree_str);
        strcat(BUFFER, LABEL_BEGIN);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, COLOR_BEGIN);
        strcat(BUFFER, coleur1_str);
        strcat(BUFFER, LABEL_END);
        fprintf(fp, "%s", BUFFER);
        memset(BUFFER, 0, 100);

        sprintf(valeur_str, "%d", valeur_1);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, tree_str);
        strcat(BUFFER, SW);
        sprintf(valeur_str, "%d", valeur_2);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, tree_str);
        strcat(BUFFER, LABEL_BRANCH);
        sprintf(valeur_str, "%d", 0);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, COLOR_BEGIN);
        strcat(BUFFER, coleur1_str);
        strcat(BUFFER, LABEL_END);
        fprintf(fp, "%s", BUFFER);
        memset(BUFFER, 0, 100);

        sprintf(valeur_str, "%d", valeur_1);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, tree_str);
        strcat(BUFFER, SE);
        sprintf(valeur_str, "%d", valeur_3);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, tree_str);
        strcat(BUFFER, LABEL_BRANCH);
        sprintf(valeur_str, "%d", 1);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, COLOR_BEGIN);
        strcat(BUFFER, coleur1_str);
        strcat(BUFFER, LABEL_END);
        fprintf(fp, "%s", BUFFER);
        memset(BUFFER, 0, 100);
            }
    }

        for (i=0;i<MAXCARS;i++) {
            if(huffmanTree[i] != -256) {
                valeur_1 = i;
                sprintf(valeur_str, "%d", valeur_1);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, tree_str);
        strcat(BUFFER, LABEL_BEGIN);
        sprintf(valeur_str, "%c", valeur_1);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, COLOR_BEGIN);
        strcat(BUFFER, coleur1_str);
        strcat(BUFFER, LABEL_END);
        fprintf(fp, "%s", BUFFER);
        memset(BUFFER, 0, 100);
            }
        }

    int n;
        n = head->nbElt;
        for(i=0;i<n;i++) {
            valeur_1 = head->tree[i];
            
            sprintf(valeur_str, "%d", valeur_1);
      strcat(BUFFER, valeur_str);
      strcat(BUFFER, LABEL_BEGIN);
            if(valeur_1<128){
          sprintf(valeur_str, "%c", valeur_1);
            } else {
                sprintf(valeur_str, "%d", valeur_1);
            }
      strcat(BUFFER, valeur_str);
      strcat(BUFFER, "(");
            sprintf(valeur_str, "%d", head->data[valeur_1]);
          strcat(BUFFER, valeur_str);
          strcat(BUFFER, ")");
      strcat(BUFFER, COLOR_BEGIN);
      strcat(BUFFER, coleur2_str);
      strcat(BUFFER, LABEL_END);
      fprintf(fp, "%s", BUFFER);
      memset(BUFFER, 0, 100);
            
            if (isINTREE(iLCHILD(i),n)) {
                valeur_2 = VALP(head,iLCHILD(i));
                
                sprintf(valeur_str, "%d", valeur_1);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, SW);
        sprintf(valeur_str, "%d", valeur_2);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, LABEL_BRANCH);
        sprintf(valeur_str, "%c", ' ');
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, COLOR_BEGIN);
        strcat(BUFFER, coleur2_str);
        strcat(BUFFER, LABEL_END);
        fprintf(fp, "%s", BUFFER);
        memset(BUFFER, 0, 100);
            }

            if (isINTREE(iRCHILD(i),n)) {
                valeur_3 = VALP(head,iRCHILD(i));
                
                sprintf(valeur_str, "%d", valeur_1);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, SE);
        sprintf(valeur_str, "%d", valeur_3);
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, LABEL_BRANCH);
        sprintf(valeur_str, "%c", ' ');
        strcat(BUFFER, valeur_str);
        strcat(BUFFER, COLOR_BEGIN);
        strcat(BUFFER, coleur2_str);
        strcat(BUFFER, LABEL_END);
        fprintf(fp, "%s", BUFFER);
        memset(BUFFER, 0, 100);
            }
        }

    fputc('}', fp);
    return;
}

void generatePNG(char *filename, T_indirectHeap *head, int *huffmanTree) {
    char command[50] = {0};
    char png_file[20] = {0};

    // on cree et rempli le fichier .dot
    FILE* fichier = fopen(filename, "w");
    if (fichier == NULL) {
      printf("Erreur d'ouverture de .dot file.\n");
      exit(1);
    }

    completeDotFile(fichier, head, huffmanTree);
    fclose(fichier);

    strcpy(png_file, filename);
    png_file[strlen(png_file) - 3] = 'p';
    png_file[strlen(png_file) - 2] = 'n';
    png_file[strlen(png_file) - 1] = 'g'; // last position

    strcpy(command, "dot ");
    strcat(command, filename);
    strcat(command, " -T png -o ");
    strcat(command, png_file);

    int res = system(command);  // Créer une image
    if (res == -1) {
        printf("Erreur de génération d'image.\n");
    }

    return;
}
