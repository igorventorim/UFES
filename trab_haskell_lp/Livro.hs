data Date = Date{
                 dia :: Int,
                 mes:: Int,
                 ano::Int
                }deriving (Eq,Show,Read)
data Book = Book{
                 cod :: Int,
                 titulo::String,
                 autor::String,
                 assunto::String,
                 datePub::Date,
                 editora::String,
                 resumo::String
                 } deriving (Eq,Show,Read)
	
type Cod = Int
type Titulo = String
type Autor = String
type Assunto = String
type Data = (Int,Int,Int)
type Editora = String
type Resumo = String
type Livro = [(Cod,Titulo,Autor,Assunto,Data,Editora,Resumo)]
--tellBook(Book{cod = c,titulo = t,autor=a,})
showDate (Date d m a) = show d ++"/"++show m++"/"++show a
showBook (Book cod titulo autor assunto (Date d m a) editora resumo) = "codigo:" ++ show cod ++ " titulo:"++titulo++" autor:"++autor++" assunto:"++assunto++" data:"++showDate (Date d m a)++" editora:"++editora++" resumo:"++resumo

