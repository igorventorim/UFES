/**
 * Cabeçalho com as assinaturas das funções de ordenacao
 * @Author Igor Ventorim
 */

#ifndef ORDENA_H
#define ORDENA_H

/** [bubbleSort description] */
void bubbleSort(int *vet,const int N);

/** [selectionSort description] */
void selectionSort(int *vet, const int N);

/** [insertionSort description] */
void insertionSort(int *vet, const int N);

/** [shakeSort description] */
void shakeSort(int *vet,const int N);

/** [shellsort description] */
void shellSort(int *vet, const int N);

/** [constroi_heap  description] */
void constroi_heap (int *vet,int n);
/** [heapSort description] */
void heapSort(int *vet, int n);

/** [quickSort1 description] */
void quickSort1(int *vet, int ini, int fim);

/** [quickSortCentral description] */
void quickSortCentral(int *vet, int ini, int fim);

/** [quickSortRandom description] */
void quickSortRandom(int *vet, int ini, int fim);

/** [quickSortMediana3 description] */
void quickSortMediana3(int *vet, int ini, int fim);

/** [mergeSort description] */
void mergeSort(int *vet, int ini, int fim);

/** [rankSort description] */
void rankSort(int* vet, const int N);

/** [radixSort description] */
void radixSort(int *vet, const int N);

/** [radixSortBin description] */
void radixSortBin(int *vet, const int N);
int verificaBound(int a, int b);

#endif
