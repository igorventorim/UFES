-- CLASSE CATÁLOGO
-- CLASSE RESPONSÁVEL POR CONTROLAR TODAS AS FUNÇÕES E ATRIBUTOS DE CATÁLOGO
-- @AUTHOR IGOR VENTORIM
-- DATE BEGIN: 04/30/2016

dofile("Livro.lua")

local catalogoMethods = 
{
	-- # FUNÇÃO QUE ADICIONA UM LIVRO AO CATÁLOGO
	addLivro = function(self,cod,titulo,autor,assunto,data,editora,resumo)
		local livro = Livro(cod,titulo,autor,assunto,data,editora,resumo)
		self.livros[tonumber(cod)] = livro
	end,

	-- #FUNÇÃO QUE VERIFICA SE UM LIVRO JÁ PERTENCE AO CATÁLOGO
	isElementTable = function(self,cod)
		if(self.livros[cod]) then
			return 1
		else
			return 0
		end
	end,

	-- # FUNÇÃO QUE REMOVE UM LIVRO DA LISTA
	removeLivro = function(self,cod)
		self.livros[cod] = nil
	end,

	-- #FUNÇÃO QUE RETORNA O CATÁLOGO ATUAL
	getCatalogo = function(self)
		aux = {}
		count = 0
		for k, v in pairs(self.livros) do
			aux[count] = v
			count = count + 1
		end
		return aux
	end,

	-- # FUNÇÃO AUXILIAR PARA PRINTAR O CÓDIGO DE TODOS OS ITENS DO CATÁLOGO
	printCatalogo = function(self)
		for k, v in pairs(self.livros) do
			v:Print()
		end
	end,

	-- # FUNÇÃO QUE INFORMA O TAMANHO DO CATALOGO
	sizeCatalogo = function(self)
		count = 0
		for k, v in pairs(self.livros) do
			count = count + 1
		end
		return count
	end,

	-- #FUNÇÃO QUE ORDENA A LISTA CONFORME A FUNÇÃO DE ORDENAÇÃO DESEJADA
	ordenaCatalogo = function(self,cmpFunc)
		aux = self:getCatalogo()
		for j=1,#aux do
			chave = aux[j]
			i = j - 1
			while (i >= 0) and cmpFunc(aux[i],chave) == 1 do
				aux[i+1] = aux[i]
				i = i - 1
			end 
			aux[i+1] = chave
		end
		return aux	
	end
}


local catalogoMetatable =
{
	__index = catalogoMethods
}

-- #MÉTODO CONSTRUTOR DE CATÁLOGO
Catalogo = function()
	self = {}
	self.livros = {}
	setmetatable(self,catalogoMetatable)
	return self
end
