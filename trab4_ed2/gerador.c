/**
 * PROGRAMA COM AS FUNÇÕES PARA GERAR UMA AMOSTRA DE NÚMEROS ALEATÓRIA, CRESCENTE E DECRESCENTE
 * @author Igor Ventorim
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define REPETE 5

/**
 * createRandom Cria uma amostra de números aleatórios
 * @param qtdNum Tamanho da amostra desejada
 */
void createRandom(int qtdNum)
{
		FILE *arq = fopen("amostra.txt","w");

		int i;
		srand( (unsigned)time(NULL) );

		int num = qtdNum;

		for(i = 0; i < qtdNum; i++)
			fprintf(arq,"%d ",rand()%(num)+1);
		
		fclose(arq);
}

/**
 * createC Cria uma amostra de números crescente
 * @param Tamanho da amostra desejada
 */
void createC(int qtdNum)
{
	FILE *arq = fopen("amostra.txt","w");
	int i, cont = 0;
	for(i = 0; i < qtdNum; i++,cont++)
	{
		if(cont > REPETE)
		{
			cont = 0;
			fprintf(arq,"%d ",(i*100)-1);	
		}else
			fprintf(arq,"%d ",(i*100));

	}
	fclose(arq);
}

/**
 * createD Cria uma amostra de números decrescente
 * @param qtdNum Tamanho da amostra desejada
 */
void createD(int qtdNum)
{
	FILE *arq = fopen("amostra.txt","w");
	int i, cont = 0;
	for(i = qtdNum; i > 0; i--,cont++)
	{
		if(cont > REPETE)
		{
			cont = 0;
			fprintf(arq,"%d ",(i*100)+1);	
		}else
			fprintf(arq,"%d ",(i*100));

	}
	
	fclose(arq);

}

int main(int argc, char** argv)
{
	
	if(argc == 3)
	{
		int qtdNum = atoi(argv[2]);
		if(!strcmp(argv[1],"-a"))
		{
			createRandom(qtdNum);	
		}else
		if(!strcmp(argv[1],"-c"))
		{
			createC(qtdNum);
		}else
		if(!strcmp(argv[1],"-d"))
		{
			createD(qtdNum);
		}else
			fprintf(stdout, "Usage: %s -[Tipo de amostra que deseja (a,c,d)] [Quantidade de jobs que deseja gerar]\n", argv[0]);
		
	}
	else
	{
		fprintf(stdout, "Usage: %s -[Tipo de amostra que deseja (a,c,d)] [Quantidade de jobs que deseja gerar]\n", argv[0]);
	}

	return 0;
}