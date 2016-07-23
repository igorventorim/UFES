#include <string>
#include <vector>
#ifndef Genero_H
#define Genero_H
using namespace std;

class Midia;
class Genero{

private:
	string sigla;
	string nome;
	vector<Midia*> midiasGenero;

public:
	Genero(string sigla, string nome);
	string getSigla();
	string getNome();
	void addMidiaGen(Midia& m);
	vector<Midia*> getMidiaGen();
	int qtdGenero();
};

#endif
