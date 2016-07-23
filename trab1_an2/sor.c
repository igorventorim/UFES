#include <stdio.h>
#include <stdlib.h>
#include "pvc.h"
#include <math.h>

/**
 * [sor description]
 * @param  newMat          [description]
 * @param  vetIndependente [description]
 * @param  omega           [description]
 * @param  tolerancia      [description]
 * @param  iterMax         [description]
 * @return                 [description]
 */
double *sor(MatColuna *newMat, double *vetIndependente, double omega, double toler, int iterMax)
{
	int i,qtdElementos,iter = 0;
	double r,soma,*vetSolucao,*vetAux,normaNum,normaDen,normaRel,aux;

	qtdElementos = newMat->tamX * newMat->tamY;
	vetSolucao = calloc((size_t)qtdElementos,sizeof(double));
	vetAux = calloc((size_t)qtdElementos,sizeof(double));

	for( i = 0; i < qtdElementos; i++)
	{
		r = 1/newMat->vetAi[i];
		newMat->vetBi[i] = newMat->vetBi[i] * r;
		newMat->vetCi[i] = newMat->vetCi[i] * r;
		newMat->vetDi[i] = newMat->vetDi[i] * r;
		newMat->vetEi[i] = newMat->vetEi[i] * r;
		vetIndependente[i] = vetIndependente[i] * r;
		vetSolucao[i] = vetIndependente[i];
	}

	do
	{
		iter++;
		for( i = 0; i < qtdElementos; i++)
		{
			soma = 0;
			if(newMat->vetBi[i])
				soma += newMat->vetBi[i]*vetSolucao[i+1];
			if(newMat->vetCi[i])
				soma += newMat->vetCi[i]*vetSolucao[i-1];
			if(newMat->vetEi[i])
				soma += newMat->vetEi[i]*vetSolucao[i-newMat->tamX];
			if(newMat->vetDi[i])
				soma += newMat->vetDi[i]*vetSolucao[i+newMat->tamX];
			vetAux[i] = vetSolucao[i];
			vetSolucao[i] = omega * (vetIndependente[i] - soma) + (1 - omega) * vetSolucao[i];
		}
		normaNum = 0;
		normaDen = 0;
		for( i = 0; i < qtdElementos; i++)
		{
			aux = fabs(vetSolucao[i] - vetAux[i]);
			if( aux > normaNum)
				normaNum = aux;
			if(fabs(vetSolucao[i]) > normaDen)
				normaDen = fabs(vetSolucao[i]);
		}
		normaRel = normaNum/normaDen;
	}while(normaRel > toler && iter < iterMax);

	free(vetAux);
	if(normaRel < toler) printf("CONVERGIU! :)\n"); else printf("NAO CONVERGIU! :(\n");
	printf("Numero de iteracoes: %d\n",iter);
	printf("Erro: %g\n",normaRel);
	return vetSolucao;
}

/**
 * [sorLivre description]
 * @param  input   [description]
 * @param  lpoints [description]
 * @param  omega   [description]
 * @param  toler   [description]
 * @param  iterMax [description]
 * @return         [description]
 */
double *sorLivre(Data *input,Point *lPoints,double omega, double toler, int iterMax)
{
	int i/*,j*/,qtdElementos,iter = 0;//,flagOeste = 0, flagLeste = 0;
	double r,soma,*vetSolucao,*vetAux,normaNum,normaDen,normaRel,aux,hx,hy;
	double eI,cI,aI,bI,dI,x,y;

	qtdElementos = input->tamX*input->tamY;

	hx = (input->fimX - input->iniX)/((double)(input->tamX - 1));
	hy = (input->fimY - input->iniY)/((double)(input->tamY - 1));

	vetSolucao = calloc((size_t)qtdElementos,sizeof(double));
	vetAux = calloc((size_t)qtdElementos,sizeof(double));

	
	

	for( i = 0; i < qtdElementos; i++)
	{
		aI = GAMA(x,y)+ 2*K*((1/(hx*hx)) + (1/(hy*hy)));
		r = 1/(aI);
		vetSolucao[i] = F(lPoints[i].x,lPoints[i].y)*r;
	}

	do
	{
		iter++;

		/* LOOP PARA A INSERÇÃO DE CONTORNO U(x,0) */
		for(i = 0; i < input->tamX;i++)
		{
			soma = 0;
			x = lPoints[i].x;
			y = lPoints[i].y;
			if(!CONTORNOsulDERIVADA)
				setContornoComum(&aI,&bI,&cI,&dI,&eI);	
			else{}
			r = 1/aI;
			vetAux[i] = vetSolucao[i];
			vetSolucao[i] = omega * ( (CONTORNOnorte(x,y)) *r - soma) + (1 - omega) * vetSolucao[i];
		}

		/* LOOP PARA RESOLVER PONTOS INTERNOS E INSERÇÃO DE CONTORNO U(L,y) e U(0,y) */
		for(i = input->tamX; i < qtdElementos - input->tamX; i++)
		{
			soma = 0;
			x = lPoints[i].x;
			y = lPoints[i].y;
			/* CONDIÇÃO PARA A INSERÇÃO DE CONTORNO U(0,y) */
			if(i % input->tamX == 0)
			{
				if(!CONTORNOoesteDERIVADA)
					setContornoComum(&aI,&bI,&cI,&dI,&eI);
				else{}
				r = 1/aI;
				vetAux[i] = vetSolucao[i];
				vetSolucao[i] = omega * ( (CONTORNOoeste(x,y)) *r - soma) + (1 - omega) * vetSolucao[i];
			}else if(i % input->tamX == input->tamX-1)	/* CONDIÇÃO PARA A INSERÇÃO DE CONTORNO U(L,y) */
			{
				if(!CONTORNOlesteDERIVADA)
				{	
					setContornoComum(&aI,&bI,&cI,&dI,&eI);
					r = 1/aI;
					vetAux[i] = vetSolucao[i];
					vetSolucao[i] = omega * ( (CONTORNOleste(x,y)) *r - soma) + (1 - omega) * vetSolucao[i];
				}else /* CONDIÇÃO PARA A INSERÇÃO DE CONTORNO U(L,y) com DERIVADA */
				{
					aI = GAMA(x,y)+ 2*K*((1/(hx*hx)) + (1/(hy*hy)));
					bI = ((-1*K)/(hx*hx))+(BETAx(x,y)/(2*hx));
					aI = aI + bI * (1 - hx); 
					// bI = 0;
					r = 1/aI;	
					cI = ((-1*K)/(hx*hx))-(BETAx(x,y)/(2*hx));
					soma += cI *r * vetSolucao[i-1];

					eI = ((-1*K)/(hy*hy))-(BETAy(x,y)/(2*hy));
					soma += eI * r * vetSolucao[i-input->tamX];
				
					dI = ((-1*K)/(hy*hy))+(BETAy(x,y)/(2*hy));
					soma += dI * r * vetSolucao[i+input->tamX];
				
					vetAux[i] = vetSolucao[i];
					vetSolucao[i] = omega * ( ((F(x,y)) - 70*hx*bI) *r - soma) + (1 - omega) * vetSolucao[i];
				}
				
			}else	/* CALCULO DE PONTOS INTERNOS */
			{
				aI = GAMA(x,y)+ 2*K*((1/(hx*hx)) + (1/(hy*hy)));
				r = 1/(aI);

					bI = ((-1*K)/(hx*hx))+(BETAx(x,y)/2*hx);
					soma += bI * r * vetSolucao[i+1];//F(lPoints[i+1].x,lPoints[i+1].y);
			
					cI = ((-1*K)/(hx*hx))-(BETAx(x,y)/2*hx);
					soma += cI *r * vetSolucao[i-1];//F(lPoints[i-1].x,lPoints[i-1].y);

					eI = ((-1*K)/(hy*hy))-(BETAy(x,y)/2*hy);
					soma += eI * r * vetSolucao[i-input->tamX];//F(lPoints[i-input->tamX].x,lPoints[i - input->tamX].y);
				
					dI = ((-1*K)/(hy*hy))+(BETAy(x,y)/2*hy);
					soma += dI * r * vetSolucao[i+input->tamX];//F(lPoints[i + input->tamX].x,lPoints[i + input->tamX].y);
				
				vetAux[i] = vetSolucao[i];
				vetSolucao[i] = omega * ( (F(x,y)) *r - soma) + (1 - omega) * vetSolucao[i];
			}
		}

		/* LOOP PARA A INSERÇÃO DE CONTORNO U(x,W) */
		for(i = qtdElementos - input->tamX; i < qtdElementos;i++)
		{
			soma = 0;
			x = lPoints[i].x;
			y = lPoints[i].y;
			if(!CONTORNOnorteDERIVADA)
				setContornoComum(&aI,&bI,&cI,&dI,&eI);
			else{}
			r = 1/aI;
			vetAux[i] = vetSolucao[i];
			vetSolucao[i] = omega * ( (CONTORNOsul(x,y)) *r - soma) + (1 - omega) * vetSolucao[i];
		}

		normaNum = 0;
		normaDen = 0;
		for( i = 0; i < qtdElementos; i++)
		{
			aux = fabs(vetSolucao[i] - vetAux[i]);
			if( aux > normaNum)
				normaNum = aux;
			if(fabs(vetSolucao[i]) > normaDen)
				normaDen = fabs(vetSolucao[i]);
		}
		normaRel = normaNum/normaDen;
	}while(normaRel > toler && iter < iterMax);
	free(vetAux);
	if(normaRel < toler) printf("CONVERGIU! :)\n"); else printf("NAO CONVERGIU! :(\n");
	printf("Numero de iteracoes: %d\n",iter);
	printf("Erro: %g\n",normaRel);
	return vetSolucao;
}
