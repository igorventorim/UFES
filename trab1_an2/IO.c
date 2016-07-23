#include "IO.h"
#include "pvc.h"

/**
 * [printInfo description]
 */
void printInfo()
{
    printf("Sintaxe: ./trab1 [Algoritmo] [Metodo de Entrada]\n");
    printf("Algoritmos: sorComum / sorLivre \n");
    printf("Metodos de entrada: -t (teclado) / -f [arquivo]\n");
    printf("Exemplos:\n ./trab1 sorComum -t\n ./trab1 sor -f exemplo.txt\n");
}

/**
 * [readInputKey description]
 * @param input      [description]
 * @param omega      [description]
 * @param tolerancia [description]
 * @param iterMax    [description]
 */
void readInputKey(Data *input, double *omega, double *tolerancia, int *iterMax)
{
	printf("Informe o inicio do dominio X: ");
	scanf("%lf",&input->iniX);

	printf("Informe o fim do dominio X: ");
	scanf("%lf",&input->fimX);

	printf("Informe o inicio do dominio Y: ");
	scanf("%lf",&input->iniY);

	printf("Informe o fim do dominio Y: ");
	scanf("%lf",&input->fimY);

	printf("Informe a quantidade de pontos X: ");
	scanf("%d",&input->tamX);

	printf("Informe a quantidade de pontos Y: ");
	scanf("%d",&input->tamY);

	printf("Informe o valor de OMEGA: ");
	scanf("%lf",omega);

	printf("Informe o valor de tolerancia: ");
	scanf("%lf",tolerancia);

	printf("Informe o numero maximo de iteracoes: ");
	scanf("%d",iterMax);
}

/**
 * [readInputFile description]
 * @param input      [description]
 * @param omega      [description]
 * @param tolerancia [description]
 * @param iterMax    [description]
 * @param nameFile   [description]
 */
void readInputFile(Data *input, double *omega, double *tolerancia, int *iterMax, char *nameFile)
{
	FILE *f = fopen(nameFile,"r");

	if(!f)
	{
		printf("ERRO AO ABRIR O ARQUIVO!");
		return;
	}

	fscanf(f,"%lf",&input->iniX);
	fscanf(f,"%lf",&input->fimX);
	fscanf(f,"%lf",&input->iniY);
	fscanf(f,"%lf",&input->fimY);
	fscanf(f,"%d",&input->tamX);
	fscanf(f,"%d",&input->tamY);
	fscanf(f,"%lf",omega);
	fscanf(f,"%lf",tolerancia);
	fscanf(f,"%d",iterMax);

	fclose(f);
}

/**
 * [writeOut description]
 * @param vetorSolucao [description]
 * @param input        [description]
 */
void writeOut(double *vetorSolucao,Data *input)
{
	FILE *f = fopen("saida.txt","w");

	if(!f)
	{
		printf("ERRO AO ABRIR O ARQUIVO!");
		return;
	}

	int i,j;
	/* IMPRIMINDO NO FORMATO MATRIZ */
	for(i = (input->tamX*input->tamY)-1; i >= 0; i -= input->tamX+1)
	{
		 // printf("%d - %d = %d\n\n",i,input.tamX-1,(i - input.tamX)+1);
		for(j = 0,i = i - input->tamX+1; j < input->tamX; i++, j++)
			// printf(" %d ",i);
			fprintf(f,"   %.2f   ",vetorSolucao[i]);
		// i -= input.tamX; 
		fprintf(f,"\n");
	}

	FILE *vector = fopen("vetorSolucao.txt","w");

	if(!vector)
	{
		printf("ERRO AO ABRIR O ARQUIVO!");
		return;
	}

	for(int i = 0; i < input->tamX*input->tamY;i++)		
		fprintf(vector,"%lf\n", vetorSolucao[i]);

	fclose(vector);
	fclose(f);	
}
