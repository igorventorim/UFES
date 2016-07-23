#include "Filme.h"

/**
 * Construtor de Filme
 * @param codigo codigo do filme
 * @param nome nome do filme
 * @param tamanho duracao do filme
 * @param genero genero do filme
 * @param possui true se possui este filme ou false caso contrario
 * @param consumiu true se consumiu este filme ou false caso contrario
 * @param deseja true se deseja este filme ou false caso contrario
 * @param preco preco do filme
 * @param diretor diretor do filme
 * @param atores lista de atores do filme
 */
Filme::Filme(int codigo, string nome, int tamanho, Genero& genero, bool possui, bool consumiu, bool deseja, double preco, Pessoa& diretor, vector<Pessoa> atores) : Midia(codigo, nome, tamanho, genero, possui, consumiu, deseja, preco,'F'), diretor(diretor) {
	this->diretor = diretor;
	this->atores = atores;
}

/**
 * Pega diretor
 * @return diretor do filme
 */
Pessoa Filme::getDiretor() {
	return diretor;
}

/**
 * Pega atores
 * @return lista de atores do filme
 */
// list<Pessoa> Filme::getAtores() {
// 	return atores;
// }
