#!/usr/bin/env python
# -'- coding: utf-8 -'-
from Livro import Livro

class Catalogo:

	#MÉTODO CONSTRUTOR DE CATÁLOGO
	def __init__(self):
		self.__livros = []

	# FUNÇÃO QUE ADICIONA UM LIVRO AO CATÁLOGO
	def addLivro(self,cod,titulo,autor,assunto,data,editora,resumo):
		livro = Livro(cod,titulo,autor,assunto,data,editora,resumo)
		self.__livros.append(livro)

	#FUNÇÃO QUE VERIFICA SE UM LIVRO JÁ PERTENCE AO CATÁLOGO
	def verificaLivro(self,code):
		for i in self.__livros:
			if(i.getCod() == code):
				return 1
		return 0

	
	# FUNÇÃO QUE REMOVE UM LIVRO DA LISTA
	# * CODE - Código identificador do livro
	def removeLivro(self,code):
		for i in self.__livros:
			if(i.getCod() == code):
				self.__livros.remove(i)
				return 1
		return 0

	# FUNÇÃO AUXILIAR PARA PRINTAR O CÓDIGO DE TODOS OS ITENS DO CATÁLOGO
	def printCatalogo(self):
		for i in self.__livros:
			print (i.getCod())

	#FUNÇÃO QUE RETORNA O CATÁLOGO ATUAL
	def getCatalogo(self):
		return self.__livros 

	#FUNÇÃO QUE ORDENA A LISTA CONFORME A FUNÇÃO DE ORDENAÇÃO DESEJADA
	def ordenaLista(self,cmpFunc):
	    for j in range(1, len(self.__livros)):
	        chave = self.__livros[j]
	        i = j - 1
	        while i >= 0 and cmpFunc(self.__livros[i],chave):
	            self.__livros[i+1] = self.__livros[i]
	            i -= 1
	        self.__livros[i + 1] = chave
	    return self.__livros