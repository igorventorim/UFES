/**
 * TAD com todas funções de entrada e saída
 * @Author Igor Ventorim
 */

#include <stdlib.h>
#include <stdio.h>
#include "io.h"

/**
 * readAmostra Efetuar a leitura das amostras
 * @param amostra Vetor onde será armazenado a amostra
 * @param size    Tamanho da amostra
 */
void readAmostra(int *amostra,const int size)
{
	int i;

	for(i = 0; i < size; i++)
		scanf("%d",&amostra[i]);
	
}

/**
 * [print description]
 * @param vet  [description]
 * @param size [description]
 */
void print(int *vet, const int size)
{
	int i;

	for(i = 0; i < size; i++)
		printf("%d ",vet[i]);

	printf("\n");
	
}