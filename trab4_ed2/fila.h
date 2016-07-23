#ifndef FILA_H
#define FILA_H

typedef struct celula Celula;
typedef struct fila Fila;

struct fila
{
	struct celula *primeiro;
	struct celula *ultimo;
};


struct celula
{
	int number;
	struct celula *prox;
};

/** [aloca description] */
Fila *aloca();

/** [createFila description] */
Fila *createFila();

/** [insert description] */
void insert(Fila *f, int n);

/** [removeFila description] */
int removeFila(Fila *f);

/** [freeFila description] */
void freeFila(Fila *f);

#endif 