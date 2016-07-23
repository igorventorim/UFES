-- CLASSE LIVRO
-- CLASSE RESPONSÁVEL POR CONTROLAR TODAS AS FUNÇÕES DE UM LIVRO
-- @AUTHOR IGOR VENTORIM
-- DATE BEGIN: 04/30/2016

local bookMethods = {
  
  -- MÉTODO QUE RETORNAR O VALOR DE CÓDIGO
  getCod = function(self)
      return self.cod
  end,

  setCod = function (self,cod)
    self.cod = cod
  end,

  -- #MÉTODO QUE RETORNA O VALOR DE TÍTULO
  getTitulo = function(self)
      return self.titulo
  end,

  -- #MÉTODO QUE SETA UM NOVO TÍTULO A UM LIVRO
  setTitulo = function(self,titulo)
      self.titulo = titulo
  end,

  --#MÉTODO QUE RETORNA O VALOR DE AUTOR
  getAutor = function(self)
      return self.autor
  end,
  -- #MÉTODO QUE SETA UM NOVO AUTOR AO LIVRO
  setAutor = function(self,autor)
      self.autor = autor
  end,

  -- #MÉTODO QUE RETORNA O VALOR DE ASSUNTO
  getAssunto = function(self)
      return self.assunto
  end,

  -- #MÉTODO QUE SETA UM NOVO ASSUNTO A UM LIVRO
  setAssunto = function(self,assunto)
      self.assunto = assunto
  end,

  -- #MÉTODO QUE RETORNA A DATA EM TIPO TIME
  getData = function(self)
      return self.data
  end,

  -- #MÉTODO QUE RETORNA A DATA EM PADRÃO PT-BR TIPO STRING
  getStringData = function(self)
      return os.date("%d/%m/%Y",self.data)
  end,

  -- #MÉTODO QUE SETA UMA NOVA DATA
  setData = function(self,data)
      t = {}
      i = 0
      for word in (data.."/"):gmatch("([^/]*)/") do
        t[i] = word
        i = i+1
      end  
      self.data = os.time{year = t[2] ,month = t[1] ,day = t[0]}
  end,

  -- #MÉTODO QUE RETORNA O VALOR DE EDITORA
  getEditora = function(self)
      return self.editora
  end,

  -- #MÉTODO QUE SETA UMA NOVA EDITORAR AO LIVRO
  setEditora = function(self,editora)
      self.editora = editora
  end,

  -- #MÉTODO QUE RETORNA O VALOR DE RESUMO
  getResumo = function(self)
      return self.resumo
  end,

  -- #MÉTODO QUE SETA UM NOVO RESUMO
  setResumo = function(self,resumo)
      self.resumo = resumo
  end,

  -- MÉTODO QUE IMPRIME UM LIVRO
  Print = function(self)
    print(self.cod .." : ".. self.titulo .. " : ".. self.autor .. " : ".. self.assunto .." : "..  self:getStringData().. ":" ..self.editora  .." : " .. self.resumo)
  end
}

local bookMetatable =
{
  __index = bookMethods
}

splitData = function (data)
  t = {}
  i = 0
  for word in (data.."/"):gmatch("([^/]*)/") do
    t[i] = word
    i = i+1
  end
  return t  
end

--Construtor
Livro = function (cod,titulo,autor,assunto,data,editora,resumo)  
  self = {}
  self.cod = cod or 0.0
  self.titulo = titulo or ""
  self.autor = autor or ""
  self.assunto = assunto or ""
  local t = splitData(data)
  self.data = os.time{year = t[2] ,month = t[1] ,day = t[0]}
  self.editora = editora or ""
  self.resumo = resumo or ""
  setmetatable(self,bookMetatable)
  return self
end


-- #MÉTODO PARA COMPARAR LIVROS POR CÓDIGO
cmpCod = function(livro1,livro2)
  if(livro1:getCod() > livro2:getCod()) then
    return 1
  else
    return 0
  end
end

-- #MÉTODO PARA COMPARAR LIVROS POR TÍTULO
cmpTitulo = function(livro1,livro2)
  if(livro1:getTitulo() > livro2:getTitulo()) then
    return 0
  elseif(livro1:getTitulo() == livro2:getTitulo()) then
      x = cmpCod(livro1,livro2)
      if(x == 1) then
        return 0
      else
        return 1
      end   
  else
      return 1
  end
end

-- #MÉTODO PARA COMPARAR LIVROS POR AUTOR
cmpAutor = function(livro1,livro2)
  if(livro1:getAutor() > livro2:getAutor()) then
    return 1
  elseif(livro1:getAutor() == livro2:getAutor()) then
    return cmpCod(livro1,livro2)
  else
    return 0
  end
end

-- #MÉTODO PARA COMPARAR LIVROS POR DATA
cmpDate = function(livro1,livro2)
  if(livro1:getData() > livro2:getData()) then
    return 0
  elseif(livro1:getData() == livro2:getData()) then
    x = cmpCod(livro1,livro2)
      if(x == 1) then
        return 0
      else
        return 1
      end  
  else
    return 1
  end
end
