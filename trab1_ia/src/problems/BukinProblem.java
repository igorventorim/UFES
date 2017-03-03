package problems;

import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.encodings.solutionType.RealSolutionType;
import jmetal.util.JMException;

/**
 * Classe com a implementação do problema Bukin
 * @author igor
 *
 */
public class BukinProblem extends Problem {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	
	public BukinProblem(String solutionType, Integer numberOfVariables){
		
		numberOfVariables_ = numberOfVariables;
		numberOfObjectives_ = 1;
		numberOfConstraints_ = 0;
		
		problemName_ = "Bukin";
		
		lowerLimit_ = new double[numberOfVariables];
		upperLimit_ = new double[numberOfVariables];
				
			lowerLimit_[0] = -15.00;
			upperLimit_[0] = -5.00;
			lowerLimit_[1] = -3.00;
			upperLimit_[1] = 3;

		
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

		Variable[] var = solution.getDecisionVariables();
		double x1 = var[0].getValue();
		double x2 = var[1].getValue();
		
		double result =  100.00 * Math.sqrt(Math.abs(x2 - (0.01*Math.pow(x1, 2))))+ (0.01*Math.abs(x1+10.00));
		solution.setObjective(0, result);
	}

}
