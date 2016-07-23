#ifndef IO_C
#define IO_C
#include "pvc.h"
#include <stdio.h>

/**
 * [printInfo description]
 */
void printInfo();

/**
 * [readInput description]
 * @param input      [description]
 * @param omega      [description]
 * @param tolerancia [description]
 * @param iterMax    [description]
 */
void readInputKey(Data *input, double *omega, double *tolerancia, int *iterMax);

/**
 * [readInputFile description]
 * @param input      [description]
 * @param omega      [description]
 * @param tolerancia [description]
 * @param iterMax    [description]
 * @param nameFile   [description]
 */
void readInputFile(Data *input, double *omega, double *tolerancia, int *iterMax, char *nameFile);

/**
 * [writeOut description]
 * @param vetorSolucao [description]
 * @param input        [description]
 */
void writeOut(double *vetorSolucao,Data *input);


#endif