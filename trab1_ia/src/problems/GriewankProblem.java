package problems;
import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.encodings.solutionType.RealSolutionType;
import jmetal.util.JMException;

/**
 * Classe com a implementação do problema Griewank
 * @author igor
 *
 */
public class GriewankProblem extends Problem {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	
	public GriewankProblem(String solutionType, Integer numberOfVariables)
	{
		// TODO Auto-generated constructor stub
		
		numberOfVariables_ = numberOfVariables;
		numberOfObjectives_ = 1;
		numberOfConstraints_ = 0;
		
		problemName_ = "Griewank";
		
		lowerLimit_ = new double[numberOfVariables];
		upperLimit_ = new double[numberOfVariables];
		
		for(int i=0; i < numberOfVariables_; i++)
		{
			lowerLimit_[i] = -600.00;
			upperLimit_[i] = 600.00;
		}
		
		if (solutionType.compareTo("Real") == 0) {
			solutionType_ = new RealSolutionType(this);
		} else {
			System.out.println("Tipo de variavel informada e diferente de Real.");
			System.exit(-1);
		}
	}
	
	@Override
	public void evaluate(Solution solution) throws JMException {
		// TODO Auto-generated method stub
		
		double result;
		Variable[] var = solution.getDecisionVariables();
		double x = var[0].getValue();
		double y = var[1].getValue();
		double z = var[2].getValue();

		result = 1.0 + (Math.pow(x, 2)/4000.00)+(Math.pow(y, 2)/4000.00)+(Math.pow(z, 2)/4000.00) - (Math.cos(x)*Math.cos(y/Math.sqrt(2.0))*Math.cos(z/Math.sqrt(3.0)));
		solution.setObjective(0, result);

	}

}
