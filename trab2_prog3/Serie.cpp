#include "Serie.h"

/**
 * Construtor de Serie
 * @param codigo codigo da serie
 * @param nome nome da serie
 * @param tamanho duracao da serie
 * @param genero genero da serie
 * @param possui true se possui esta serie ou false caso contrario
 * @param consumiu true se consumiu esta serie ou false caso contrario
 * @param deseja true se deseja esta serie ou false caso contrario
 * @param preco preco da serie
 * @param atores lista de atores da serie
 * @param temporada temporada da serie
 * @param nameSerie nome da serie
 */
Serie::Serie(int codigo, string nome, int tamanho, Genero& genero, bool possui, bool consumiu, bool deseja, double preco, vector<Pessoa> atores, string temporada, string nameSerie) : Midia(codigo, nome, tamanho, genero, possui, consumiu, deseja, preco, 'S') {
	this->atores = atores;
	this->temporada = temporada;
	//cout << this->temporada << endl;
	this->nameSerie = nameSerie;
}

/**
 * Pega lista de atores da serie
 * @return lista de atores da serie
 */
vector<Pessoa> Serie::getAtores() {
	return atores;
}

/**
 * Pega temporada da serie
 * @return temporada da serie
 */
string Serie::getTemporada() {
	return temporada;
}

/**
 * Pega nome da serie
 * @return nome da serie
 */
string Serie::getNomeSerie() {
	return nameSerie;
}
