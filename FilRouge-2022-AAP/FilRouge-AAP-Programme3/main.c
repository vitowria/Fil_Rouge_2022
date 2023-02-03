#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

//#define CLEAR2CONTINUE
#include "include/traces.h"
#include "codage.h"

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
        tok && *tok;
        tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int main(void) {
  char file[] = "archive_test.txt"; 
  printf("Opening file: %s \n",file);
  FILE *stream = fopen(file, "r");
  printf("Opened file: %s \n",file);
  char phrase_bin[200];
  char endoftable[1024] = "END OF TABLE";
  char caract;
  char intermed[7];

  int m=0;
  char line[1024];
  while (fgets(line, 1024, stream)){
    m++; 
  }
  m=m-2;
  rewind(stream);

  T_box vecteur_lettres[m];
  
  for(int j=1; j<=3; j++){
    int i = 0;
    int space = 0;
    char line[1024];
  
    while (fgets(line, 1024, stream)){
      char* tmp = strdup(line);
      if(j==1){
        if(i<m){
	        vecteur_lettres[i].letre = getfield(tmp, j)[0];
        }
      }
      if(j==3){
        if(i<m){
          strcpy(vecteur_lettres[i].bin_str, getfield(tmp, j));
        }
      }
      
      //printf("Element %d would be %s\n", i, getfield(tmp, j));
      if(space == 1){
        strcpy(phrase_bin, getfield(tmp, j));
        printf("Phrase codifié en binaire: %s \n", phrase_bin);
        space = 0;
      }
      if(j==1){
        if((strcmp(getfield(tmp, j), endoftable)==0)){
        // salvar o codigo binario
        space = 1;
        }
      }
      free(tmp);
      i++;
    }
    rewind(stream);
  }
  int longueur_vec_l = sizeof(vecteur_lettres)/sizeof(vecteur_lettres[0]);
	//printf("%d\n", longueur_vec_l);

  // DECODIFICATION
	//char lettre_bin[phrase_bin];
  char *lettre_bin = calloc(strlen(phrase_bin), sizeof(char));
  char str_l_bin[15];
	//char str_l_bin[10];
  char phrase_decod;

	//printf("%s\n", lettre_bin);
  int counter = 0;
  printf("Phrase decodifié: ");
  for(int i=0; i<strlen(phrase_bin); i++) { // percorrendo a string
    caract = phrase_bin[i];
    //printf("Caracter sendo adicionado: %c \n", caract);
		// printf("%s\n", lettre_bin);
		lettre_bin[counter] = caract;
		counter++;
    //strcat(lettre_bin, &caract); //concatena as strings pra ir formando as letras
		 //printf("%s\n", lettre_bin);
    //printf("String lettre_bin concatenada: %s\n",  lettre_bin);
    //break;
    for(int j=0; j<longueur_vec_l;j++) { //percorre o vetor com os structs das letras
			if (strcmp(lettre_bin, vecteur_lettres[j].bin_str) == 0) {
          //printf("Próxima letra \n");
					printf("%c", vecteur_lettres[j].letre);
					memset(lettre_bin, '\0', strlen(phrase_bin)*sizeof(char));
					counter = 0;
					break;
			}

			/*
			for(int k=0; k<(sizeof(vecteur_lettres[j])/sizeof(vecteur_lettres[j].bin));k++) {
        if(vecteur_lettres[j].bin[k]!=-1){
          snprintf(str_l_bin, 10, "%d", vecteur_lettres[j].bin[k]); //converte o código binário para string
        }else{break;}
      }
      
			if(strcmp(str_l_bin, lettre_bin) == 0){ //se já tiver uma letra que corresponde ao código montado
        phrase_decod = *strcat(&phrase_decod, &vecteur_lettres[j].letre); //montar frase decod com a letra
        lettre_ok = 1; // letra encontrada
        lettre_bin = ""; //resetar letra a ser adicionada
        break; //quebrar o ciclo  se letra já tiver sido encontrada
      }

			*/

		
    }

		
  }
  printf("\n");
  return 0;

	

	
}



/*
void decod(T_box vecteur_lettres, char phrase_bin, ){
  int longueur_vec_l = sizeof(vecteur_lettres)/sizeof(vecteur_lettres[0]);

  // DECODIFICATION
  char *lettre_bin = calloc(strlen(phrase_bin), sizeof(char));
  char str_l_bin[15];
  char phrase_decod;
  int counter = 0;
  
  for(int i=0; i<strlen(phrase_bin); i++) { // percorrendo a string
    caract = phrase_bin[i];
    
		lettre_bin[counter] = caract;
		counter++;
		
    for(int j=0; j<longueur_vec_l;j++) { //percorre o vetor com os structs das letras

			if (strcmp(lettre_bin, vecteur_lettres[j].bin_str) == 0) {
					printf("%c", vecteur_lettres[j].letre);
					memset(lettre_bin, '\0', strlen(phrase_bin)*sizeof(char));
					counter = 0;
					break;
			}
    }

		
  }
  
}*/