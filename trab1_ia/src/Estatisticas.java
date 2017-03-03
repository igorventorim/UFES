import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.util.JMException;

/**
 * CLASSE PARA MANIPULAÇÃO DE ESTATÍSTICAS
 * @author igor
 *
 */
public class Estatisticas {
	
	private long[] amostra = null;
	private double[] amostraDouble = null;
	private Solution[] amostraPontos;
	
	/**
	 * Método de inicialização de estatisticas para trabalhar com pontos
	 * @param amostraPontos
	 */
	public Estatisticas(Solution[] amostraPontos)
	{
		this.amostraPontos = amostraPontos;
	}
	
	/**
	 * Método de inicialização de estatisticas para amostra double
	 * @param amostraDouble
	 */
	public Estatisticas(double[] amostraDouble)
	{
		this.amostraDouble = amostraDouble;
	}
	
	/**
	 * Método de inicialização de estatisticas para amostra long
	 * @param amostra
	 */
	public Estatisticas(long[] amostra)
	{
		this.amostra = amostra;
	}
	
	
	/**
	 * Método de calcular média dos pontos
	 * @param numberOfVariables Número de variáveis
	 * @return Média dos pontos
	 * @throws JMException
	 */
	public double[] mediaPontos(int numberOfVariables) throws JMException
	{
		double var[] = new double[numberOfVariables];
		for(int i = 0; i < numberOfVariables;i++)
		{
			for (Solution sol : this.amostraPontos) {
				Variable variaveis[] = sol.getDecisionVariables();
				var[i] += variaveis[i].getValue();				
			}	
			var[i] /= (double)this.amostraPontos.length;
		}
		return var;
	}
	
	/**
	 * Método para calculo de média
	 * @return Média da amostra
	 */
	public double media()
	{
		double result = 0;
		
		if(this.amostra == null)
		{
			
			for(int i = 0; i < this.amostraDouble.length; i++)
				result += this.amostraDouble[i];
			
			return result/(double)this.amostraDouble.length;
			
		}else
		{	
			for(int i = 0; i < this.amostra.length; i++)
				result += this.amostra[i];
			
			return result/(double)this.amostra.length;
		}
		
		
	}
	
	/**
	 * Método para calcular a variância da amostra
	 * @return variancia da amostra
	 */
	public double variancia()
	{
		double media = this.media();
		double result = 0;
		
		if(this.amostra == null)
		{
			for(int i=0; i < this.amostraDouble.length; i++)
				result += Math.pow(this.amostraDouble[i] - media,2); 
			
			result /= (double)this.amostraDouble.length;
			
			return result;
		}else
		{
			for(int i=0; i < this.amostra.length; i++)
				result += Math.pow(this.amostra[i] - media,2); 
			
			result /= (double)this.amostra.length;
			
			return result;
		}
	}
	
	/**
	 * Método que calcula o desvio padrão da amostra
	 * @return Desvio padrão da amostra
	 */
	public double desvioPadrao(){ return Math.sqrt(this.variancia()); }
	
	/**
	 * Método que encontra o maior número da amostra
	 * @return maior elemento da amostra
	 */
	public double maior()
	{
		double maior = 0;
		
		if(this.amostra == null)
		{
			for (int i=0; i < this.amostraDouble.length;i++) {
				
				if(this.amostraDouble[i] > maior)
					maior = this.amostraDouble[i];
			}
		}else{
			for (int i=0; i < this.amostra.length;i++) {
		
				if(this.amostra[i] > maior)
					maior = this.amostra[i];
			}
		}
		return maior;
	}
	
	/**
	 * Método para encontrar o menor número da amostra
	 * @return menor número da amostra
	 */
	public double menor()
	{
		double menor = Double.MAX_VALUE;
		if(this.amostra == null)
		{
			for (int i=0; i < this.amostraDouble.length;i++) {
				if(this.amostraDouble[i] < menor)
					menor = this.amostraDouble[i];
			}
		}else
		{
			for (int i=0; i < this.amostra.length;i++) {
				if(this.amostra[i] < menor)
					menor = this.amostra[i];
			}
		}
		return menor;
	}
	
}
