#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <map>
#include <fstream>
#include "Filme.h"
#include "Livro.h"
#include "Serie.h"
#include "Emprestimo.h"
#include <vector>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <string>
#include <stdexcept>

using namespace std;

class Genero;
class Pessoa;
class Midia;
class Emprestimo;

/**
 * [StringSplit description]
 * @param  str     [description]
 * @param  delim   [description]
 * @param  results [description]
 * @return         [description]
 */
void static StringSplit(string str, string delim, vector<string>& results)
{
  int cutAt;
  while((cutAt = str.find_first_of(delim)) != str.npos)
  {
    if(cutAt >= 0) {
      results.push_back(str.substr(0,cutAt));
    }
    str = str.substr(cutAt+1);
  }
  if(str.length() >= 0) {
    results.push_back(str);
  }
}

/**
 * [readGenero description]
 * @param  file [description]
 * @return      [description]
 */
map<string,Genero> static readGenero(char *file)
{
	// char *ptr;
	map<string,Genero> g;
	ifstream inFile;//(file);
	inFile.open(file);
	if(inFile){
	string line;
	vector<string> partes;

	if(!inFile) 
	{
		cout << "Não foi possivel abrir o arquivo de entrada : " << file << " Saindo do programa!\n";
		return g;
	}

	getline(inFile,line);
				
	while(!inFile.eof())
	{
		getline(inFile,line);
		if(line.length() < 1) break;
		StringSplit(line,";",partes);
		if(*(partes[1].begin())==' ') partes[1].erase(partes[1].begin());
		if(*(partes[1].end()-1)>126||*(partes[1].end()-1)<33) partes[1].pop_back();
		g.insert(pair<string,Genero>(partes[0],Genero(partes[0],partes[1])));	
		// count +=2;
		partes.clear();
	}

	inFile.close();
	}
	else{
		cout<<"Erro de I/O"<<endl;
	}
	return g;
 
}


/**
 * [readPessoa description]
 * @param  file [description]
 * @return      [description]
 */
map<int,Pessoa> static readPessoa(char *file)
{
	map<int,Pessoa> p;
	ifstream inFile;//(file);
	inFile.open(file);
	if(inFile){
	string line;
	vector<string> partes;
	// unsigned int count = 0;

	if(!inFile) 
	{
		cout << "Não foi possivel abrir o arquivo de entrada : " << file << " Saindo do programa!\n";
		return p;
	}

	getline(inFile,line);
	

	while(!inFile.eof())
	{
		getline(inFile,line);
		if(line.length() < 1) break;
		// cout << line << endl;		
		StringSplit(line,";",partes);
		if(*(partes[1].begin())==' ') partes[1].erase(partes[1].begin());
		if(*(partes[1].end()-1)>126||*(partes[1].end()-1)<33) partes[1].pop_back();

		// if(count < partes.size())
			p.insert(pair<int,Pessoa>(atoi(partes[0].c_str()),Pessoa(atoi(partes[0].c_str()),partes[1])));	
		partes.clear();
	}	
		
	inFile.close();
	}
	else{
		cout<<"Erro de I/O"<<endl;
	}
	return p;
}

/**
 * [createlAtores description]
 * @param  codAutores [description]
 * @param  l          [description]
 * @return            [description]
 */
vector<Pessoa> static createlAtores(string codAutores, map<int,Pessoa>& l)
{
	vector<Pessoa> autores;
	vector<string> partes;
	StringSplit(codAutores,",",partes);
	//cout << codAutores << "\n";
	for(unsigned int i = 0; i < partes.size();i++)
	{
		int idPessoa;
	 	idPessoa = atoi(partes[i].c_str());
	 	//cout << idPessoa << "\n";
	 	if(l.find(idPessoa) == l.end()){
			cout<<"Dados inconsistentes (A(u)tor: "<<idPessoa<<")"<<endl;
			vector<Pessoa> vazio;
			return vazio;
		}
		else{ 
			autores.push_back(l.find(idPessoa)->second);
		}
	}

	return autores;
}

/**
 * [relationPessoaMidia description]
 * @param  p [description]
 * @param  m [description]
 * @return   [description]
 */
void static relationPessoaMidia(vector<Pessoa>& p, Midia& m,map<int,Pessoa>& lPessoas)
{
	for(unsigned int i =0; i < p.size();i++)
		lPessoas.find(p[i].getCodigo())->second.addMidia(m);	
}




/**
 * [readMidia description]
 * @param  file     [description]
 * @param  lPessoas [description]
 * @param  lGenero  [description]
 * @return          [description]
 */
map<int,Midia*> static readMidia(char *file, map<int,Pessoa>& lPessoas, map<string,Genero> &lGenero)
{
	map<int,Midia*> m;
	vector<Pessoa> elenco; 
	ifstream inFile;//(file);
	inFile.open(file);
	if(inFile){
	string line;
	vector<string> partes;
	// int count = 0;

	if(!inFile) 
	{
		cout << "Não foi possivel abrir o arquivo de entrada : " << file << " Saindo do programa!\n";
		return m;
	}

	getline(inFile,line);
	while(!inFile.eof())
	{
		getline(inFile,line);
		if(line.length() < 1) break;
		Pessoa *diretor;
		
		StringSplit(line,";",partes);
		if(*(partes[12].end()-1)>126||*(partes[12].end()-1)<33) partes[12].pop_back();
		int codigo = atoi(partes[0].c_str());
		string nome = partes[1];
		char type = partes[2].at(0);
		string dir = partes[3];
		if(dir.length()>0)
		{
			int id;
			try{
		 	id = atoi(dir.c_str());
		 	diretor = &lPessoas.find(id)->second;
		 	}
		 	catch(const std::out_of_range& oor){
		 		cout<<"Dados inconsistentes (Diretor: "<<id<<")"<<endl;
		 		return m;
		 	}
		}
		 //string lAutores = partes[4];		 
		/** LER LISTA DE AUTORES */
		if(partes[4].length()>0)
			elenco = createlAtores(partes[4],lPessoas);
		int tamanho = atoi(partes[5].c_str());
		string gen = partes[6];
		string serie = partes[7];
		string temporada = partes[8];
		bool possui = !partes[9].compare("x");
		bool consumiu = !partes[10].compare("x") ;
		bool deseja = !partes[11].compare("x");
		replace(partes[12].begin(),partes[12].end(),',','.');
		double preco = atof(partes[12].c_str());
		int flag=0;
		
		switch(type)
		{
			case 'L':
				m.insert(pair<int,Midia*>(codigo,new Livro(codigo,nome,tamanho,lGenero.find(gen)->second,possui,consumiu,deseja,preco,elenco)));
				relationPessoaMidia(elenco,*(m.find(codigo)->second),lPessoas);
				lGenero.find(gen)->second.addMidiaGen(*(m.find(codigo)->second));

				break;
			case 'F':
				m.insert(pair<int,Midia*>(codigo,new Filme(codigo,nome,tamanho,lGenero.find(gen)->second,possui,consumiu,deseja,preco,*diretor,elenco)));
				relationPessoaMidia(elenco,*(m.find(codigo)->second),lPessoas);
				lGenero.find(gen)->second.addMidiaGen(*(m.find(codigo)->second));
				for(int x=0; x<elenco.size(); x++)
					if(elenco[x].getNome() == diretor->getNome()){
						flag = 1;
						break;
					}
				if(flag==0)
					diretor->addMidia(*(m.find(codigo)->second));

				break;
			case 'S': 
				m.insert(pair<int,Midia*>(codigo,new Serie(codigo,nome,tamanho,lGenero.find(gen)->second,possui,consumiu,deseja,preco,elenco,temporada,serie)));
				relationPessoaMidia(elenco,*(m.find(codigo)->second),lPessoas);
				lGenero.find(gen)->second.addMidiaGen(*(m.find(codigo)->second));				

				break;
		}
		elenco.clear();		
		partes.clear();
	}	
	inFile.close();
	}
	else{
		cout<<"Erro de I/O"<<endl;
	}

	return m;

}

//bool isNum(string str){
	
	//for(unsigned int i=0; i<str.length()

/**
 * [readEmprestimo description]
 * @param  file [description]
 * @param  m    [description]
 * @return      [description]
 */
map<int,Emprestimo> static readEmprestimo(char *file, map<int,Midia*> m)
{
	time_t t = 0;
	time_t f = 0;
	map<int,Emprestimo> e;
	ifstream inFile;//(file);
	inFile.open(file);
	if(inFile){
	string line;
	vector<string> partes;
	vector<string>data;
	struct tm dateEmp, dateDev;
	string nome;
	getline(inFile,line);
	time(&t);
	while(!inFile.eof())
	{
		getline(inFile,line);
		if(line.length() < 1) break;
		StringSplit(line,";",partes);
		int codigo = atoi(partes[0].c_str());
		try{
			m.find(codigo);
		}
		catch(exception& f){
			cout<<"Dados inconsistentes (Midia: "<<codigo<<")"<<endl;
			return e;
		}
		nome = partes[1];
		StringSplit(partes[2],"/",data);
		if(*(partes[3].end()-1)>126||*(partes[3].end()-1)<33) partes[3].pop_back();
		//if(!isdigit(data[0]) || !isdigit(data[1]) || !isdigit(data[0]))
			//cout<<"Erro de formatação"<<endl;
		dateEmp = *localtime(&t);
		dateEmp.tm_sec = 0; dateEmp.tm_min = 0; dateEmp.tm_hour = 0;
		//if(!isdigit(data[0]) || !isdigit(data[1]) || !isdigit(data[0]))
			//cout<<"Erro de formatação"<<endl;
		dateEmp.tm_year = atoi(data[2].c_str());
		dateEmp.tm_mon = atoi(data[1].c_str());
		dateEmp.tm_mday = atoi(data[0].c_str());
		data.clear();
		StringSplit(partes[3],"/",data);
		dateDev = *localtime(&f);
		dateDev.tm_sec = 0; dateDev.tm_min = 0; dateDev.tm_hour = 0;
		dateDev.tm_year = atoi(data[2].c_str());
		dateDev.tm_mon = atoi(data[1].c_str());
		dateDev.tm_mday = atoi(data[0].c_str());
		data.clear();
		mktime(&dateEmp);
		mktime(&dateDev);
		e.insert(pair<int,Emprestimo>(codigo,Emprestimo(codigo,nome,dateEmp,dateDev)));
		partes.clear();
	}
	inFile.close();
	}
	else{
		cout<<"Erro de I/O"<<endl;
	}
	return e;
}

/** [mapToVectorMidia description] */
vector<Midia> static mapToVectorMidia(map<int,Midia*>m,vector<Midia>& l)
{
	for (map<int,Midia*>::iterator it=m.begin(); it!=m.end(); ++it)
		l.push_back(*(it->second));
	
	return l;
}

/** [freeMidia Liberando MAP de midias alocado] */
void static freeMidia(map<int,Midia*>m)
{
	for (map<int,Midia*>::iterator it=m.begin(); it!=m.end(); ++it)
		delete (it->second);	
}


/** [compareToMidia ORDENANDO AS MIDIAS] */
bool static compareToMidia( Midia& s1, Midia& s2)
{
   locale::global(locale("pt_BR.UTF-8"));
   const collate<char>& col = use_facet<collate<char> >(locale()); // Use the global locale
   const char* pb1; 
   const char* pb2;

   if(s1.getType() != s2.getType())
   		return ( s1.getType() < s2.getType());
   else	
   	if(s1.getPreco() != s2.getPreco())
   	{
		return (s1.getPreco() > s2.getPreco());
   }else
   {
   		pb1 = s1.getNome().data();
   		pb2 = s2.getNome().data();
		return (col.compare(pb1, pb1 + s1.getNome().size(),pb2, pb2 + s2.getNome().size()) < 0);
   	}

}

/**
 * [generatorWishList description]
 * @param  m [description]
 * @return   [description]
 */
void static generatorWishList(map<int,Midia*> m)
{
	/*TEM QUE APRENDER A DAR FREE NO LOCALE*/
	locale::global(locale("pt_BR.UTF-8"));
	ofstream outFile;//("4-wishlist.csv");
	if(outFile){
	outFile.open("4-wishlist.csv");
	vector<Midia> lMidias;
	outFile << "Tipo;Mídia;Gênero;Preço" << endl;
	mapToVectorMidia(m,lMidias);
	sort(lMidias.begin(),lMidias.end(),compareToMidia);

	/* TEMOS QUE ORDENAR O VETOR DA FORMA QUE O PROFESSOR QUER !!! */
	for(unsigned int i = 0; i < lMidias.size(); i++)
	{
		if(lMidias[i].isDeseja() && !lMidias[i].isPossui())
		{
			switch(lMidias[i].getType())
	         {     
	            case 'L': outFile  << "Livro;" << lMidias[i].getNome() <<";"<< lMidias[i].getGenero().getNome()<<";R$ " << setiosflags (ios::fixed)<< setprecision(2) <<lMidias[i].getPreco()<< endl;
	               break;
	            case 'F': outFile  << "Filme;" << lMidias[i].getNome() <<";"<< lMidias[i].getGenero().getNome()<<";R$ " << setiosflags (ios::fixed)<< setprecision(2) <<lMidias[i].getPreco() << endl;
	               break;
	            case 'S': outFile  << "Série;" << lMidias[i].getNome() <<";"<< lMidias[i].getGenero().getNome()<<";R$ " << setiosflags (ios::fixed)<< setprecision(2) <<lMidias[i].getPreco() << endl;
	               break;
	            
	         }
		}
	}
	lMidias.clear();
	outFile.close();
	}
	else{
		cout<<"Erro de I/O"<<endl;
		return;
	}
}

/** [mapToVectorEmprestimo description] */
vector<Emprestimo> static mapToVectorEmprestimo(map<int,Emprestimo>p,vector<Emprestimo>& l)
{
	for (map<int,Emprestimo>::iterator it=p.begin(); it!=p.end(); ++it)
		l.push_back(it->second);
	
	return l;
}

/** [compareToEmprestimo description] */
bool static compareToEmprestimo(Emprestimo& s1,Emprestimo& s2)
{
   const struct tm pb1 = s1.getEmprestimo(); 
   const struct tm pb2 = s2.getEmprestimo();
   
   if(pb1.tm_year != pb2.tm_year)
	return pb1.tm_year > pb2.tm_year;
   else if(pb1.tm_mon != pb2.tm_mon)
    return pb1.tm_mon > pb2.tm_mon;
   else
    return pb1.tm_mday > pb2.tm_mday;   
}

/**
 * [generatorEmprestimos description]
 * @param  e [description]
 * @return   [description]
 */
void static generatorEmprestimos(map<int,Emprestimo> e){
	
	ofstream outFile;//("3-emprestimos.csv");
	outFile.open("3-emprestimos.csv");
	if(outFile){
	outFile<<"Data;Tomador;Atrasado?;Dias de Atraso"<<endl;
	vector<Emprestimo> emps;
	mapToVectorEmprestimo(e, emps);
	time_t tempo = 0;
	struct tm hj, a;
	int dif;
	
	hj = *localtime(&tempo);
	hj.tm_hour = 0; hj.tm_min = 0; hj.tm_sec = 0; hj.tm_mday = 7; hj.tm_mon = 11; hj.tm_year = 2015;
	
	sort(emps.begin(),emps.end(),compareToEmprestimo);
	for (unsigned int i=0; i<emps.size(); i++){
		
		outFile<<setfill('0')<<setw(2)<<emps[i].getEmprestimo().tm_mday<<"/"<<setfill('0')<<setw(2)<<(emps[i].getEmprestimo().tm_mon == 0 ? 12 : emps[i].getEmprestimo().tm_mon)<<"/"<<emps[i].getEmprestimo().tm_year/1000<<setw(3)<<(emps[i].getEmprestimo().tm_mon == 0 ? emps[i].getEmprestimo().tm_year%1000 - 1 : emps[i].getEmprestimo().tm_year%1000)<<";"<<emps[i].getTomador()<<";";
		
		a = emps[i].getDevolucao();
		dif = difftime(mktime(&hj),mktime(&a));
		
		if(dif>0)
			outFile<<"Sim;"<<dif/86400<<endl;
		else
			outFile<<"Não;0"<<endl;
		
	}
	outFile.close();
	}
	else{
		cout<<"Erro de I/O"<<endl;
		return;
	}
	
}

/** [mapToVectorPessoa description] */
vector<Pessoa> static mapToVectorPessoa(map<int,Pessoa>p,vector<Pessoa>& l)
{
	for (map<int,Pessoa>::iterator it=p.begin(); it!=p.end(); ++it)
		l.push_back(it->second);
	
	return l;
}

/** [compareToPessoa description] */
bool static compareToPessoa(Pessoa& s1,Pessoa& s2)
{
   locale::global(locale("pt_BR.UTF-8"));
   const collate<char>& col = use_facet<collate<char> >(locale()); // Use the global locale
   const char* pb1 = s1.getNome().data(); 
   const char* pb2 = s2.getNome().data();
   
   return (col.compare(pb1, pb1 + s1.getNome().size(),pb2, pb2 + s2.getNome().size()) < 0);
}

/** [compareToTrab description] */
bool static compareToTrab( Midia& s1, Midia& s2)
{
   locale::global(locale("pt_BR.UTF-8"));
   const collate<char>& col = use_facet<collate<char> >(locale()); // Use the global locale
   const char* pb1 = s1.getNome().data(); 
   const char* pb2 = s2.getNome().data();
   
   return (col.compare(pb1, pb1 + s1.getNome().size(),pb2, pb2 + s2.getNome().size()) < 0);
}

/**
 * [generatorPorPessoa description]
 * @param  p [description]
 * @return   [description]
 */
void static generatorPorPessoa(map<int,Pessoa> p){
	
	ofstream outFile;//("2-porpessoa.csv");
	outFile.open("2-porpessoa.csv");
	if(outFile){
	outFile<<"Pessoa;Produção"<<endl;
	vector<Pessoa> lPessoas;
	unsigned int j;

	mapToVectorPessoa(p,lPessoas);
	sort(lPessoas.begin(),lPessoas.end(),compareToPessoa);
	
	for(unsigned i = 0; i < lPessoas.size();i++)
	{
		if(lPessoas[i].getTrabalhos().size() > 0)
		{
			outFile << lPessoas[i].getNome() <<";";
			sort(lPessoas[i].getTrabalhos().begin(),lPessoas[i].getTrabalhos().end(),compareToTrab);
			//cout<<lPessoas[i].getNome()<<endl;
			//if(lPessoas[i].getTrabalhos().size()>1)
			//	sort(lPessoas[i].getTrabalhos().begin(),lPessoas[i].getTrabalhos().end(),compareToTrab);
			//cout<<"ok"<<endl;
			for(j = 0; j < lPessoas[i].getTrabalhos().size()-1; j++)
			{
				outFile << (lPessoas[i].getTrabalhos())[j].getNome() << ", ";
			}
			outFile << lPessoas[i].getTrabalhos()[j].getNome() << endl;
		}		
	}
	outFile.close();
	}
	else{
		cout<<"Erro de I/O"<<endl;
		return;
	}
	
}

/** [mapToVectorGenero description] */
vector<Genero> static mapToVectorGenero(map<string,Genero>g,vector<Genero>& l)
{
	for (map<string,Genero>::iterator it=g.begin(); it!=g.end(); ++it)
		l.push_back(it->second);
	
	return l;
}

/** [compareToGenero description] */
bool static compareToGenero( Genero& s1, Genero& s2)
{
   locale::global(locale("pt_BR.UTF-8"));
   const collate<char>& col = use_facet<collate<char> >(locale()); // Use the global locale
   const char* pb1; 
   const char* pb2;

   if(s1.qtdGenero() != s2.qtdGenero())
   		return ( s1.qtdGenero() > s2.qtdGenero());
   else
   {
   		pb1 = s1.getNome().data();
   		pb2 = s2.getNome().data();
		return (col.compare(pb1, pb1 + s1.getNome().size(),pb2, pb2 + s2.getNome().size()) < 0);
   	}

}

/** [compareToSerie description] */
bool static compareToSerie( Serie& s1, Serie& s2)
{
   locale::global(locale("pt_BR.UTF-8"));
   const collate<char>& col = use_facet<collate<char> >(locale()); // Use the global locale
   const char* pb1 = s1.getNome().data(); 
   const char* pb2 = s2.getNome().data();
   
   return (col.compare(pb1, pb1 + s1.getNome().size(),pb2, pb2 + s2.getNome().size()) < 0);
}

/**
 * [generatorEstatisticas description]
 * @param  p [description]
 * @param  m [description]
 * @param  g [description]
 * @return   [description]
 */
void static generatorEstatisticas(map<int,Pessoa> p, map<int,Midia*> &m, map<string,Genero> g){
	
	locale::global(locale("C"));
	ofstream outFile;//("1-estatisticas.txt");
	outFile.open("1-estatisticas.txt");
	if(outFile){
	vector<Midia> lMidias;
	vector<Serie*> lSeries;
	set<string> nomeSeries;
	vector<Genero> lGenero;
	int horasConsumidas = 0,horasConsumir = 0;
	mapToVectorGenero(g,lGenero);
	for (map<int,Midia*>::iterator it=m.begin(); it!=m.end(); ++it)
	{
		if(it->second->getType() != 'L')
		{
			if(it->second->isConsumiu())
				horasConsumidas += it->second->getTamanho(); 
			if(it->second->isDeseja())
				horasConsumir += it->second->getTamanho();
			if(it->second->getType() == 'S')
			{	
			  lSeries.push_back((Serie*)it->second);
			  nomeSeries.insert(((Serie*)it->second)->getNomeSerie());  			
			}
		}
	}	
	
	outFile<<"Horas consumidas: " << horasConsumidas << " minutos" << endl;	
	outFile<<"Horas a consumir: " << horasConsumir << " minutos" << endl;	
	outFile<<"\nMídias por gênero:"<<endl;

	sort(lGenero.begin(),lGenero.end(),compareToGenero);
	for(unsigned int k = 0; k < lGenero.size();k++)
		outFile << "\t" << lGenero[k].getNome() << ": " << lGenero[k].getMidiaGen().size() << endl;
			
	outFile<<"\nTemporadas por série:"<<endl;
	for(set<string>::iterator it=nomeSeries.begin(); it!=nomeSeries.end(); ++it)
	{  
		int assistida = 0, assistir = 0;	
		for(unsigned int k = 0; k < lSeries.size(); k++)
		{
			if(!(*it).compare(lSeries[k]->getNomeSerie()))
			{
				if(lSeries[k]->isDeseja())
					assistir++;
				if(lSeries[k]->isConsumiu())
					assistida++;
			}	
		}
		outFile << "\t" << *it <<": "<< assistida << " assistidas, " << assistir << " a assistir" <<endl;
	}
	outFile.close();
	}
	else{
		cout<<"Erro de I/O"<<endl;
		return;
	}
	
}
