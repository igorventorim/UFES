#include<set>
#include<cstdio>
#include"Genero.h"

#ifndef Midia_H
#define Midia_H
using namespace std;

class Midia{

private:
	int codigo;
	string nome;
	char type;
	int tamanho;
	Genero genero;
	bool possui;
	bool consumiu;
	bool deseja;
	double preco;

public:
	Midia(int codigo, string nome, int tamanho, Genero& genero, bool possui, bool consumiu, bool deseja, double preco, char type);
	Midia();
	char getType();
	void setType(char type);
	int getCodigo();
	string getNome();
	int getTamanho();
	Genero& getGenero();
	bool isPossui();
	bool isConsumiu();
	bool isDeseja();
	double getPreco();
	void setPossui(bool possui);
	void setConsumiu(bool consumiu);
	void setDeseja(bool deseja);
	void setPreco(double preco);
	string toString();
	int compareTo(Midia otherMidia);
	virtual ~Midia(){}
	virtual string getTemporada(){}

};

#endif
