import java.io.Serializable;
import java.text.Collator;
import java.util.HashSet;
import java.util.Locale;
import java.util.Set;


@SuppressWarnings("serial")
public class Genero implements Serializable, Comparable<Genero> {

	private String sigla;
	private String nome;
	private Set<Midia> midiasGenero = null;
	
	
	/**
	 * Construtor de Genero
	 * @param sigla sigla do genero
	 * @param nome nome do genero
	 */
	public Genero(String sigla, String nome) {
		this.sigla = sigla;
		this.nome = nome;
		midiasGenero = new HashSet<>();//ArrayList<>();
	}

	/**
	 * Pega sigla do genero
	 * @return sigla do genero
	 */
	public String getSigla() {
		return sigla;
	}

	/**
	 * Pega nome do genero
	 * @return nome do genero
	 */
	public String getNome() {
		return nome;
	}
	
	/**
	 * Adiciona midia com genero correspondente
	 * @param m midia a ser adicionada
	 */
	public void addMidiaGen(Midia m)
	{
		midiasGenero.add(m);
	}
	
	/**
	 * Retorna quantidade de generos
	 * @return quantidade de generos
	 */
	public int qtdGenero()
	{
		return midiasGenero.size();
	}

	@Override
	public int compareTo(Genero o) {
		Locale br = new Locale("pt","BR");
		Collator collator = Collator.getInstance(br);
		// TODO Auto-generated method stub
		if(this.midiasGenero.size() > o.midiasGenero.size())
		{
			return -1;
		}else if(this.midiasGenero.size() < o.midiasGenero.size())
		{
			return 1;
		}else {
			return collator.compare(this.getNome(), o.getNome());//this.getNome().compareToIgnoreCase(o.getNome());
		}
	}
	
}
