#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void simplex(double **matrix,int M, int N,int *vectorSolution);
void simplex2fases(double **matrix,int M, int N);
void printMatrix(double **matrix, int M, int N);
int getColIndexPivot(double **matrix, int colNumbers);
int getLineIndexPivot(double **matrix, int linesNumber, int indexColPivot, int colsNumber);
void updateMatrix(double **matrix, double pivot,int indexLinePivot, int colsNumber);
void schedule(double **matrix, int linesLimit, int colsLimit, int indexLinePivot, int indexColPivot);
void printVector(double **matrix, int *vector, int M, int N);
void readData(double ***matrix,int *lines, int *cols);
void simplex2fases(double **matrix,int M, int N);
int checkArtificialVariables(double **matrix,int M, int N,int *vector );
double** solverPhase1(double **matrix,int M, int N,int *vector, int qtdArtificalVariables);
int checkContainsArtificial(int *vector, int length);
int* createVector(int M, int N);
void freeMatrix(double **matrix,int M);
void printResult(int tipo, double **matrix,int *vectorSolution, int M, int N);
int checkMultiplasSolucoes(double **matrix, int M, int N,int *vectorSolution);


int main()
{
	double **matrix;
	int M,N;
	int choice;

		printf("1 - Simplex.\n");
		printf("2 - Metodo de duas fases.\n");
		printf("0 - Sair\n");
		printf("Informe qual metodo deseja utilizar: \n");
		scanf("%d",&choice);
		readData(&matrix,&M,&N);
		switch(choice)
		{
			case 1:
				for(int i = 0; i < N; i++){ matrix[0][i] *= -1; } 
				simplex(matrix,M,N,createVector(M,N));
				break;
			case 2:
				for(int i = 0; i < N; i++){ matrix[0][i] *= -1; }
				for(int i = 0; i < N; i++){ matrix[1][i] *= -1; }  
				simplex2fases(matrix,M,N);
				break;
			case 0:
				exit(0);
				
			default:
				printf("Valor informado invalido, tente novamente.\n");
		}	

		freeMatrix(matrix,M);

}

void readData(double ***matrix,int *lines, int *cols)
{

	scanf("%d %d",lines,cols);
	int M = *lines;
	int N = *cols;

	(*matrix) = malloc(M * sizeof(double*));
	
	for(int i = 0; i < M; i++)
	{
		(*matrix)[i] = malloc(N * sizeof(double));
	}

	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			double elemento;
			scanf("%lf",&elemento);
			(*matrix)[i][j] = elemento;
		}
	}

}

int* createVector(int M, int N)
{
	int *vectorSolution;
	vectorSolution = malloc((M-1) * sizeof(int));

	for(int i = 0; i < M-1; i++)
	{
		vectorSolution[i] = N-M+i+1;
	}

	return vectorSolution;
}

void simplex(double **matrix,int M, int N,int *vectorSolution)
{

	
	int tipo = 0;
	printMatrix(matrix,M,N);
	int indexColPivot = getColIndexPivot(matrix,N);
	int indexLinePivot = getLineIndexPivot(matrix,M,indexColPivot,N);
	printf("Col Index: %d\n",indexColPivot);
	printf("Line Index: %d\n",indexLinePivot);

	while(indexColPivot != -1)
	{

		if(indexLinePivot != -1)
		{
			vectorSolution[indexLinePivot-1] = indexColPivot+1;
			updateMatrix(matrix,matrix[indexLinePivot][indexColPivot],indexLinePivot,N);
			schedule(matrix, M, N, indexLinePivot, indexColPivot);

			indexColPivot = getColIndexPivot(matrix,N);
			indexLinePivot = getLineIndexPivot(matrix,M,indexColPivot,N);

		}else
		{ 
			// printf("Verificar o que significa quando chega neste estado!!!\n");
			// exit(0);
			tipo = 3;
			break;
		}
		
		printMatrix(matrix,M,N);
		printf("Col Index: %d\n",indexColPivot);
		printf("Line Index: %d\n",indexLinePivot);
		
	}

	if(tipo != 3)
	{	
		tipo = checkMultiplasSolucoes(matrix,M,N,vectorSolution);
	}
	

	printResult(tipo,matrix,vectorSolution,M,N);
	free(vectorSolution);

	
	
}

int checkMultiplasSolucoes(double **matrix, int M, int N,int* vectorSolution)
{
	int ok =0;
	for(int i = 0; i < N-1; i++)
	{
		if(matrix[0][i] == 0)
		{
			// printf("%d \n\n",i);
			for(int j = 0; j < M-1; j++)
			{
				if(vectorSolution[j]-1 == i)
				{
					ok = 1;
				}
			}
			if(ok != 1){ return 2;} else{ ok = 0;}
		}
	}

	return 0;
}

void updateMatrix(double **matrix, double pivot,int indexLinePivot, int colsNumber)
{
	for(int i = 0; i < colsNumber; i++)
	{
		matrix[indexLinePivot][i] = matrix[indexLinePivot][i]/pivot; 
	}


}

void schedule(double **matrix, int linesLimit, int colsLimit, int indexLinePivot, int indexColPivot)
{
	for(int i = 0; i < linesLimit;i++)
	{
		if( i == indexLinePivot){ continue;}
		double divisor = matrix[i][indexColPivot];
		for(int j = 0; j < colsLimit; j++)
		{
				matrix[i][j] = (-1)*divisor*matrix[indexLinePivot][j] + matrix[i][j];  
		}
	}
}

int getColIndexPivot(double **matrix, int colsNumber)
{
	double max = 0, index = -1;
	for(int i = 0; i < colsNumber-1; i++)
	{
		if (matrix[0][i] > max)
		{
			max = matrix[0][i];
			index = i;
		}
	}

	return index;
}

int getLineIndexPivot(double **matrix, int linesNumber, int indexColPivot, int colsNumber)
{
	double min = FLT_MAX, index = -1;
	if(indexColPivot == -1){ return -1;}
	for(int i = 1; i < linesNumber; i++)
	{
		if(matrix[i][indexColPivot] > 0 && matrix[i][colsNumber-1] >= 0 && matrix[i][colsNumber-1]/matrix[i][indexColPivot] < min)
		{
			min = matrix[i][colsNumber-1]/matrix[i][indexColPivot];
			index = i;
		}
	}

	// for(int i = 1; i < linesNumber; i++)
	// {
	// 	printf("%f\n", matrix[i][indexColPivot]);
	// }	

	return index;
}

void printMatrix(double **matrix, int M, int N)
{
	printf("\n");
	for(int i = 0; i < M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf("%.2lf ",matrix[i][j]);
		}
		printf("\n");
	}
}

void printVector(double **matrix, int *vector, int M, int N)
{
	double *vet = calloc(N-1,sizeof(double));
	for(int i = 1; i < M; i++)
	{

		vet[vector[i-1]-1] = matrix[i][N-1];
	}
	// printf("\n");
	printf("(");
	for(int i = 0; i < N-2; i++)
	{
		 printf(" %.3f,",vet[i]);		
	}
		printf(" %.3f )\n",vet[N-2]);
	free(vet);
}

void simplex2fases(double **matrix,int M, int N)
{
	int vector[N];
	// printMatrix(matrix,M,N);
	int qtdArtificalVariables = checkArtificialVariables(matrix,M,N,vector);
	// printf("%d\n",qtdArtificalVariables);
	printMatrix(matrix,M,N);
	
	double **newMatrix = solverPhase1(matrix,M, N,vector, qtdArtificalVariables);
	freeMatrix(newMatrix,M-1);

}

double** solverPhase1(double **matrix,int M, int N,int *vector, int qtdArtificalVariables)
{
	int *vectorSolution = createVector(M,N);
	int tipo = 0;
	for(int i = 0; i < qtdArtificalVariables;i++)
	{
		vectorSolution[vector[i]-2] = -1;
	}

	while( checkContainsArtificial(vectorSolution,M-2))
	{
		int indexColPivot = getColIndexPivot(matrix,N);
		int indexLinePivot = getLineIndexPivot(matrix,M,indexColPivot,N);
		printf("Col Index: %d\n",indexColPivot);
		printf("Line Index: %d\n",indexLinePivot);

		if(indexColPivot != -1)
		{
			if(indexLinePivot != -1)
			{
				vectorSolution[indexLinePivot-2] = indexColPivot+1;
				updateMatrix(matrix,matrix[indexLinePivot][indexColPivot],indexLinePivot,N);
				schedule(matrix, M, N, indexLinePivot, indexColPivot);
				indexColPivot = getColIndexPivot(matrix,N);
				indexLinePivot = getLineIndexPivot(matrix,M,indexColPivot,N);

			}else{ printf("Algoritmo nao encontrou nao negativo!\n"); break;}
		}else{ printf("Algoritmo nao encontrou nao negativo!\n"); break;}
		printMatrix(matrix,M,N);

	}

	if(matrix[0][N-1] != 0)
	{
		tipo = 1;
	}
	
	

	double **newMatrix;
	newMatrix = malloc((M-1) * sizeof(double*));
	
	for(int i = 0; i < M-1; i++)
	{
		newMatrix[i] = malloc((N - qtdArtificalVariables) * sizeof(double));
	}

	for(int i = 0; i < M-1; i++)
	{
		for(int j = 0; j < N - qtdArtificalVariables-1; j++)
		{
			newMatrix[i][j] = matrix[i+1][j];
		}
	}

	for(int i = 0; i < M-1; i++)
	{
		newMatrix[i][N - qtdArtificalVariables-1] = matrix[i+1][N-1];
	}

	// printMatrix(newMatrix,M-1,N - qtdArtificalVariables);
	if(tipo != 1)
	{
		simplex(newMatrix,M-1,N - qtdArtificalVariables,vectorSolution);
	}else
	{
		printResult(tipo,matrix,vectorSolution,M,N);
	}
	

	return newMatrix;	
}

int checkArtificialVariables(double **matrix,int M, int N,int *vector )
{
	int count = 0;
	for(int i = 0; i < N-1; i++)
	{
		if(matrix[0][i] == -1)
		{
			
			for(int j = 0; j < M; j++)
			{
				if(matrix[j][i] == 1)
				{
					vector[count] = j;
				}
			}
			count++;
		}
	}

	for(int i = 0; i < count; i++)
	{
		for(int j = 0; j < N; j++)
		{
			matrix[0][j] += matrix[vector[i]][j]; 
		}
	}

	return count;
}

int checkContainsArtificial(int *vector, int length)
{
	for(int i = 0; i < length; i++)
	{
		if(vector[i] == -1)
		{
			return 1;
		}
	}

	return 0;
}

void printResult(int tipo, double **matrix,int *vectorSolution, int M, int N)
{

	switch(tipo)
	{
		case 0:
			printf("\n\nZ* = %.3f X=",matrix[0][N-1]);
			printVector(matrix,vectorSolution,M,N);
			printf("Solucao unica.\n");
			printMatrix(matrix,M,N);
			printf("\n\n");
			break;

		case 1:
			printf("Z* = Nao possui solucao viavel.\n");
			break;

		case 2:
			printf("\n\nZ* = %.3f X=",matrix[0][N-1]);
			printVector(matrix,vectorSolution,M,N);
			printf("Multiplas Solucoes.\n");
			printMatrix(matrix,M,N);
			printf("\n\n");
			break;

		case 3:
			printf("Z* = -inf\n");
			break;	
	}
}

void freeMatrix(double **matrix,int M)
{
	for(int i = 0; i < M; i++)
	{
		free(matrix[i]);
	}

	free(matrix);
}

