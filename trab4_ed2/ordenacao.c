/**
 * TAD com todas funções de ordenacao
 * @Author Igor Ventorim
 */

#include <stdlib.h>
#include <stdio.h>
#include "ordenacao.h"
#include <time.h>
#include "fila.h"
#include <string.h>
#define SWAP(x,y){x = x+y; y = x - y; x = x - y;}

/**
 * [bubbleSort description]
 * @param  vet [description]
 * @param  n   [description]
 */
void bubbleSort(int *vet,const int N)
{
	int i,j,aux,flag = 1;

	for(i = N-1; (i > 0) && (flag == 1); i--)
	{
		flag = 0;
		for(j = 0; j < i;j++)
		{
			if(vet[j] > vet[j+1])
			{
				aux = vet[j];
				vet[j] = vet[j+1];
				vet[j+1] = aux;
				flag = 1;
			}
		}
	}
}

/**
 * [selectionSort description]
 * @param vet [description]
 * @param N   [description]
 */
void selectionSort(int *vet, const int N)
{
	int i,j,aux,min;

	for(i = 0; i < N-1;i++)
	{
		min = i;
		for(j = i+1; j < N; j++)
		{
			if(vet[j] < vet[min])
				min = j;
		}

		aux = vet[i];
		vet[i] = vet[min];
		vet[min] = aux;
	}
}

/**
 * [insertionSort description]
 * @param vet [description]
 * @param N   [description]
 */
void insertionSort(int *vet, const int N)
{
	int i,j,aux;

	for(i = 1; i < N; i++)
	{
		aux = vet[i];
		j = i - 1;
		while(j >= 0 && vet[j] > aux)
		{
			vet[j+1] = vet[j];
			j = j-1;
		}
		vet[j+1] = aux;
	}
}

/**
 * [shakeSort description]
 * @param vet [description]
 * @param N   [description]
 */
void shakeSort(int *vet,const int N)
{
	int inicio,fim,swap,aux,i;

	inicio = 0;
	fim = N -1;
	swap = 0;

	while(swap == 0 && (inicio < fim))
	{
		swap = 1;

		for(i = inicio; i < fim; i++)
		{
			if(vet[i] > vet[i+1])
			{
				aux = vet[i];
				vet[i] = vet[i+1];
				vet[i+1] = aux;
				swap = 0;
			}
		}

		fim--;

		for(i = fim; i > inicio; i--)
		{
			if(vet[i] < vet[i-1])
			{
				aux = vet[i];
				vet[i] = vet[i-1];
				vet[i-1] = aux;
				swap=0;
			}
		}

		inicio++;
	}

}

/**
 * [shellsort description]
 * @param vet [description]
 * @param N   [description]
 */
void shellSort(int *vet, const int N)
{
	int i,j, valor;
	int h = 1;

	while(h < N)
	{
		h = 3 * h + 1;
	}

	while( h > 1)
	{
		h /= 3;
		for( i = h; i < N; i++)
		{
			valor = vet[i];
			j = i - h;
			while(j >= 0 && (valor < vet[j]))
			{
				vet[j + h] = vet[j];
				j -= h;
			}

			vet[j + h] = valor;
		}
	}
}

/**
 * [heapSort description]
 * @param vet [description]
 * @param n   [description]
 */
void heapSort(int *vet, int n)
{
	int i = n/2, pai, filho, t;
	while(1 == 1)
	{
		if(i > 0)
		{
			i--;
			t = vet[i];
		}else
		{
			n--;
			if(n == 0)	return;
			t = vet[n];
			vet[n] = vet[0];
		}

		pai = i;
		filho = i *2 +1;
		while(filho < n)
		{
			if((filho +1 < n) && (vet[filho +1] > vet[filho]))
				filho++;
			if(vet[filho] > t)
			{
				vet[pai] = vet[filho];
				pai = filho;
				filho = pai * 2 + 1;
			}else
				break;
		}
		vet[pai] = t;
	}
}

/**
 * [quickSort description]
 * @param vet [description]
 * @param ini [description]
 * @param fim [description]
 */
void quickSort1(int *vet, int ini, int fim)
{
	int i, j, pivo, aux;

	i = ini;
	j = fim;
	pivo = vet[ini];

	while(i <= j)
	{
		while(vet[i] < pivo /*&& i < fim*/)
			i++;
		while(vet[j]>pivo /*&& j > ini*/)
			j--;
		if(i <= j)
		{
			aux = vet[i];
			vet[i] = vet[j];
			vet[j] = aux;
			i++;
			j--;
		}
	}
	if( j > ini)
		quickSort1(vet,ini,j);
	if(i < fim)
		quickSort1(vet,i,fim);
}


/**
 * [quickSortCentral description]
 * @param vet [description]
 * @param ini [description]
 * @param fim [description]
 */
void quickSortCentral(int *vet, int ini, int fim)
{
	int i, j, pivo, aux;

	i = ini;
	j = fim;
	pivo = vet[(ini+fim)/2];

	while(i <= j)
	{
		while(vet[i] < pivo /*&& i < fim*/)
			i++;
		while(vet[j]>pivo /*&& j > ini*/)
			j--;
		if(i <= j)
		{
			aux = vet[i];
			vet[i] = vet[j];
			vet[j] = aux;
			i++;
			j--;
		}
	}
	if( j > ini)
		quickSortCentral(vet,ini,j);
	if(i < fim)
		quickSortCentral(vet,i,fim);
}

/**
 * [quickSortCentral description]
 * @param vet [description]
 * @param ini [description]
 * @param fim [description]
 */
void quickSortRandom(int *vet, int ini, int fim)
{
	int i, j,pivo, aux;

	i = ini;
	j = fim;
	int p = ini + (rand()%(fim-ini));
	pivo = vet[p];
	
	while(i <= j)
	{
		while(vet[i] < pivo /*&& i < fim)//*/)
			i++;
		while(vet[j]>pivo /*&& j > ini)//*/)
			j--;
		if(i <= j)
		{
			aux = vet[i];
			vet[i] = vet[j];
			vet[j] = aux;
			i++;
			j--;
		}
	}
	if( j > ini)
	{
		quickSortRandom(vet,ini,j);
	}
	if(i < fim)
	{
		quickSortRandom(vet,i,fim);
	}
}

/**
 * [quickSortMediana3 description]
 * @param vet [description]
 * @param ini [description]
 * @param fim [description]
 */
void quickSortMediana3(int *vet, int ini, int fim)
{
	int i, j, pivo, aux,mid;

	i = ini;
	j = fim;	
	//pivo = vet[(ini+((ini+fim)/2)+fim)/3];

	mid = (ini + fim) / 2;

    if(vet[fim] < vet[ini])
        SWAP(vet[fim], vet[ini]);

    if(vet[mid] < vet[ini])
        SWAP(vet[mid], vet[ini]);

    if(vet[fim] < vet[mid])
        SWAP(vet[fim], vet[mid]);

    pivo = vet[mid]; 

	while(i <= j)
	{
		while(vet[i] < pivo /*&& i < fim*/)
			i++;
		while(vet[j]>pivo /*&& j > ini*/)
			j--;
		if(i <= j)
		{
			aux = vet[i];
			vet[i] = vet[j];
			vet[j] = aux;
			i++;
			j--;
		}
	}
	if( j > ini)
		quickSortMediana3(vet,ini,j);
	if(i < fim)
		quickSortMediana3(vet,i,fim);
}

/**
 * [mergeSort description]
 * @param vet [description]
 * @param ini [description]
 * @param fim [description]
 */
void mergeSort(int *vet, int ini, int fim)
{
	int i,j,k,media,*vetAux;
	if(ini == fim) return;

	media = ( ini + fim )/ 2;
	mergeSort(vet, ini, media);
	mergeSort(vet,media+1,fim);

	i = ini;
	j = media+1;
	k = 0;

	vetAux = calloc((size_t)(fim - ini + 1),sizeof(int));

	while(i < media +1 ||  j < fim + 1)
	{
		if(i == media + 1)
		{
			vetAux[k] = vet[j];
			j++;
			k++;
		}else
		{
			if(j == fim +1)
			{
				vetAux[k] = vet[i];
				i++;
				k++;
			}else
			{
				if(vet[i] < vet[j])
				{
					vetAux[k] = vet[i];
					i++;
					k++;
				}else
				{
					vetAux[k] = vet[j];
					j++;
					k++;
				}
			}
		}
	}

	for(i = ini; i <= fim; i++)
	{
		vet[i] = vetAux[i - ini];
	}
	free(vetAux);
}

/**
 * [rankSort description]
 * @param vet [description]
 * @param N   [description]
 */
void rankSort(int* vet, const int N)
{
	int i, max = 1000000, *aux,pos = 0;

	//for(i = 0; i < N; i++)
	//{
	//	if(vet[i] > max)
	//		max = vet[i];
	//}

	aux = calloc((size_t)(max + 1),sizeof(int));
	
	for(i = 0; i < N; i++)
	{
		aux[vet[i]]++; 
	}

	for( i = 0; i <= max; i++)
	{
			while(aux[i] > 0)
			{	
				vet[pos] = i;
				aux[i]--;
				pos++;
			}
	}
	free(aux);
}

/**
 * [radixSort description]
 * @param vet [description]
 * @param N   [description]
 */
void radixSort(int *vet, const int N)
{
	int i,pos = 0;
	int m = 1, maior = 1000000;
	Fila **f = calloc(10,sizeof(Fila*));
	
	for( i = 0; i < 10; i++)
			f[i] = createFila();

	//for(i = 0; i < N; i++)
	//{
	//	if(vet[i] > maior)
	//		maior = vet[i];
	//}
	
	while(m <= maior)
	{
		pos = 0;
		for(i = 0; i < N; i++)
			insert(f[(vet[i]/m)%10],vet[i]); 
	
		for(i = 0; i < 10; i++)
		{
			while(f[i]->primeiro != NULL)
			{
				vet[pos] = removeFila(f[i]);
				pos++;
			}
		}
		m *= 10;
	}	

	for( i = 0; i < 10; i++)	
			freeFila(f[i]);
	
	free(f);	
}



/**
 * [radixSort description]
 * @param vet [description]
 * @param N   [description]
 */
void radixSortBin(int *vet, const int N)
{
	
	int i,pos = 0;
	int m = 1, maior = 1000000;
	Fila **f = calloc(10,sizeof(Fila*));
	//Fila *aux = malloc(sizeof(Fila));
	for( i = 0; i < 2; i++)
			f[i] = createFila();

	//for(i = 0; i < N; i++)
	//{
	//	if(vet[i] > maior)
	//		maior = vet[i];
	//}
	//maior *= 2;
	while(m <= maior)
	{
		pos = 0;
		for(i = 0; i < N; i++)
		{
			insert(f[verificaBound(vet[i],m)],vet[i]); 
		}
		for(i = 0; i < 2; i++)
		{
			while(f[i]->primeiro != NULL)
			{
				vet[pos] = removeFila(f[i]);
				pos++;
			}
		}
		m = m << 1;
	}	

	for( i = 0; i < 2; i++)	
			freeFila(f[i]);
	
	free(f);
	
}

/**
 * [verificaBound description]
 * @param  a [description]
 * @param  b [description]
 * @return   [description]
 */
int verificaBound(int a, int b)
{
	
	if(a & b)
		return 1;
	else
		return 0;
}