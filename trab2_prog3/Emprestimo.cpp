#include "Emprestimo.h"

/**
 * Construtor de Emprestimo
 * @param midia midia emprestada
 * @param tomador quem tomou a midia
 * @param emprestimo data de emprestimo
 * @param devolucao data de devolucao
 */
Emprestimo::Emprestimo(int codigomidia, string tomador, struct tm emprestimo, struct tm devolucao) {
	this->codigomidia = codigomidia;
	this->tomador = tomador;
	this->emprestimo = emprestimo;
	this->devolucao = devolucao;
}

/**
 * Pega midia
 * @return midia
 */
int Emprestimo::getMidia() {
	return codigomidia;
}

/**
 * Pega tomador
 * @return tomador
 */
string Emprestimo::getTomador() {
	return tomador;
}

/**
 * Pega data de emprestimo
 * @return data de emprestimo
 */
struct tm Emprestimo::getEmprestimo() {
	return emprestimo;
}

/**
 * Pega data de devolucao
 * @return data de devolucao
 */
struct tm Emprestimo::getDevolucao() {
	return devolucao;
}

