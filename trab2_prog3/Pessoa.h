#include <string>
#include <vector>
#include "Midia.h"

#ifndef Pessoa_H
#define Pessoa_H

using namespace std;
class Midia;

class Pessoa {

private:
	int codigo;
	string nome;
	vector<Midia> trabalhos;
	
public:
	Pessoa(int codigo, string nome);
	Pessoa();
	int getCodigo();
	string getNome();
	vector<Midia>& getTrabalhos();
	void addMidia(Midia& midia);
	
};

#endif
