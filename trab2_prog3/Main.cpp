#include "FileIO.cpp"

using namespace std;

/**
 * Verifica se um string pertence a um vetor de strings
 * @param args vetor de strings
 * @param param string a ser procurado no vetor
 * @return indice do string no vetor ou -1 caso nao foi encontrado
 */
int isIn(char *args[], char param[], int argc)
{
	
	int i;
	
	for(i=0;i<argc;i++)
		if(!strcmp(param,args[i]))
			return i;
	
	return -1;
	
}
/**
 * Metodo principal para execucao do programa
 * @param args argumentos passados por linha de comando
 * @throws IOException
 * @throws ParseException
 */
int main(int argc, char *argv[]){
	map<int,Pessoa> p;
	map<string,Genero> g;
	map<int,Midia*> m;
	map<int,Emprestimo> e;
	int idx;
	try{
	idx = isIn(argv, (char*)"-g",argc);
	if(idx!=-1)
		g = readGenero(argv[idx+1]);
		if(g.size()==0)
		 return -1;
	
	idx = isIn(argv, (char*)"-p",argc);
	if(idx!=-1)
		p = readPessoa(argv[idx+1]);
		if(p.size()==0)
		 return -1;
	
	idx = isIn(argv, (char*)"-m",argc);
	if(idx!=-1){
		m = readMidia(argv[idx+1],p,g);	
		if(m.size()==0)
		 return -1;
		generatorWishList(m);
		generatorPorPessoa(p);
		generatorEstatisticas(p,m,g);		
	}
	
	idx = isIn(argv, (char*)"-e",argc);
	if(idx!=-1){
		
		e = readEmprestimo(argv[idx+1],m);
		if(e.size()==0)
		 return -1;
		generatorEmprestimos(e);
		
	}
		freeMidia(m);
	}catch(exception& f)
	{

	}
}
