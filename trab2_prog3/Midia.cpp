#include "Midia.h"

using namespace std;

/**
 * Construtor de Midia
 * @param codigo codigo da midia
 * @param nome nome da midia
 * @param tamanho tamanho da midia
 * @param genero genero da midia
 * @param possui true se possui esta midia ou false caso contrario
 * @param consumiu true se consumiu esta midia ou false caso contrario
 * @param deseja true se deseja esta midia ou false caso contrario
 * @param preco preco da midia
 * @param type tipo de midia
 */
Midia::Midia(int codigo, string nome, int tamanho, Genero& genero, bool possui, bool consumiu, bool deseja, double preco, char type): genero(genero){
	this->codigo = codigo;
	this->nome = nome;
	this->tamanho = tamanho;
	this->possui = possui;
	this->consumiu = consumiu;
	this->deseja = deseja;
	this->preco = preco;
	this->type = type;
}

Midia::Midia():genero(genero){}
/**
 * Construtor de Midia
 */
//Midia::Midia(){}

/**
 * Pega tipo de midia
 * @return tipo de midia
 */
char Midia::getType() {
	return type;
}

/**
 * Altera tipo de midia
 * @param type tipo de midia
 */
void Midia::setType(char type) {
	this->type = type;
}

/**
 * Pega codigo da midia
 * @return codigo da midia
 */
int Midia::getCodigo() {
	return codigo;
}

/**
 * Pega nome da midia
 * @return nome da midia
 */
string Midia::getNome() {
	return nome;
}

/**
 * Pega tamanho da midia
 * @return tamanho da midia
 */
int Midia::getTamanho() {
	return tamanho;
}

/**
 * Pega genero da midia
 * @return genero da midia
 */
Genero& Midia::getGenero() {
	return genero;
}

/**
 * Verifica se possui midia
 * @return true se possui midia ou false caso contrario
 */
bool Midia::isPossui() {
	return possui;
}

/**
 * Verifica se consumiu midia
 * @return true se consumiu midia ou false caso contrario
 */
bool Midia::isConsumiu() {
	return consumiu;
}

/**
 * Verifica se deseja midia
 * @return true se deseja midia ou false caso contrario
 */
bool Midia::isDeseja() {
	return deseja;
}

/**
 * Pega preco da midia
 * @return preco da midia
 */
double Midia::getPreco() {
	return preco;
}

/**
 * Altera posse da midia
 * @param possui true se possui ou false caso contrario
 */
void Midia::setPossui(bool possui) {
	this->possui = possui;
}

/**
 * Altera consumo da midia
 * @param consumiu true se consumiu ou false contrario
 */
void Midia::setConsumiu(bool consumiu) {
	this->consumiu = consumiu;
}

/**
 * Altera desejo da midia
 * @param deseja true se deseja ou false caso contrario
 */
void Midia::setDeseja(bool deseja) {
	this->deseja = deseja;
}

/**
 * Altera preco da midia
 * @param preco preco da midia
 */
void Midia::setPreco(double preco) {
	this->preco = preco;
}

string Midia::toString()
{
  char pc[10],tm[10];
	sprintf(pc,"%.2lf",preco);
	sprintf(tm,"%d",tamanho);
	return "Nome: "+nome+", tipo: "+type+", preço: "+pc+", tamanho: "+tm;
}

// /**
//  * Método de critério de ordenação
//  */
// int Midia::compareTo(Midia otherMidia) {
// 	locale br = setlocale(LC_ALL, "Portuguese");
// 	collate collator = use_facet<collate<char> >(br);
//     if (this->type < otherMidia.type) {
//         return -1;
//     }
//     else if (this->type > otherMidia.type) {
//         return 1;
//     }else
//     {
//     	if(this->preco > otherMidia.preco)
//     	{
//     		return -1;
//     	}else if(this->preco < otherMidia.preco)
//     		return 1;
//     	else
//     	{
//     		return collator.compare(this->getNome(), this->getNome()+this->getNome().length(), otherMidia.getNome(), otherMidia.getNome()+otherMidia.getNome().length());
//     	}
//     }
// }
