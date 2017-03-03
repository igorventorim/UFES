package algoritmo;

import java.text.DecimalFormat;
import java.text.NumberFormat;

import jmetal.core.Algorithm;
import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.SolutionSet;
import jmetal.util.JMException;

/**
 * CLASSE QUE CONTÉM O ALGORITMO PSO E CONTÉM EXIBIÇÃO DOS DADOS ALCANÇADOS
 * @author igor
 *
 */
public class PSO extends Algorithm {

	public PSO(Problem problem) {
		super(problem);
		// TODO Auto-generated constructor stub
	}

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	/**
	 * Método que executa o algoritmo PSO
	 */
	@Override
	public SolutionSet execute() throws JMException, ClassNotFoundException {
		// TODO Auto-generated method stub
		int fixBestSolution = 0;
		double lastValueBestSolution;
		int evaluations = 0;
		
		final int maxEvaluations = ((int) getInputParameter("maxEvaluations"));
		final int populationSize = ((int) getInputParameter("numberOfParticles"));
		final double w = ((double) getInputParameter("inertialCoefficient"));
		final double c1 = ((double) getInputParameter("accelarationCoefficient1"));
		final double c2 = ((double) getInputParameter("accelarationCoefficient2"));
		
		Particle[] swarm = Particle.generatePopulation(populationSize,problem_);
		Particle.updateVelocityAndPosition(swarm, problem_,w, c1, c2);
		lastValueBestSolution = Particle.getBestSolution().getObjective(0);
		
		while(evaluations < maxEvaluations && fixBestSolution < 100)
		{
			for (int i=0; i < swarm.length && evaluations < maxEvaluations;i++)
			{ 
				problem_.evaluate(swarm[i].getPosition());
				evaluations++;
			}
			
			Particle.updateBests(swarm,problem_);
			Particle.updateVelocityAndPosition(swarm, problem_,w, c1, c2);
			
			if(lastValueBestSolution == Particle.getBestSolution().getObjective(0)){fixBestSolution++;}
			else
			{ 
				lastValueBestSolution = Particle.getBestSolution().getObjective(0);
				fixBestSolution = 0;
			}
		}
		
		
		setOutputParameter("evaluations", evaluations);
		SolutionSet result = new SolutionSet(1);
		result.add(Particle.getBestSolution());

		return result;
	}
	
	/**
	 * Função responsável por realizar as execuções do PSO e exibir estatísticas
	 * @param problem [Problema a ser avaliado]
	 * @param pso [Algoritmo a ser executado]
	 * @throws ClassNotFoundException
	 * @throws JMException
	 */
	public static void executePSO(Problem problem, Algorithm pso) throws ClassNotFoundException, JMException
	{
		final int ITER = 10;
		SolutionSet solution = null;
		long[] times = new long[ITER];
		long[] avaliacoes = new long[ITER];
		double[] otimos = new double[ITER];
		Solution[] solutions = new Solution[ITER];
		
		for (int i = 0; i < ITER; i++) 
		{
			long tempoInicial = System.currentTimeMillis();
			solution = pso.execute();
			times[i] = System.currentTimeMillis() - tempoInicial;
			avaliacoes[i] = Long.valueOf((Integer.toString((int)pso.getOutputParameter("evaluations"))));
			otimos[i] = solution.get(0).getObjective(0);
			solutions[i] = Particle.getBestSolution();
		}
		
		Estatisticas statusTempo = new Estatisticas(times);
		Estatisticas statusEvaluations = new Estatisticas(avaliacoes);
		Estatisticas statusOtimos = new Estatisticas(otimos);
		Estatisticas statusPoints = new Estatisticas(solutions);
		
		NumberFormat formatter = new DecimalFormat("#0.00000");
		NumberFormat format = new DecimalFormat("#0");

		
		double[] var = statusPoints.mediaPontos(problem.getNumberOfVariables());
		System.out.println(problem.getName());
		System.out.println("\nParametros:");
		System.out.println(" - Número de particulas: "+pso.getInputParameter("numberOfParticles"));
		System.out.println(" - Coeficiente de inercia: "+pso.getInputParameter("inertialCoefficient"));
		System.out.println(" - Coeficiente de aceleração 1: "+pso.getInputParameter("accelarationCoefficient1"));
		System.out.println(" - Coeficiente de aceleração 2: "+pso.getInputParameter("accelarationCoefficient2"));
		System.out.println(" - Número de convergência: 100");
		System.out.println(" - Número máximo de avaliações: "+pso.getInputParameter("maxEvaluations"));
		System.out.print("\nBest Solution: ["+var[0]+",");
		for(int i = 1; i < problem.getNumberOfVariables()-1;i++){ System.out.print(var[i]+",");}
		System.out.print(var[problem.getNumberOfVariables()-1]+"]");
		
		System.out.println("\nEstatisticas de melhores:");
		System.out.println(" - Media dos melhores: "+formatter.format(statusOtimos.media()));
		System.out.println(" - Min dos melhores: "+statusOtimos.menor());
		System.out.println(" - Max dos melhores: "+statusOtimos.maior());
		System.out.println(" - Desvio padrão dos melhores: "+statusOtimos.desvioPadrao());
		
		System.out.println("\nEstatisticas de tempo:");
		System.out.println(" - Average execution time is " + formatter.format((statusTempo.media()) / 1000d) + " seconds");
		System.out.println(" - Min execution time is " + formatter.format((statusTempo.menor()) / 1000d) + " seconds");
		System.out.println(" - Max execution time is " + formatter.format((statusTempo.maior())/ 1000d) + " seconds");
		System.out.println(" - Standard deviation time is " + formatter.format((statusTempo.desvioPadrao()) / 1000d) + " seconds"); 
		
		System.out.println("\nEstatisticas de Avaliações:");
		System.out.println(" - Media de avaliações realizadas: " + format.format(statusEvaluations.media()));
		System.out.println(" - Min das avaliações realizadas: " + format.format(statusEvaluations.menor()));
		System.out.println(" - Max das avaliações realizadas: " + format.format(statusEvaluations.maior()));
		System.out.println(" - Desvio Padrão de avaliações realizadas: " + format.format(statusEvaluations.desvioPadrao())+"\n\n\n");
	
	}

}
