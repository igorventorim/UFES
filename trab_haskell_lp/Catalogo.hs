-- MÓDULO CATÁLOGO 
module Catalogo
(
    Catalogo(..),
    geraLista,
    geraCatalogo,
    createLivro,
    addBookList,
    splitDate,
    removeBook,
    hasThisBook,
    readUpdate,
    updateCatalogo,
    printCatalogo,
    quicksort,
    printSaidaTXT,
    closeCatalogo
)where

import Book

-- FUNÇÃO QUE TRANSFORMA UMA LISTA DE STRING EM UMA LISTA DE LIVROS
geraLista [] = []
geraLista xs = [(takeWhile (/="") xs)] ++ geraLista (tail (dropWhile (/="") xs))

-- FUNÇÃO QUE DAR UM SPLIT EM UMA STRING PARA O FORMATO DATA
splitDate [] = []
splitDate xs = [part] ++ splitDate (tail (dropWhile (/='/') xs))
                    where part = (takeWhile (/='/') xs)

-- FUNÇÃO QUE ADICIONA UM LIVRO EM UMA LISTA
addBookList xs (Book c t a ass d e r) = xs ++ [Book c t a ass d e r]

-- FUNÇÃO QUE CONSTRÓI UM LIVRO
createLivro xs = Book (read (xs!!0) :: Int) (xs!!1) (xs!!2) (xs!!3) dataPub (xs!!5) (concat [ x++"\n" | x <- ys ])
                  where dataPub = Date (dia) (mes) (ano)
                        [dia,mes,ano] = splitDate ((xs!!4)++"/")
                        ys = drop 6 xs 

-- FUNÇÃO QUE CONSTRÓI UM CATÁLOGO
geraCatalogo l [] = []
geraCatalogo l xss = (addBookList l (createLivro (head xss))) ++ geraCatalogo l (tail xss)

-- FUNÇÃO QUE ATUALIZA O CATÁLOGO APARTIR DO ARQUIVO ATUAL.TXT
updateCatalogo catalogo [] = catalogo
updateCatalogo catalogo xss = (updateCatalogo (readUpdate catalogo (head xss)) (tail xss))

--FUNÇÃO QUE INTERPRETA O ARQUIVO ATUAL.TXT
readUpdate catalogo xs = if (xs!!0) == "i" then
                         if not (hasThisBook((read (xs!!1)::Int),catalogo)) then
                               addBookList catalogo (createLivro (tail xs))
                            else catalogo
                         else if (xs!!0) == "a" then
                            if not (hasThisBook((read (xs!!1)::Int),catalogo)) then
                               addBookList catalogo (createLivro (tail xs))
                            else addBookList (removeBook ((read (xs!!1)::Int),catalogo,catalogo)) (createLivro (tail xs))
                         else if (xs!!0) == "e" then
                               removeBook((read (xs!!1)::Int),catalogo,catalogo)
                         else catalogo

-- FUNÇÃO QUE VERIFICA SE UM LIVRO ESTÁ NA LISTA
hasThisBook (_,[]) = False
hasThisBook (codigo,x:xs) = if codigo == (cod x) then True else hasThisBook(codigo,xs) 

-- FUNÇÃO QUE REMOVE UM LIVRO DA LISTA
removeBook (_,[],catalogo) = catalogo
removeBook (codigo,x:xs,catalogo) = if codigo == (cod x) then takeWhile (/=x) catalogo ++ tail (dropWhile (/=x) catalogo) else removeBook(codigo,xs,catalogo) 

-- FUNÇÃO QUE IMPRIME O CATÁLOGO
printCatalogo [] = ""
printCatalogo (x:xs) = (showBook x)++"\n"++(printCatalogo xs)

-- FUNÇÃO QUE CONSTRÓI OS DADOS A SEREM ESCRITOS EM SAIDA.TXT
printSaidaTXT catalogo = ("Lista de Livros Ordenada Crescentemente por Codigo:\n\n" ++ (printCatalogo (quicksort cmpCod catalogo)) ++ "Lista de Livros Ordenada Decrescentemente por Titulo:\n\n" ++ (printCatalogo (quicksort cmpTitle catalogo)) ++ "Lista de Livros Ordenada Crescentemente por Autor:\n\n" ++ (printCatalogo (quicksort cmpAuthor catalogo)) ++ "Lista de Livros Ordenada Decrescentemente por Data de Publicacao:\n\n" ++ (init (printCatalogo (quicksort cmpDate catalogo))))

-- FUNÇÃO DE ORDENAÇÃO APARTIR DE UMA FUNÇÃO
quicksort func [] = []  
quicksort func (x:xs) =   
    let smallerSorted = quicksort func [a | a <- xs, not (func a x)]  
        biggerSorted = quicksort func [a | a <- xs, (func a x)]  
    in  smallerSorted ++ [x] ++ biggerSorted  

-- FUNÇÃO PARA FINALIZAR O PROGRAMA
closeCatalogo [] = "Programa executado com sucesso!"
closeCatalogo (x:xs) = closeCatalogo xs