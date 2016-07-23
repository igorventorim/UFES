-- MÓDULO PRINCIPAL
import Catalogo
import Book

-- FUNÇÃO QUE EXECUTA O PROGRAMA E ESCREVE NOS ARQUIVOS
main = do
        teste <- readFile "catalogo.txt"
        let catalogo = (geraCatalogo [] (geraLista ((lines teste)++[""])))
        teste <- readFile "atual.txt"
        let catalogoAtualizado = (updateCatalogo catalogo (geraLista (lines teste++[""]))) 
        print (closeCatalogo catalogoAtualizado)
        writeFile "catalogo.txt" (init (printCatalogo catalogoAtualizado))
        writeFile "saida.txt" (printSaidaTXT catalogoAtualizado)
