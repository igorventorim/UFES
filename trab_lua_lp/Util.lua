-- CLASSE UTIL - UTILITÁRIOS
-- CLASSE RESPONSÁVEL POR CONTROLAR TODAS AS FUNÇÕES UTILITÁRIAS PARA O TRABALHO
-- @AUTHOR IGOR VENTORIM
-- DATE BEGIN: 04/30/2016

-- package.path = package.path .. ";../?.lua"
-- require("Livro.lua")
dofile("Catalogo.lua")

-- #FUNÇÃO QUE LER TODOS OS ELEMENTOS DE UM LIVRO
readBook = function(f,catalogo)
	cod = tonumber(f:read())
	titulo = f:read()
	autor = f:read()
	assunto = f:read()
	data = f:read()
	editora = f:read()
	resumo = f:read().."\n"
	line = f:read()
	while(line ~= nil and string.len(line) ~= 0) do
		resumo = resumo..line.."\n"
		line = f:read()
	end	
	if(catalogo:isElementTable() == 0) then
		catalogo:addLivro(cod,titulo,autor,assunto,data,editora,resumo)
	end	
	return line
end

-- #FUNÇÃO QUE LER TODOS OS LIVROS DO CATÁLOGO
readCatalogo = function(fileName,catalogo)
	file = io.open(fileName,"r")
	line = 0
	while( line ~= nil) do
		line = readBook(file,catalogo)
	end
	file:close()
end

-- #FUNÇÃO QUE LER O ARQUIVO ATUAL.TXT
readUpdate = function(fileName,catalogo)
	file = io.open(fileName,"r")
	line = 0
	while( line ~= nil) do
		typeUpd = file:read()
		-- print(typeUpd)
		if(typeUpd == 'i') then
			line = readBook(file,catalogo)
			elseif(typeUpd == 'a') then
					pos = file:seek()
					cod = tonumber(file:read())
					file:seek("set",pos)
					if(catalogo:isElementTable(cod) == 1) then
						catalogo:removeLivro(cod)
						line = readBook(file,catalogo)
					end
			elseif(typeUpd == 'e') then
				cod = tonumber(file:read())
				catalogo:removeLivro(cod)
				line = file:read()
			else
				print "WARNING: OPTION OF UPDATE NOT FOUND"
			end
	end
	file:close()
end

-- #FUNÇÃO QUE ESCREVE OS LIVROS DE UM CATÁLOGO EM UM ARQUIVO
writeDocument = function(f,catalogo)
	for i = 0, #catalogo-1 do
		f:write(catalogo[i]:getCod().."\n"..catalogo[i]:getTitulo().."\n"..catalogo[i]:getAutor().."\n".. catalogo[i]:getAssunto().."\n"..catalogo[i]:getStringData().."\n"..catalogo[i]:getEditora().."\n"..catalogo[i]:getResumo().."\n")		
	end
		f:write(catalogo[#catalogo]:getCod().."\n"..catalogo[#catalogo]:getTitulo().."\n"..catalogo[#catalogo]:getAutor().."\n".. catalogo[#catalogo]:getAssunto().."\n"..catalogo[#catalogo]:getStringData().."\n"..catalogo[#catalogo]:getEditora().."\n"..catalogo[#catalogo]:getResumo())		

end

-- #FUNÇÃO QUE GERA O SAIDA.TXT COM ORDENS ESPECIFICAS
writeOutput = function(catalogo)
	file = io.open("saida.txt","w")
	file:write("Lista de Livros Ordenada Crescentemente por Codigo:\n\n")
	livros = catalogo:ordenaCatalogo(cmpCod) --#ORDENANDO CATALOGO PELO CRITÉRIO CÓDIGO
	writeDocument(file,livros)

	file:write("\nLista de Livros Ordenada Decrescentemente por Titulo:\n\n")
	livros = catalogo:ordenaCatalogo(cmpTitulo) -- #ORDENANDO CATALOGO PELO CRITERIO TITULO
	writeDocument(file,livros)

	file:write("\nLista de Livros Ordenada Crescentemente por Autor:\n\n")
	livros = catalogo:ordenaCatalogo(cmpAutor) --#ORDENANDO CATALOGO PELO CRITERIO AUTOR
	writeDocument(file,livros)
	
	file:write("\nLista de Livros Ordenada Decrescentemente por Data de Publicacao:\n\n")
	livros = catalogo:ordenaCatalogo(cmpDate)	--#ORDENANDO CATALOGO PELO CRITERIO DATA
	writeDocument(file,livros)

	file:close()
end


-- #FUNÇÃO QUE RESCREVE O ARQUIVO CATÁLOGO ATUALIZADO EM CATALOGO.TXT	
writeCatalogo = function(fileName,catalogo)
	file = io.open(fileName,"w")
	livros = catalogo:getCatalogo()
	writeDocument(file,livros)
	file:close()
end