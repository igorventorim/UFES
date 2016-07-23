import java.io.Serializable;
import java.text.Collator;
import java.util.Locale;



@SuppressWarnings("serial")
public abstract class Midia implements Serializable, Comparable<Midia>{
	
	private int codigo;
	private String nome;
	private char type;
	private int tamanho;
	private Genero genero;
	private boolean possui;
	private boolean consumiu;
	private boolean deseja;
	private double preco;
	
	/**
	 * Construtor de Midia
	 * @param codigo codigo da midia
	 * @param nome nome da midia
	 * @param tamanho tamanho da midia
	 * @param genero genero da midia
	 * @param possui true se possui esta midia ou false caso contrario
	 * @param consumiu true se consumiu esta midia ou false caso contrario
	 * @param deseja true se deseja esta midia ou false caso contrario
	 * @param preco preco da midia
	 * @param type tipo de midia
	 */
	public Midia(int codigo, String nome, int tamanho, Genero genero,
			boolean possui, boolean consumiu, boolean deseja, double preco, char type) {
		//super();
		this.codigo = codigo;
		this.nome = nome;
		this.tamanho = tamanho;
		this.genero = genero;
		this.possui = possui;
		this.consumiu = consumiu;
		this.deseja = deseja;
		this.preco = preco;
		this.type = type;
	}
	
	/**
	 * Construtor de Midia
	 */
	public Midia(){}

	/**
	 * Pega tipo de midia
	 * @return tipo de midia
	 */
	public char getType() {
		return type;
	}

	/**
	 * Altera tipo de midia
	 * @param type tipo de midia
	 */
	public void setType(char type) {
		this.type = type;
	}

	/**
	 * Pega codigo da midia
	 * @return codigo da midia
	 */
	public int getCodigo() {
		return codigo;
	}

	/**
	 * Pega nome da midia
	 * @return nome da midia
	 */
	public String getNome() {
		return nome;
	}

	/**
	 * Pega tamanho da midia
	 * @return tamanho da midia
	 */
	public int getTamanho() {
		return tamanho;
	}

	/**
	 * Pega genero da midia
	 * @return genero da midia
	 */
	public Genero getGenero() {
		return genero;
	}

	/**
	 * Verifica se possui midia
	 * @return true se possui midia ou false caso contrario
	 */
	public boolean isPossui() {
		return possui;
	}

	/**
	 * Verifica se consumiu midia
	 * @return true se consumiu midia ou false caso contrario
	 */
	public boolean isConsumiu() {
		return consumiu;
	}

	/**
	 * Verifica se deseja midia
	 * @return true se deseja midia ou false caso contrario
	 */
	public boolean isDeseja() {
		return deseja;
	}

	/**
	 * Pega preco da midia
	 * @return preco da midia
	 */
	public double getPreco() {
		return preco;
	}

	/**
	 * Altera posse da midia
	 * @param possui true se possui ou false caso contrario
	 */
	public void setPossui(boolean possui) {
		this.possui = possui;
	}

	/**
	 * Altera consumo da midia
	 * @param consumiu true se consumiu ou false contrario
	 */
	public void setConsumiu(boolean consumiu) {
		this.consumiu = consumiu;
	}

	/**
	 * Altera desejo da midia
	 * @param deseja true se deseja ou false caso contrario
	 */
	public void setDeseja(boolean deseja) {
		this.deseja = deseja;
	}

	/**
	 * Altera preco da midia
	 * @param preco preco da midia
	 */
	public void setPreco(double preco) {
		this.preco = preco;
	}
	
	public String toString()
	{
		return "Nome: "+nome+", tipo: "+type+", preço: "+preco+", tamanho: "+tamanho;
	}
	
	/**
	 * Método de critério de ordenação
	 */
	public int compareTo(Midia otherMidia) {
		Locale br = new Locale("pt","BR");
		Collator collator = Collator.getInstance(br);
    if (this.type < otherMidia.type) {
        return -1;
    }
    else if (this.type > otherMidia.type) {
        return 1;
    }else
    {
    	if(this.preco > otherMidia.preco)
    	{
    		return -1;
    	}else if(this.preco < otherMidia.preco)
    		return 1;
    	else
    	{
    		//return this.getNome().compareToIgnoreCase(otherMidia.getNome());
    		return collator.compare(this.getNome(), otherMidia.getNome());
    		
    	}
    }
    
    
	}

	
}
