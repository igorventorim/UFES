package problems;
import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.encodings.solutionType.RealSolutionType;
import jmetal.util.JMException;

/**
 * Classe com a implementação do problema EggHolder
 * @author igor
 *
 */
public class EggholderProblem extends Problem {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public EggholderProblem(String solutionType,Integer numberOfVariables) {
		// TODO Auto-generated constructor stub
		numberOfVariables_ = numberOfVariables;
		numberOfObjectives_ = 1;
		numberOfConstraints_ = 0;
		
		problemName_ = "Eggholder";
		
		lowerLimit_ = new double[numberOfVariables];
		upperLimit_ = new double[numberOfVariables];
		
		for(int i=0; i < numberOfVariables_; i++)
		{
			lowerLimit_[i] = -512.00;
			upperLimit_[i] = 512.00;
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
		
		double result = 0.0;
		Variable[] var = solution.getDecisionVariables();
		double x1 = var[0].getValue();
		double x2 = var[1].getValue();
		
		result = -(x2 + 47)* Math.sin(Math.sqrt(Math.abs(x2+(x1/2.0)+47))) - x1*Math.sin(Math.sqrt(Math.abs(x1-(x2+47))));
		solution.setObjective(0, result);
	}

}
