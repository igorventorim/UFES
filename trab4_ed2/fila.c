#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

/**
 * [aloca description]
 * @return [description]
 */
Fila *aloca()
{
	Fila *novo= malloc(sizeof(Fila));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}else{
		//printf("Novo elemento: "); scanf("%d", &novo->num);
		return novo;
	}
}
/**
 * [createFila description]
 * @param f [description]
 */
Fila* createFila()
{
	Fila *new = aloca();
	new->primeiro = NULL;
	new->ultimo = NULL;
	return new;
}

/**
 * [insert description]
 * @param f [description]
 * @param n [description]
 */
void insert(Fila *f, int n)
{
	Celula *new = malloc(sizeof(Celula));

	if(f->ultimo == NULL)
	{
		f->primeiro = f->ultimo = new;
	}else
	{
		f->ultimo->prox = new;
		f->ultimo = f->ultimo->prox;
	}

	f->ultimo->number = n;
	f->ultimo->prox = NULL;

}

/**
 * [removeFila description]
 * @param  f [description]
 * @return   [description]
 */
int removeFila(Fila *f)
{
	int element;
	Celula *c;

		c = f->primeiro;
		element = c->number;
		f->primeiro = c->prox;
		if(f->primeiro == NULL)
			f->ultimo = NULL;
		free(c);
		return element;
	

}


/**
 * [freeFila - Liberando memória da Fila]
 * @param l [Fila ao qual se deseja liberar da memória]
 */
void freeFila(Fila *f)
{
	Celula* aux = f->primeiro;
	while(aux != NULL)
	{
		Celula* t = aux->prox;
		free(aux);
		aux = t;
	}
	free(f);
}