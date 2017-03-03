package algoritmo;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.util.JMException;

public class Estatisticas {
	
	private long[] amostra = null;
	private double[] amostraDouble = null;
	private Solution[] amostraPontos;
	
	public Estatisticas(Solution[] amostraPontos)
	{
		this.amostraPontos = amostraPontos;
	}
	
	public Estatisticas(double[] amostraDouble)
	{
		this.amostraDouble = amostraDouble;
	}
	
	public Estatisticas(long[] amostra)
	{
		this.amostra = amostra;
	}
	
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
	
	public double desvioPadrao(){ return Math.sqrt(this.variancia()); }
	
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
