#include <string>
#include <ctime>
#include "Midia.h"

using namespace std;

class Emprestimo{

private:
	int codigomidia;
	string tomador;
	struct tm emprestimo;
	struct tm devolucao;

public:
	Emprestimo(int codigomidia, string tomador, struct tm emprestimo, struct tm devolucao);
	int getMidia();
	string getTomador();
	struct tm getEmprestimo();
	struct tm getDevolucao();	
};
