/**
 * Algoritmos de Ordenação
 * @last_update 12-11-15
 * @Author Igor Ventorim
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "io.h"
#include "ordenacao.h"
#include "fila.h"

int main(int argc, char **argv)
{
	int n, *amostra;

	/* Verifica o número de parâmetros */
    if(argc != 3)
    {
        printf("Sintaxe:\n./trab4 [algoritmo] [quantidade de numeros]\n");
        exit(1);
    }

     n = atoi(argv[2]);

     amostra = calloc((size_t)n,sizeof(int));
     readAmostra(amostra,n);

     if(!strcmp(argv[1],"bubble"))
     {
          bubbleSort(amostra,n);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"shake"))
     {
          shakeSort(amostra,n);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"insertion"))
     {
          insertionSort(amostra, n);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"shell"))
     {
          shellSort(amostra, n);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"selection"))
     {
          selectionSort(amostra, n);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"rank"))
     {
          rankSort(amostra, n);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"quickprimeiro"))
     {
          quickSort1(amostra, 0, n-1);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"quickcentral"))
     {
          quickSortCentral(amostra, 0, n-1);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"quickrandom"))
     {
          srand( (unsigned)time(NULL));
          quickSortRandom(amostra, 0, n-1);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"quickmediana3"))
     {
          quickSortMediana3(amostra, 0, n-1);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"merge"))
     {
          mergeSort(amostra, 0, n-1);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"heap"))
     {
          heapSort(amostra, n);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"radix"))
     {
          radixSort(amostra, n);
          print(amostra,n);
     }else
     if(!strcmp(argv[1],"radixbin"))
     {
          radixSortBin(amostra, n);
          print(amostra,n);
     }else
     	printf("Algoritmo \"%s\" incorreto. Insira o nome do algoritmo correto e tente novamente. \n", argv[2]);



     free(amostra);
	return 0;
}