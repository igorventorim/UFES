#!/usr/bin/env python
# -'- coding: utf-8 -'-
from datetime import date

class Livro:
	
	#MÉTODO CONSTRUTOR DE LIVRO
	def __init__(self,cod,titulo,autor,assunto,data,editora,resumo):
		partes = data.split("/") # Transforma a string data d/m/Y em uma lista [d,m,Y]
		self.__cod = cod
		self.__titulo = titulo
		self.__autor = autor
		self.__assunto = assunto
		self.__data = date(int(partes[2]),int(partes[1]),int(partes[0])) #Criando o objeto tipo date
		self.__editora = editora
		self.__resumo = resumo

	#MÉTODO QUE RETORNAR O VALOR DE CÓDIGO
	def getCod(self):
		return self.__cod

	#MÉTODO QUE RETORNA O VALOR DE TÍTULO
	def getTitulo(self):
		return self.__titulo

	#MÉTODO QUE RETORNA O VALOR DE AUTOR
	def getAutor(self):
		return self.__autor

	#MÉTODO QUE RETORNA O VALOR DE ASSUNTO
	def getAssunto(self):
		return self.__assunto

	#MÉTODO QUE RETORNA A DATA EM PADRÃO PT-BR
	def getDataPTBR(self):
		return self.__data.strftime("%d/%m/%Y")

	#MÉTODO QUE RETORNA A DATA EM TIPO DATE
	def getData(self):
		return self.__data

	#MÉTODO QUE RETORNA O VALOR DE EDITORA
	def getEditora(self):
		return self.__editora

	#MÉTODO QUE RETORNA O VALOR DE RESUMO
	def getResumo(self):
		return self.__resumo

	#MÉTODO QUE SETA UM NOVO TÍTULO A UM LIVRO
	def setTitulo(self,newTitle):
		self.__titulo = newTitle

	#MÉTODO QUE SETA UM NOVO ASSUNTO A UM LIVRO
	def setAssunto(self,newSubject):
		self.__assunto = newSubject

	#MÉTODO QUE SETA UMA NOVA DATA
	def setData(self,date):
		partes = date.split("/")
		self.__data = date(int(partes[2]),int(partes[1]),int(partes[0]))

	#MÉTODO QUE SETA UMA NOVA EDITORAR AO LIVRO
	def setEditora(self,editora):
		self.__editora = editora

	#MÉTODO QUE SETA UM NOVO AUTOR AO LIVRO
	def setAutor(self,autor):
		self.__autor = autor	

	#MÉTODO QUE SETA UM NOVO RESUMO
	def setResumo(self,resumo):
		self.__resumo = resumo

	#MÉTODO PARA CONFERIR A ORDEM DOS LIVROS POR CÓDIGO
	@staticmethod
	def cmpCod(livro1,livro2):
		if(livro1.getCod() > livro2.getCod()):
			return 1
		else:	return 0

	#MÉTODO PARA CONFERIR A ORDEM DOS LIVROS POR TÍTULO
	@staticmethod	
	def cmpTittle(livro1,livro2):
		if(livro1.getTitulo() > livro2.getTitulo()):
			return 0
		elif(livro1.getTitulo() == livro2.getTitulo()):
			return not Livro.cmpCod(livro1,livro2)
		else:	return 1

	#MÉTODO PARA CONFERIR A ORDEM DOS LIVROS POR AUTOR
	@staticmethod	
	def cmpAuthor(livro1,livro2):
		if(livro1.getAutor() > livro2.getAutor()):
			return 1
		elif(livro1.getAutor() == livro2.getAutor()):
			return Livro.cmpCod(livro1,livro2)
		else: return 0

	#MÉTODO PARA CONFERIR A ORDEM DOS LIVROS POR DATA
	@staticmethod	
	def cmpDate(livro1,livro2):
		if(livro1.getData().toordinal() > livro2.getData().toordinal()):
			return 0
		elif(livro1.getData().toordinal() == livro2.getData().toordinal()):
			return not Livro.cmpCod(livro1,livro2)
		else: return 1		
