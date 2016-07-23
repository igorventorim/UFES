#include "Livro.h"

/**
 * Construtor de Livro
 * @param codigo codigo do livro
 * @param nome nome do livro
 * @param tamanho quantidade de paginas do livro
 * @param genero genero do livro
 * @param possui true se possui este livro ou false caso contrario
 * @param consumiu true se consumiu este livro ou false caso contrario
 * @param deseja true se deseja este livro ou false caso contrario
 * @param preco preco do livro
 * @param autores lista de autores do livro
 */
Livro::Livro(int codigo, string nome, int tamanho, Genero& genero, bool possui, bool consumiu, bool deseja, double preco, vector<Pessoa> autores) : Midia(codigo, nome, tamanho, genero, possui, consumiu, deseja, preco, 'L') {
	this->autores = autores;
}

/**
 * Pega autores do livro
 * @return lista de autores do livros
 */
vector<Pessoa> Livro::getAutores() {
	return autores;
}
