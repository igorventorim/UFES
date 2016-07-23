#include"Genero.h"

using namespace std;

/**
 * Construtor de Genero
 * @param sigla sigla do genero
 * @param nome nome do genero
 */
Genero::Genero(string sigla, string nome) {
	this->sigla = sigla;
	this->nome = nome;
}

/**
 * Pega sigla do genero
 * @return sigla do genero
 */
string Genero::getSigla() {
	return sigla;
}

/**
 * Pega nome do genero
 * @return nome do genero
 */
string Genero::getNome() {
	return nome;
}

/**
 * Adiciona midia com genero correspondente
 * @param m midia a ser adicionada
 */
void Genero::addMidiaGen(Midia& m)
{
	midiasGenero.push_back(&m);
}

// /**
//  * Retorna quantidade de generos
//  * @return quantidade de generos
//  */
int Genero::qtdGenero()
{
	return midiasGenero.size();
}
/**  */
vector<Midia*> Genero::getMidiaGen()
{
	return midiasGenero;
}
