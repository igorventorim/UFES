import java.io.Serializable;
import java.util.Date;

@SuppressWarnings("serial")
public class Emprestimo implements Serializable, Comparable<Emprestimo> {
	
	private Midia midia;
	private String tomador;
	private Date emprestimo;
	private Date devolucao;
	
	/**
	 * Construtor de Emprestimo
	 * @param midia midia emprestada
	 * @param tomador quem tomou a midia
	 * @param emprestimo data de emprestimo
	 * @param devolucao data de devolucao
	 */
	public Emprestimo(Midia midia, String tomador, Date emprestimo,
			Date devolucao) {
		this.midia = midia;
		this.tomador = tomador;
		this.emprestimo = emprestimo;
		this.devolucao = devolucao;
	}

	/**
	 * Pega midia
	 * @return midia
	 */
	public Midia getMidia() {
		return midia;
	}

	/**
	 * Pega tomador
	 * @return tomador
	 */
	public String getTomador() {
		return tomador;
	}

	/**
	 * Pega data de emprestimo
	 * @return data de emprestimo
	 */
	public Date getEmprestimo() {
		return emprestimo;
	}

	/**
	 * Pega data de devolucao
	 * @return data de devolucao
	 */
	public Date getDevolucao() {
		return devolucao;
	}

	@Override
	public int compareTo(Emprestimo arg0) {
		// TODO Auto-generated method stub
		if(this.emprestimo.before(arg0.getEmprestimo()))
			return 1;
		else if(this.emprestimo.after(arg0.getEmprestimo()))
			return -1;
		else
			return 0;
	}
	

}
