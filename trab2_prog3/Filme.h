#include <vector>
#include "Midia.h"
#include "Pessoa.h"

using namespace std;

class Filme : public Midia {

private:
	Pessoa diretor;
	vector<Pessoa> atores;
	
public:
	Filme(int codigo, string nome, int tamanho, Genero& genero, bool possui, bool consumiu, bool deseja, double preco, Pessoa& diretor, vector<Pessoa> atores);
	Pessoa getDiretor();
	vector<Pessoa> getAtores();
	
};	
