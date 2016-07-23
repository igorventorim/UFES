import java.io.Serializable;
import java.text.Collator;
import java.util.Locale;
import java.util.Set;
import java.util.TreeSet;


@SuppressWarnings("serial")
public class Pessoa implements Comparable<Pessoa>, Serializable {
	
	private int codigo;
	private String nome;
	private Set<Midia> trabalhos = null;

	/**
	 * Construtor de Pessoa
	 * @param codigo codigo da pessoa
	 * @param nome nome da pessoa
	 */
	public Pessoa(int codigo, String nome) {
		this.codigo = codigo;
		this.nome = nome;
		this.trabalhos = new TreeSet<>();
	}
	
	/**
	 * Construtor de Pessoa
	 */
	public Pessoa(){}

	/**
	 * Pegar codigo de Pessoa
	 * @return codigo da pessoa
	 */
	public int getCodigo() {
		return codigo;
	}

	/**
	 * Pegar nome de Pessoa
	 * @return nome da pessoa
	 */
	public String getNome() {
		return nome;
	}
	
	/**
	 * Adicionar midia a pessoa
	 * @param m midia a ser adicionada
	 */
	public void addMidia(Midia m)
	{
		this.trabalhos.add(m);
	}
	
	/**
	 * Pegar quantidade de midias relacionadas a pessoa
	 * @return quantidade de trabalhos realizados
	 */
	public int qtdTrabalhos()
	{
		return this.trabalhos.size();
	}

	/**
	 * Pega lista de midias feitas pela pessoa
	 * @return conjunto de midias realizadas por pessoa
	 */
	public Set<Midia> getTrabalhos() {
		return trabalhos;
	}
	
	@Override
	public int compareTo(Pessoa o) {
		// TODO Auto-generated method stub
		Locale br = new Locale("pt","BR");
		Collator collator = Collator.getInstance(br);
		try{
			//return this.nome.compareToIgnoreCase(o.nome);
			return collator.compare(this.getNome(), o.getNome());
		}
		catch(Exception ex){
			ex.printStackTrace();
		}
		return 0;
	}

}
