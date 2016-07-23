
#ifndef PVC_H
#define PVC_H
#include <math.h>
#define e 2.718281
#define K 1	// DEFINA O VALOR CORRESPONDENTE DE K
#define F(x,y)  70 //-((2.5) * (pow(e,pow(x,4.5))) *  (81 * (pow(x,9)) - 81 * (pow(x,8)) + 135 * (pow(x,4.5)) - 99 * (pow(x,3.5)) + 8) * (y-1) * y + (20 * (pow(e,pow(x,4.5))) * (x -1) * x) ) + 5 * (pow(e,pow(x,4.5))) * ( x * ( 9 *( x-1) * (pow(x,3.5))+4)-2)*(y-1)*y + 20*y*(10*(pow(e,pow(x,4.5)))*(x-1)*x*(2*y-1))+ 10 * x*y*(1-x)*(1-y)*(pow(e,pow(x,4.5))) // MACRO DA FUNÇÃO Fi -> TROQUE O VALOR PELA FUNÇÃO MATEMÁTICA CORRESPONDENTE DE F(x,y)
#define BETAx(x,y) 0//1 // MACRO DA FUNÇÃO BETA em x -> TROQUE O VALOR 0 PELA FUNÇÃO MATEMÁTICA CORRESPONDENTE DE BETA(x,y)
#define BETAy(x,y) 0//20*y // MACRO DA FUNÇÃO BETA em y -> TROQUE O VALOR 0 PELA FUNÇÃO MATEMÁTICA CORRESPONDENTE DE BETA(x,y)
#define GAMA(x,y) 1 // MACRO DA FUNÇÃO GAMA -> TROQUE O VALOR 0 PELA FUNÇÃO MATEMÁTICA CORRESPONDENTE DE GAMA(x,y)
/* DEFININDO VALOR OU EXPRESSÃO PARA CALCULAR O VALOR DE CADA CONTORNO */
#define CONTORNOsul(x,y) 70
#define CONTORNOoeste(x,y) 200
#define CONTORNOnorte(x,y) 70
#define CONTORNOleste(x,y) 0
/* DEFININDO QUAIS CONTORNOS SÃO COMPOSTOS DE DERIVADAS: 1 - TRUE / 0 - FALSE */
#define CONTORNOsulDERIVADA 0
#define CONTORNOoesteDERIVADA 0
#define CONTORNOnorteDERIVADA 0
#define CONTORNOlesteDERIVADA 1

typedef struct data Data;
typedef struct point Point;
typedef struct matColuna MatColuna;

struct data
{
	double iniX;
	double iniY;
	double fimX;
	double fimY;
	int tamX,tamY;
};

struct point
{
	double x,y;
};

struct matColuna
{
	double *vetAi;
	double *vetBi;
	double *vetCi;
	double *vetDi;
	double *vetEi;
	int tamX, tamY;
};

/**
 * [criarLPoints description]
 * @param  N [description]
 * @param  M [description]
 * @return   [description]
 */
Point* criaLPoints(const int N, const int M);

/**
 * [criaMatrizColuna description]
 * @param  N [description]
 * @param  M [description]
 * @return   [description]
 */
MatColuna* criaMatrizColuna(const int N, const int M);

/**
 * [freeLPoints description]
 * @param lPoints [description]
 */
void freeLPoints(Point *lPoints);

/**
 * [discretiza description]
 * @param input   [description]
 * @param lPoints [description]
 */
void discretiza(Data *input, Point *lPoints);

/**
 * [criarVetorIndependente description]
 * @param  input   [description]
 * @param  lPoints [description]
 * @return         [description]
 */
double* criaVetorIndependente(Data *input, Point *lPoints);

/**
 * [buildingMatrix description]
 * @param input   [description]
 * @param newMat  [description]
 * @param lPoints [description]
 */
void buildingMatrix(Data *input, MatColuna *newMat, Point *lPoints);

/**
 * [freeMatColuna description]
 * @param newMat [description]
 * @param input  [description]
 */
void freeMatColuna(MatColuna *newMat);

/**
 * [generationNewIndex description]
 * @param  x    [description]
 * @param  y    [description]
 * @param  tamX [description]
 * @return      [description]
 */
int generationNewIndex(int x, int y, int tamX);

/**
 * [setContornoComum description]
 * @param aI [description]
 * @param bI [description]
 * @param cI [description]
 * @param dI [description]
 * @param eI [description]
 */
void setContornoComum(double* aI, double* bI, double* cI, double* dI, double* eI);

/**
 * [inserirContorno description]
 * @param newMat          [description]
 * @param vetIndependente [description]
 * @param input           [description]
 * @param lPoints         [description]
 */
void inserirContorno(MatColuna *newMat, double *vetIndependente, Data *input, Point *lPoints);

/**
 * [geraMatriz description]
 * @param vetorSolucao [description]
 * @param input        [description]
 */
void printMatriz(double *vetorSolucao,Data input);

#endif


//-((5/2) * (pow(e,pow(x,4.5))) *  (81 * (pow(x,9)) - 81 * (pow(x,8)) + 135 * (pow(x,4.5)) - 99 * (pow(x,3.5)) + 8) * (y-1) * y + (20 * (pow(e,pow(x,4.5))) * (x -1) * x) ) + 5 * (pow(e,pow(x,4.5))) * ( x * ( 9 *( x-1) * (pow(x,3.5))+4)-2)*(y-1)*y + 20*y*(10*(pow(e,pow(x,4.5)))*(x-1)*x*(2*y-1))+ 10 * x*y*(1-x)*(1-y)*(pow(e,pow(x,4.5)))