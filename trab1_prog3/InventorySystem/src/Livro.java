import java.util.List;

@SuppressWarnings("serial")
public class Livro extends Midia {
	
	private List<Pessoa> autores;

	/**
	 * Construtor de Livro
	 * @param codigo codigo do livro
	 * @param nome nome do livro
	 * @param tamanho quantidade de paginas do livro
	 * @param genero genero do livro
	 * @param possui true se possui este livro ou false caso contrario
	 * @param consumiu true se consumiu este livro ou false caso contrario
	 * @param deseja true se deseja este livro ou false caso contrario
	 * @param preco preco do livro
	 * @param autores lista de autores do livro
	 */
	public Livro(int codigo, String nome, int tamanho, Genero genero,
			boolean possui, boolean consumiu, boolean deseja, double preco,
			List<Pessoa> autores) {
		super(codigo, nome, tamanho, genero, possui, consumiu, deseja, preco, 'L');
		this.autores = autores;

	}

	/**
	 * Pega autores do livro
	 * @return lista de autores do livros
	 */
	public List<Pessoa> getAutores() {
		return autores;
	}
	
}
