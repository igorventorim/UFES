#include "Pessoa.h"
/**
 * Construtor de Pessoa
 * @param codigo codigo da pessoa
 * @param nome nome da pessoa
 */
Pessoa::Pessoa(int codigo, string nome) {
	this->codigo = codigo;
	this->nome = nome;
}

/**
 * Construtor de Pessoa
 */
Pessoa::Pessoa(){}

/**
 * Pegar codigo de Pessoa
 * @return codigo da pessoa
 */
int Pessoa::getCodigo() {
	return codigo;
}

/**
 * Pegar nome de Pessoa
 * @return nome da pessoa
 */
string Pessoa::getNome() {
	return nome;
}

/**
 * Adicionar midia a pessoa
 * @param m midia a ser adicionada
 */
void Pessoa::addMidia(Midia& midia)//:midia(midia)
{
	this->trabalhos.push_back(midia);
}


/**
 * Pega lista de midias feitas pela pessoa
 * @return conjunto de midias realizadas por pessoa
 */
vector<Midia>& Pessoa::getTrabalhos() {
 	return trabalhos;
}

