#!/usr/bin/env python
# -'- coding: utf-8 -'-

from Catalogo import Catalogo
from Livro import Livro

class IO:

	#FUNÇÃO QUE LER TODOS OS ELEMENTOS DE UM LIVRO
	@staticmethod
	def __readBook(f,catalogo):
		cod = int(f.readline())	
		tittle = f.readline().rstrip("\n") #RSTRIP REMOVE O /n no final da linha
		author = f.readline().rstrip("\n")
		subject = f.readline().rstrip("\n")
		date = f.readline().rstrip("\n")
		editora = f.readline().rstrip("\n")
		abstract = f.readline()
		line = f.readline()
		while(line != '\n' and line != ""):
			abstract += line
		 	line = f.readline()
		abstract = abstract.rstrip("\n")
		if(not catalogo.verificaLivro(cod)):
			catalogo.addLivro(cod,tittle,author,subject,date,editora,abstract)
		return line
		# print( tittle +"\n"+ author+ "\n" + subject+ "\n" + date+"\n" + editora+"\n" + abstract+"\n")						

	#FUNÇÃO QUE LER TODOS OS LIVROS DO CATÁLOGO
	@staticmethod 
	def readCatalogo(fileName,catalogo):
		f = open(fileName,"r")
		line = 0
		while(line != ""):
			line = IO.__readBook(f,catalogo)
		f.close()

	#FUNÇÃO QUE LER O ARQUIVO ATUAL.TXT
	@staticmethod
	def readUpdate(fileName,catalogo):
		f = open(fileName,"r")
		line = 0
		while(line != ""):
			typeUpd = f.readline().rstrip("\n")
			if(typeUpd == "i"): #CASO A OPÇÃO SEJA I, LER UM LIVRO
				line = IO.__readBook(f,catalogo)
			elif(typeUpd == "a"):	#CASO A OPÇÃO SEJA A, REMOVE O LIVRO COM AQUELE CÓDIGO, E CRIA UM NOVO COM OS DADOS NOVOS
				pos = f.tell() # PEGA A POSIÇÃO ATUAL DO PONTEIRO FILE
				cod = int(f.readline())
				if(catalogo.verificaLivro(cod)):
					catalogo.removeLivro(cod)
					f.seek(pos) # RETORNA O PONTEIRO PARA A POSIÇÃO INICIAL ANTES DE PULAR PARA A PRÓXIMA LINHA
					line = IO.__readBook(f,catalogo)
			elif(typeUpd == "e"): #CASO A OPÇÃO SEJA E, REMOVE O LIVRO
				cod = int(f.readline())
				catalogo.removeLivro(cod)

				line = f.readline()
			else: 
					print "WARNING: OPTION OF UPDATE NOT FOUND"	
					line = f.readline()				
		f.close()
	
	#FUNÇÃO QUE ESCREVE O LIVROS DE UM CATÁLOGO EM UM ARQUIVO
	@staticmethod
	def __writeDocument(f,livros):		
		#PERCORRENTO LISTA DE LIVROS ATÉ O PENULTIMO ELEMENTO
		for i in livros[:-1]:
			f.write(str(i.getCod())+"\n"+i.getTitulo()+"\n"+i.getAutor()+"\n"+i.getAssunto()+"\n"+i.getDataPTBR()+"\n"+i.getEditora()+"\n"+i.getResumo()+"\n\n")
		f.write(str(livros[-1].getCod())+"\n"+livros[-1].getTitulo()+"\n"+livros[-1].getAutor()+"\n"+livros[-1].getAssunto()+"\n"+livros[-1].getDataPTBR()+"\n"+livros[-1].getEditora()+"\n"+livros[-1].getResumo())
		#for i in range(0,tam):
		#	f.write(str(livros[i].getCod())+"\n"+livros[i].getTitulo()+"\n"+livros[i].getAutor()+"\n"+livros[i].getAssunto()+"\n"+livros[i].getDataPTBR()+"\n"+livros[i].getEditora()+"\n"+livros[i].getResumo()+"\n\n")
		#f.write(str(livros[-1].getCod())+"\n"+livros[-1].getTitulo()+"\n"+livros[-1].getAutor()+"\n"+livros[-1].getAssunto()+"\n"+livros[-1].getDataPTBR()+"\n"+livros[-1].getEditora()+"\n"+livros[-1].getResumo())


	#FUNÇÃO QUE GERA O SAIDA.TXT COM ORDENS ESPECIFICAS
	@staticmethod
	def writeOutput(catalogo):
		f = open("saida.txt","w")
		# tam = len(catalogo.getCatalogo())-1

		f.write("Lista de Livros Ordenada Crescentemente por Codigo:\n\n")
		livros = catalogo.ordenaLista(Livro.cmpCod) #ORDENANDO CATALOGO PELO CRITÉRIO CÓDIGO
		IO.__writeDocument(f,livros)

		f.write("\n\nLista de Livros Ordenada Decrescentemente por Titulo:\n\n")
		livros = catalogo.ordenaLista(Livro.cmpTittle) #ORDENANDO CATALOGO PELO CRITERIO TITULO
		IO.__writeDocument(f,livros)

		f.write("\n\nLista de Livros Ordenada Crescentemente por Autor:\n\n")
		livros = catalogo.ordenaLista(Livro.cmpAuthor) #ORDENANDO CATALOGO PELO CRITERIO AUTOR
		IO.__writeDocument(f,livros)
		
		f.write("\n\nLista de Livros Ordenada Decrescentemente por Data de Publicacao:\n\n")
		livros = catalogo.ordenaLista(Livro.cmpDate)	#ORDENANDO CATALOGO PELO CRITERIO DATA
		IO.__writeDocument(f,livros)

		f.close()

	#FUNÇÃO QUE RESCREVE O ARQUIVO CATÁLOGO ATUALIZADO EM CATALOGO.TXT
	@staticmethod
	def writeCatalogo(fileName,catalogo):
		f = open(fileName,"w")
		livros = catalogo.getCatalogo()
		# tam = len(livros)-1
		IO.__writeDocument(f,livros)
		f.close()
