import java.util.List;

@SuppressWarnings("serial")
public class Filme extends Midia {

	private Pessoa diretor;
	private List<Pessoa> atores;
	
	/**
	 * Construtor de Filme
	 * @param codigo codigo do filme
	 * @param nome nome do filme
	 * @param tamanho duracao do filme
	 * @param genero genero do filme
	 * @param possui true se possui este filme ou false caso contrario
	 * @param consumiu true se consumiu este filme ou false caso contrario
	 * @param deseja true se deseja este filme ou false caso contrario
	 * @param preco preco do filme
	 * @param diretor diretor do filme
	 * @param atores lista de atores do filme
	 */
	public Filme(int codigo, String nome, int tamanho, Genero genero,
			boolean possui, boolean consumiu, boolean deseja, double preco,
			Pessoa diretor, List<Pessoa> atores) {
		super(codigo, nome, tamanho, genero, possui, consumiu, deseja, preco,'F');
		this.diretor = diretor;
		this.atores = atores;
	}
	
	/**
	 * Pega diretor
	 * @return diretor do filme
	 */
	public Pessoa getDiretor() {
		return diretor;
	}

	/**
	 * Pega atores
	 * @return lista de atores do filme
	 */
	public List<Pessoa> getAtores() {
		return atores;
	}
	
}
