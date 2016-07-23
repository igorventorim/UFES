#include <stdio.h>
#include <stdlib.h>
#include "pvc.h"
#include "sor.h"
#include "string.h"
#include "IO.h"


int main(int argc, char **argv)
{
	Data input;
	Point *lPoints;
	MatColuna *newMatriz;
	double *vetIndependente,tolerancia,omega,*vetorSolucao;
	int iterMax;

	if(argc < 3)
	{
		printInfo();
		return 1;
	}
	
	if(!strcmp(argv[1],"sorComum"))
	{
		if(!strcmp(argv[2],"-t"))
			readInputKey(&input,&omega,&tolerancia,&iterMax); 
		else if(!strcmp(argv[2],"-f"))
			readInputFile(&input, &omega, &tolerancia, &iterMax, argv[3]);
		else{printInfo(); return 1;}
		
		lPoints = criaLPoints(input.tamX,input.tamY);
		newMatriz = criaMatrizColuna(input.tamX,input.tamY);
		discretiza(&input,lPoints);
		vetIndependente = criaVetorIndependente(&input,lPoints);
		buildingMatrix(&input,newMatriz,lPoints);
		inserirContorno(newMatriz, vetIndependente, &input,lPoints);
		vetorSolucao = sor(newMatriz,vetIndependente,omega,tolerancia,iterMax);
		printMatriz(vetorSolucao,input);
		writeOut(vetorSolucao,&input);
		freeMatColuna(newMatriz);
		free(vetIndependente);

	}else if(!strcmp(argv[1],"sorLivre"))
	{
		if(!strcmp(argv[2],"-t"))
			readInputKey(&input,&omega,&tolerancia,&iterMax);
		else if(!strcmp(argv[2],"-f"))
			readInputFile(&input, &omega, &tolerancia, &iterMax, argv[3]);
		else{ printInfo(); return 1;}

		lPoints = criaLPoints(input.tamX,input.tamY);
		discretiza(&input,lPoints);
		vetorSolucao = sorLivre(&input,lPoints,omega,tolerancia,iterMax);
		// printMatriz(vetorSolucao,input);
		writeOut(vetorSolucao,&input);

	}else{printInfo(); return 1;} 
	printf("\n\n\n");
	// for(int i = 0; i < input.tamX*input.tamY;i++)
	// {
		// double x = lPoints[i].x;
		// double y = lPoints[i].y;		
		// printf("%lf\n",10 * x*y*(1-x)*(1-y)*(pow(e,pow(x,4.5))));
		// vetorSolucao[i] = 10 * x*y*(1-x)*(1-y)*(pow(e,pow(x,4.5)));
		// printf("%lf    -   %lf\n",10 * x*y*(1-x)*(1-y)*(pow(e,pow(x,4.5))), vetorSolucao[i]);
	// }

	printMatriz(vetorSolucao,input);

	freeLPoints(lPoints);
	free(vetorSolucao);

	return 0;
}