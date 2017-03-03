package algoritmo;

import java.util.Random;

import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.util.JMException;

/**
 * Classe que defini uma particula do PSO e possui métodos de para trabalhar com o exame.
 * @author igor
 *
 */
public class Particle{
		
	private Solution position;
	
	private double[] velocidade;
	
	private Solution individualBestPosition;
	
	private static Solution bestSolution;
	
	public Solution getPosition() { return position; }
		
	public static Solution getBestSolution() { return bestSolution; }
	
	/**
	 * MÉTODO RESPONSÁVEL POR CRIAÇÃO E EXIBIÇÃO DE UMA PARTICULA
	 * @param problem [Problema a ser avaliado]
	 * @throws ClassNotFoundException
	 * @throws JMException
	 */
	Particle(Problem problem) throws ClassNotFoundException, JMException
	{
		this.position = new Solution(problem);
		this.individualBestPosition = new Solution(problem);
		this.velocidade = new double[problem.getNumberOfVariables()];
		Random rn = new Random();
				
		Variable[] position = this.position.getDecisionVariables();
		for(int i=0; i < problem.getNumberOfVariables();i++){
			position[i].setValue(problem.getLowerLimit(i) + (problem.getUpperLimit(i)-problem.getLowerLimit(i))* rn.nextDouble());
		}
		problem.evaluate(this.position);
		this.individualBestPosition.setObjective(0, this.position.getObjective(0));
	}
	
	/**
	 * Function to class for update individual and global bests of swarm
	 * @param swarm is a list of particles
	 * @throws JMException 
	 */
	public static void updateBests(Particle[] swarm, Problem problem) throws JMException
	{
		for (int i =0; i < swarm.length;i++)
		{
			if (swarm[i].position.getObjective(0) < swarm[i].individualBestPosition.getObjective(0))
			{	
				swarm[i].updateIndividualBestSolution(problem.getNumberOfVariables());
				if(swarm[i].position.getObjective(0) < Particle.bestSolution.getObjective(0))
				{
					swarm[i].updateBestSolution(problem.getNumberOfVariables());
				}
			}
			
		}
	}
	
	/**
	 * Método responsável por atualizar a melhor solução
	 * @param numberOfVariables Número de variáveis do problema
	 * @throws JMException
	 */
	public void updateBestSolution(int numberOfVariables) throws JMException
	{
		Particle.bestSolution.setObjective(0, this.position.getObjective(0));
		for(int i =0; i< numberOfVariables; i++)
			Particle.bestSolution.getDecisionVariables()[i].setValue(this.position.getDecisionVariables()[i].getValue());
	}
	
	/**
	 * Método responsável por atualizar o melhor individual
	 * @param numberOfVariables Número de variáveis do problema
	 * @throws JMException
	 */
	public void updateIndividualBestSolution(int numberOfVariables) throws JMException
	{
		this.individualBestPosition.setObjective(0, this.position.getObjective(0));	
		for(int i=0; i<numberOfVariables;i++)
			this.individualBestPosition.getDecisionVariables()[i].setValue(this.position.getDecisionVariables()[i].getValue());
	}
		
	/**
	 * Método que atualiza velocidade e posição
	 * @param swarm Vetor de particulas do problema
	 * @param w Componente de inercia do problema
	 * @param c1 Componente 1 de aceleração
	 * @param c2 Componente 2 de aceleração
	 * @throws JMException 
	 * @throws ClassNotFoundException 
	 */
	public static void updateVelocityAndPosition(Particle[] swarm,Problem problem,double w, double c1, double c2) throws JMException, ClassNotFoundException
	{
		Random rn = new Random();
		double r1 = rn.nextDouble();
		double r2 = rn.nextDouble();
		double x;
			for (int i =0; i < swarm.length; i++)
			{	
				Variable[] posAtual = swarm[i].position.getDecisionVariables();
				Variable[] bestIndividualPosition = swarm[i].individualBestPosition.getDecisionVariables();
				Variable[] bestPosition = Particle.bestSolution.getDecisionVariables();
				/* TO DO: FAZER ESTE CALCULO DE FORMA MAIS AGRADAVEL!*/
				for(int j = 0; j < problem.getNumberOfVariables();j++)
				{
					x = swarm[i].velocidade[j]*w + c1*r1*(bestIndividualPosition[j].getValue() - posAtual[j].getValue()) + c2*r2*(bestPosition[j].getValue() - posAtual[j].getValue());
					swarm[i].velocidade[j] = x;
					if((posAtual[j].getValue() + x) > problem.getUpperLimit(j) || (posAtual[j].getValue() + x) < problem.getLowerLimit(j))
					{
						swarm[i] = new Particle(problem);
						swarm[i].velocidade = new double[problem.getNumberOfVariables()];
					}else
						posAtual[j].setValue(posAtual[j].getValue() + x);
				}			
			}	
	}

	
	
	/**
	 * Método responsável por gerar a população do examen
	 * @param populationSize Tamanho da população
	 * @return População populada
	 * @throws JMException 
	 * @throws ClassNotFoundException 
	 */
	public static Particle[] generatePopulation(int populationSize, Problem problem) throws ClassNotFoundException, JMException
	{
		Particle[] swarm = new Particle[populationSize];
		Particle.bestSolution = new Solution(problem);
		Particle.bestSolution.setObjective(0, Double.MAX_VALUE);
		
		for (int i = 0; i < swarm.length; i++) 
		{
			swarm[i] = new Particle(problem);
			if(swarm[i].position.getObjective(0) < Particle.bestSolution.getObjective(0))
			{
				swarm[i].updateBestSolution(problem.getNumberOfVariables());
			}
		}				
		
		return swarm;
	}
	
		
}
