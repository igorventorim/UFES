#include <vector>
#include "Midia.h"
#include "Pessoa.h"

using namespace std;

class Livro : public Midia {

private:
	vector<Pessoa> autores;
	
public:
	Livro(int codigo, string nome, int tamanho, Genero& genero, bool possui, bool consumiu, bool deseja, double preco, vector<Pessoa> autores);
	vector<Pessoa> getAutores();
	
};
