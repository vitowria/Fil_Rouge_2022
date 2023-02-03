#include <stdio.h>
#include <stdlib.h>

#include "test_utils.h"

// Ajouter ici les prototypes des fonctions à tester
//T_data fusionSort(T_data d, int n); 
T_data heapSort(T_data d, int n); 
//void fusionsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

// mode, label, x, checkOrder 
T_mode m[] = {
	{MODE_TAB_ORDONNE, "ordonne", 0, 1}, 
	{MODE_TAB_ALEATOIRE, "aleatoire", 0, 1}, 
	{MODE_TAB_INVERSE, "inverse", 0, 1}, 
	{MODE_EVAL_X, "x=2.0", 2.0, 0}, 
	{MODE_TAB_ORDONNE, "ordonne (x=59)", 59, 0}, 
	{MODE_TAB_ORDONNE, "hanoi", 1, 0}
};

int main(int argc, char *argv[])
{
    T_elt tab [MAX_ELT];
	//T_data d; 
  //int base[MAX_ELT];

	outputPath = "output"; // indiquer le chemin du répertoire où créer les fichiers
	// NB: s'il est relatif, il sera relatif au répertoire depuis lequel l'exercice est exécuté
	
    // Initialisation du générateur de nombres pseudo-aléatoires 
    srand((unsigned int)time(NULL));

	Test_Fn("HEAPSORT", heapSort, tab, MAX_ELT/10, m[MODE_TAB_ORDONNE] );
	Test_Fn("HEAPSORT", heapSort, tab, MAX_ELT/10, m[MODE_TAB_ALEATOIRE] );
	Test_Fn("HEAPSORT", heapSort, tab, MAX_ELT/10, m[MODE_TAB_ALEATOIRE] );

	Test_FnV2("HEAPSORT", heapSort, tab, 512, m[MODE_TAB_ORDONNE] );
	Test_FnV2("HEAPSORT", heapSort, tab, 512, m[MODE_TAB_ALEATOIRE] );
	Test_FnV2("HEAPSORT", heapSort, tab, 512, m[MODE_TAB_INVERSE] );


	

 /*
    T_data d;
    T_elt v[13]={5,7,2,12,11,1,13,22,4,9,17,12,10};
    d=genData(0, v);
  
    
    printArray(v, 13);
    T_data out0 = heapSort_Aux(d, 13);
    printArray(out0.pElt, 13);
    
    T_data out = heapSort(d, 13);
    printArray(out.pElt, 13);
*/  
}
