#include <stdlib.h>
#include <stdio.h>
#include "pvc.h"

/**
 * [createLPoints description]
 * @param  N [description]
 * @param  M [description]
 * @return   [description]
 */
Point* criaLPoints(const int N, const int M)
{
	Point *new = calloc((size_t)(M*N),sizeof(Point));
	return new;
}

/**
 * [criaMatrizColuna description]
 * @param  N [description]
 * @param  M [description]
 * @return   [description]
 */
MatColuna* criaMatrizColuna(const int N, const int M)
{
	
	MatColuna *newMat = malloc(sizeof(MatColuna));
	int ordem = N*M; 
	/* ALOCANDO VETORES DE ELEMENTOS NÃO NULOS */
	newMat->vetAi = calloc((size_t)ordem,sizeof(double));
	newMat->vetBi = calloc((size_t)ordem,sizeof(double));
	newMat->vetCi = calloc((size_t)ordem,sizeof(double));
	newMat->vetDi = calloc((size_t)ordem,sizeof(double));
	newMat->vetEi = calloc((size_t)ordem,sizeof(double));
	newMat->tamX = N;
	newMat->tamY = M;

	return newMat;
}

/**
 * [freeLPoints description]
 * @param lPoints [description]
 */
void freeLPoints(Point *lPoints)
{
	free(lPoints);
}

/**
 * [discretiza description]
 * @param input   [description]
 * @param lPoints [description]
 */
void discretiza(Data *input, Point *lPoints)
{
	int i,j;
	double hx,hy;
	int pos = 0;

	hx = (input->fimX - input->iniX)/((double)(input->tamX - 1));
	hy = (input->fimY - input->iniY)/((double)(input->tamY - 1));

	for( j = 1; j <= input->tamY; j++)
		for( i = 1; i <= input->tamX; i++)
		{
			lPoints[pos].x = input->iniX + (i-1)*hx;
			lPoints[pos].y = input->iniY + (j-1)*hy;
			pos++;
		}

}

/**
 * [criarVetorIndependente description]
 * @param  input   [description]
 * @param  lPoints [description]
 * @return         [description]
 */
double* criaVetorIndependente(Data *input, Point *lPoints)
{
	double *vetIndependente;
	int i, tamVetIndependente = input->tamX * input->tamY;
	double x,y;


	vetIndependente = calloc((size_t)tamVetIndependente,sizeof(double));

	for( i = 0; i < tamVetIndependente; i++)
	{
		x = lPoints[i].x;
		y = lPoints[i].y;
		vetIndependente[i] = F(x,y);
	}
	return vetIndependente;
}

/**
 * [buildingMatrix description]
 * @param input   [description]
 * @param newMat  [description]
 * @param lPoints [description]
 */
void buildingMatrix(Data *input, MatColuna *newMat, Point *lPoints)
{
	double hx,hy,aI,bI,cI,dI,eI,x,y;
	int ordem,i,j;

	/* CALCULANDO ORDEM DA MATRIZ */
	ordem = input->tamX * input->tamY;

	/* CALCULANDO VALORES DE HX E HY*/
	hx = (input->fimX - input->iniX)/((double)(input->tamX - 1));
	hy = (input->fimY - input->iniY)/((double)(input->tamY - 1));
	
	/* CONSTRUINDO MATRIZ PENTADIAGONAL E MATRIZ ARMAZENADA POR COLUNAS */
	for(i = 0; i < ordem; i++)
	{			
		x = lPoints[i].x;
		y = lPoints[i].y;
		aI = GAMA(x,y)+ 2*K*((1/(hx*hx)) + (1/(hy*hy)));
		bI = ((-1*K)/(hx*hx))+(BETAx(x,y)/(2*hx));
		cI = ((-1*K)/(hx*hx))-(BETAx(x,y)/(2*hx));
		dI = ((-1*K)/(hy*hy))+(BETAy(x,y)/(2*hy));
		eI = ((-1*K)/(hy*hy))-(BETAy(x,y)/(2*hy));

		for(j = 0; j < ordem; j++)
		{
			if(i == j)
			{	
				newMat->vetAi[i] = aI;
			}else if((i+1) == j)
			{
				newMat->vetBi[i] = bI;
			}else if((i-1) == j)
			{
				newMat->vetCi[i] = cI;
			}else if((i - input->tamX) == j)
			{
				newMat->vetEi[i] = eI;
			}else if((i + input->tamX) == j)
			// {
				newMat->vetDi[i] = dI;
		}
	}
}


/**
 * [freeMatColuna description]
 * @param newMat [description]
 * @param input  [description]
 */
void freeMatColuna(MatColuna *newMat)
{	
	free(newMat->vetAi);
	free(newMat->vetBi);
	free(newMat->vetCi);
	free(newMat->vetDi);
	free(newMat->vetEi);
	free(newMat);
}

/**
 * [generationNewIndex description]
 * @param  x    [description]
 * @param  y    [description]
 * @param  tamX [description]
 * @return      [description]
 */
int generationNewIndex(int x, int y, int tamX)
{
	return x + y*tamX;
}

/**
 * [setContorno description]
 * @param newMat [description]
 * @param pos    [description]
 */
void setContornoComum(double* aI, double* bI, double* cI, double* dI, double* eI)
{
	*aI = 1;
 	*bI = 0;
 	*cI = 0;
 	*dI = 0;
 	*eI = 0;
}


/**
 * [inserirContorno description]
 * @param matrix          [description]
 * @param newMat          [description]
 * @param vetIndependente [description]
 */
void inserirContorno(MatColuna *newMat, double *vetIndependente, Data *input, Point *lPoints)
{
	 int i,index,x,y;
	 double hx;
	 hx = (input->fimX - input->iniX)/((double)(input->tamX - 1));
	
	for( i = 0; i < input->tamY; i++)
	 {
	 	index = generationNewIndex(0,i,input->tamX);
	 	x = lPoints[index].x;
	 	y = lPoints[index].y;
	 	vetIndependente[index] =  CONTORNOoeste(x,y);
	 	if(!CONTORNOoesteDERIVADA)
	 		setContornoComum(&newMat->vetAi[index],&newMat->vetBi[index],&newMat->vetCi[index],&newMat->vetDi[index],&newMat->vetEi[index]);
	 	else{}

	 }

	 for( i = 0; i < input->tamY; i++)
	 {
	 	index = generationNewIndex(input->tamX-1,i,input->tamX);
	 	x = lPoints[index].x;
	 	y = lPoints[index].y;
	 	vetIndependente[index] = CONTORNOleste(x,y);
	 	if(!CONTORNOlesteDERIVADA)
	 		setContornoComum(&newMat->vetAi[index],&newMat->vetBi[index],&newMat->vetCi[index],&newMat->vetDi[index],&newMat->vetEi[index]);
	 	else{
	 		newMat->vetAi[index] = newMat->vetAi[index] + newMat->vetBi[index] * (1 - hx);
	 		vetIndependente[index] = vetIndependente[index] - 70 * hx * newMat->vetBi[index];
	 		newMat->vetBi[index] = 0;   
	 	}

	 }

	 for( i = 0; i < input->tamX; i++)
	 {
	 	index = generationNewIndex(i,0,input->tamX);
	 	x = lPoints[index].x;
	 	y = lPoints[index].y;
	 	vetIndependente[index] = CONTORNOsul(x,y);
	 	if(!CONTORNOsulDERIVADA)
	 		setContornoComum(&newMat->vetAi[index],&newMat->vetBi[index],&newMat->vetCi[index],&newMat->vetDi[index],&newMat->vetEi[index]);
	 	else{}

	 }

	 for( i = 0; i < input->tamX;i++)
	 {
	 	index = generationNewIndex(i,input->tamY-1,input->tamX);
	 	x = lPoints[index].x;
	 	y = lPoints[index].y;
	 	vetIndependente[index] = CONTORNOnorte(x,y);
	 	if(!CONTORNOnorteDERIVADA)
	 		setContornoComum(&newMat->vetAi[index],&newMat->vetBi[index],&newMat->vetCi[index],&newMat->vetDi[index],&newMat->vetEi[index]);
	 	else{}
	 }

	 

}


/**
 * [geraMatriz description]
 * @param vetorSolucao [description]
 * @param input        [description]
 */
void printMatriz(double *vetorSolucao,Data input)
{
	int i,j;
	/* IMPRIMINDO NO FORMATO MATRIZ */
	for(i = (input.tamX*input.tamY)-1; i >= 0; i -= input.tamX+1)
	{
		 // printf("%d - %d = %d\n\n",i,input.tamX-1,(i - input.tamX)+1);
		for(j = 0,i = i - input.tamX+1; j < input.tamX; i++, j++)
			// printf(" %d ",i);
			printf("   %.2f   ",vetorSolucao[i]);
		// i -= input.tamX; 
		printf("\n");
	}
}
