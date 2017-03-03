import algoritmo.PSO;
import jmetal.core.Algorithm;
import jmetal.core.Problem;
import jmetal.util.JMException;
import problems.BukinProblem;
import problems.EggholderProblem;
import problems.GriewankProblem;

public class Main {

	public static void main(String[] args) throws ClassNotFoundException, JMException {
		// TODO Auto-generated method stub

		Algorithm pso;
		Problem[] problems = new Problem[3];
		
		problems[0] = new BukinProblem("Real", 2);
		pso = new PSO(problems[0]);
		pso.setInputParameter("maxEvaluations", 25000);
		pso.setInputParameter("numberOfParticles", 30);
		pso.setInputParameter("inertialCoefficient", 0.8);
		pso.setInputParameter("accelarationCoefficient1", 1.0);
		pso.setInputParameter("accelarationCoefficient2", 1.0);
		PSO.executePSO(problems[0],pso);
		
		problems[1] = new EggholderProblem("Real", 2);
		pso = new PSO(problems[1]);
		pso.setInputParameter("maxEvaluations", 25000);
		pso.setInputParameter("numberOfParticles", 30);
		pso.setInputParameter("inertialCoefficient", 0.8);
		pso.setInputParameter("accelarationCoefficient1", 2.0);
		pso.setInputParameter("accelarationCoefficient2", 2.0);
		PSO.executePSO(problems[1],pso);
		
		problems[2] = new GriewankProblem("Real", 3);
		pso = new PSO(problems[2]);
		pso.setInputParameter("maxEvaluations", 25000);
		pso.setInputParameter("numberOfParticles", 30);
		pso.setInputParameter("inertialCoefficient", 0.8);
		pso.setInputParameter("accelarationCoefficient1", 2.0);
		pso.setInputParameter("accelarationCoefficient2", 2.0);
		PSO.executePSO(problems[2],pso);
						
	}
		
}
