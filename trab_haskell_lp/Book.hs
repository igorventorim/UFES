-- MÓDULO LIVRO 

module Book
(
Book(..),
Date(..),
showDate,
showBook,
valueDate,
cmpTitle,
cmpAuthor,
cmpCod,
cmpDate
)where

--ESTRUTURA DATA
data Date = Date{
                 dia :: String,
                 mes:: String,
                 ano:: String
                }deriving (Eq,Show,Read)

--ESTRUTURA LIVRO
data Book = Book{
                 cod :: Int,
                 titulo::String,
                 autor::String,
                 assunto::String,
                 datePub::Date,
                 editora::String,
                 resumo::String
                 } deriving (Eq,Show,Read)

-- FUNÇÃO QUE EXIBE A DATA
showDate (Date d m a) = d ++"/"++ m++"/"++ a

-- FUNÇÃO QUE EXIBE UM LIVRO
showBook (Book cod titulo autor assunto (Date d m a) editora resumo) = (show cod ++ "\n"++titulo++"\n"++autor++"\n"++assunto++"\n"++showDate (Date d m a)++"\n"++editora++"\n"++resumo)

-- FUNÇÃO QUE CONVERTE A DATA EM UM INTEIRO
valueDate (Date d m a) = (read (a ++ m ++ d)::Int)

-- FUNÇÃO QUE COMPARA LIVROS POR CÓDIGO
cmpCod b1 b2 = (cod b1) > (cod b2) 

-- FUNÇÃO QUE COMPARA LIVROS POR TITULOS
cmpTitle b1 b2 = if (titulo b1) > (titulo b2) then
                 False 
                 else if (titulo b1) == (titulo b2) then
                 not (cmpCod b1 b2) 
                 else True
-- FUNÇÃO QUE COMPARA LIVROS POR AUTORES
cmpAuthor b1 b2 =if (autor b1) > (autor b2) then
                 True 
                 else if (autor b1) == (autor b2) then
                 (cmpCod b1 b2) 
                 else False

-- FUNÇÃO QUE COMPARA LIVROS POR DATAS
cmpDate b1 b2 = if (valueDate (datePub b1)) > (valueDate (datePub b2)) then
                False 
                else if (valueDate (datePub b1)) == (valueDate (datePub b2)) then
                not (cmpCod b1 b2) 
                else True


