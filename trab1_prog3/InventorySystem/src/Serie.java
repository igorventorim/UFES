import java.util.List;
//import java.util.Set;
//import java.util.TreeSet;

@SuppressWarnings("serial")
public class Serie extends Midia {
	
	private List<Pessoa> atores;
	private String temporada;
	private String nameSerie;
//	private static Set<String> series = new TreeSet<>();
		
	/**
	 * Construtor de Serie
	 * @param codigo codigo da serie
	 * @param nome nome da serie
	 * @param tamanho duracao da serie
	 * @param genero genero da serie
	 * @param possui true se possui esta serie ou false caso contrario
	 * @param consumiu true se consumiu esta serie ou false caso contrario
	 * @param deseja true se deseja esta serie ou false caso contrario
	 * @param preco preco da serie
	 * @param atores lista de atores da serie
	 * @param temporada temporada da serie
	 * @param nameSerie nome da serie
	 */
	public Serie(int codigo, String nome, int tamanho, Genero genero,
			boolean possui, boolean consumiu, boolean deseja, double preco,
			List<Pessoa> atores, String temporada, String nameSerie) {
		super(codigo, nome, tamanho, genero, possui, consumiu, deseja, preco, 'S');
		this.atores = atores;
		this.temporada = temporada;
		this.nameSerie = nameSerie;
		//nome = nome2;

	}

	/**
	 * Pega lista de atores da serie
	 * @return lista de atores da serie
	 */
	public List<Pessoa> getAtores() {
		return atores;
	}

	/**
	 * Pega temporada da serie
	 * @return temporada da serie
	 */
	public String getTemporada() {
		return temporada;
	}

	/**
	 * Pega nome da serie
	 * @return nome da serie
	 */
	public String getNomeSerie() {
		return nameSerie;
	}
	
//	/**
//	 * Adiciona nova serie
//	 * @param nameSerie nome da serie
//	 */
//	public void addNewSerie(String nameSerie)
//	{
//		series.add(nameSerie);
//	}
//		
//	/**
//	 * Pega conjunto dos nomes das series
//	 * @return nomes das series
//	 */
//	public static Set<String> getSeries()
//	{
//		return series;
//	}
	



}
