package master;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;
import java.util.UUID;

import br.inf.ufes.pp2017_01.Guess;

public class Attack {
	
	private boolean status;
	private boolean finalized;
	private UUID slaveIdentifier;
	private int initWordIndex;
	private int finalWordIndex;
	private int attackNumber;
	private int checkPoint;
	
	Set<Guess> possibleSolutions = new HashSet();
	
	public Attack(boolean status, int initWordIndex, int finalWordIndex, UUID key, int attackNumber) {
		this.status = status;
		this.initWordIndex = initWordIndex;
		this.finalWordIndex = finalWordIndex;
		this.slaveIdentifier = key;
		this.attackNumber = attackNumber;
		this.finalized = false;
		this.checkPoint = initWordIndex;
	}
	
	public boolean isFinalized() {
		return finalized;
	}

	public void setFinalized(long currentindex) {
		if(this.finalized){ return;}
		if(currentindex == finalWordIndex)
		{
			this.finalized = true;
		}
	}
	
	public void close() {
			this.finalized = true;
	}
	
	public void open() {
		this.finalized = false;
	}
	
	public void setSlaveIdentifier(UUID slaveIdentifier) {
		this.slaveIdentifier = slaveIdentifier;
	}

	public boolean isStatus() {
		return status;
	}

	public void setStatus(boolean status) {
		this.status = status;
	}

	public int getInitWordIndex() {
		return initWordIndex;
	}

	public int getFinalWordIndex() {
		return finalWordIndex;
	}
	
	public UUID getSlaveIdentifier() {
		return slaveIdentifier;
	}

	public int getAttackNumber() {
		return attackNumber;
	}
	
	public Set<Guess> getPossibleSolutions() {
		return possibleSolutions;
	}

	public void addPossibleSolutions(Guess possibleSolution) {
		this.possibleSolutions.add(possibleSolution);
	}
	
	public int getCheckPoint() {
		return checkPoint;
	}

	public void setCheckPoint(int checkPoint) {
		this.checkPoint = checkPoint;
	}

	
	

}
