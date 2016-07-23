#ifndef SOR_H
#define	SOR_H

/**
 * [sor description]
 * @param  newMat          [description]
 * @param  vetIndependente [description]
 * @param  omega           [description]
 * @param  tolerancia      [description]
 * @param  iterMax         [description]
 * @return                 [description]
 */
double *sor(MatColuna *newMat, double *vetIndependente, double omega, double tolerancia, int iterMax);

/**
 * [sorLivre description]
 * @param  input   [description]
 * @param  lpoints [description]
 * @param  omega   [description]
 * @param  toler   [description]
 * @param  iterMax [description]
 * @return         [description]
 */
double *sorLivre(Data *input,Point *lpoints,double omega, double toler, int iterMax);

#endif