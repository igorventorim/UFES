package master;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.UUID;

import br.inf.ufes.pp2017_01.Guess;
import br.inf.ufes.pp2017_01.Slave;
import br.inf.ufes.pp2017_01.SlaveManager;

public class Master implements br.inf.ufes.pp2017_01.Master {

	private List<String> dictionaryWordsList;
	private Map<UUID,Slave> slaveList = new TreeMap<>();
	private Map<UUID,String> nameSlavesList = new TreeMap<>();
	private static int attack;
	Map<Integer,Map<UUID,Attack>> attackSlaveList = new HashMap<>();
	Map<Integer,Map<UUID,Attack>> attackRecoverErrorMap = new HashMap<>();
	private byte[] ciphertext;
	private byte[] knowntext;
	
	public void readDictionary(String fileName)
	{
		
		dictionaryWordsList = new ArrayList<>();
		try(BufferedReader br = new BufferedReader(new FileReader(fileName)))
		{
			String currentWord;
			while((currentWord = br.readLine()) != null)
			{
				dictionaryWordsList.add(currentWord);
			}
			
		} catch (IOException e) {
			System.out.println("Dictionary file not found!");
		}
	}
	
	public int numberSlavesRegister(){
		return slaveList.size();
	}
	
	public int numberWordsDictionary()
	{
		return dictionaryWordsList.size();
	}
	
	@Override
	public synchronized void addSlave(Slave s, String slaveName, UUID slavekey) throws RemoteException {
			
			if(!slaveList.containsKey(slavekey))
			{
				slaveList.put(slavekey, s);
				nameSlavesList.put(slavekey, slaveName);
				System.out.println("Escravo "+slaveName+" - UUID: "+slavekey+" registrado com sucesso!");
			}
	}

	@Override
	public void removeSlave(UUID slaveKey) throws RemoteException {
		slaveList.remove(slaveKey);
		nameSlavesList.remove(slaveKey);
	}

	@Override
	public synchronized void foundGuess(UUID slaveKey, int attackNumber, long currentindex, Guess currentguess)
			throws RemoteException {
		System.out.println(nameSlavesList.get(slaveKey)+":"+currentindex+":"+dictionaryWordsList.get((int)currentindex-1));
		attackSlaveList.get(attackNumber).get(slaveKey).addPossibleSolutions(currentguess);
	}

	@Override
	public void checkpoint(UUID slaveKey, int attackNumber, long currentindex) throws RemoteException {		
		System.out.println(nameSlavesList.get(slaveKey)+":"+currentindex);
			attackSlaveList.get(attackNumber).get(slaveKey).setStatus(true);
			attackSlaveList.get(attackNumber).get(slaveKey).setFinalized(currentindex);
			attackSlaveList.get(attackNumber).get(slaveKey).setCheckPoint((int) currentindex);
		if(attackRecoverErrorMap.get(attackNumber).get(slaveKey) != null)
		{
			attackRecoverErrorMap.get(attackNumber).get(slaveKey).setFinalized(currentindex);
		}	
	}

	@Override
	public Guess[] attack(byte[] ciphertext, byte[] knowntext) throws RemoteException {
		this.ciphertext = ciphertext;
		this.knowntext = knowntext;
		attack++;
		attackSlaveList.put(attack, new HashMap<>());
		attackRecoverErrorMap.put(attack, new HashMap<>());
		System.out.println("Solicitação de ataque chegou!!! - knowntext = "+new String(knowntext));
		int initWordIndex = 0, finalWordIndex;
		if(numberSlavesRegister() != 0)
		{
			int size = (numberWordsDictionary()-1)/numberSlavesRegister();
			if(size*numberSlavesRegister() == numberWordsDictionary())
			{
				finalWordIndex = size + (numberWordsDictionary() - size*numberSlavesRegister());
			}else{ finalWordIndex = size; }
			Map<UUID,Slave> copy = new HashMap<UUID,Slave>(slaveList);
			for (Map.Entry<UUID, Slave> entry: copy.entrySet()) {
				try{
					attackSlaveList.get(attack).put(entry.getKey(), new Attack(true, initWordIndex, finalWordIndex, entry.getKey(), attack));
					entry.getValue().startSubAttack(ciphertext, knowntext, initWordIndex, finalWordIndex, attack, this);
					initWordIndex = finalWordIndex;
					finalWordIndex += size;
				}catch (RemoteException e) {
					attackSlaveList.get(attack).remove(entry.getKey());
					removeSlave(entry.getKey());
					if(slaveList.size() == 0){ return null;}
					
					for (Map.Entry<UUID, Slave> en: slaveList.entrySet()){ 
						en.getValue().startSubAttack(ciphertext, knowntext, initWordIndex, finalWordIndex, attack, this); 
						attackRecoverErrorMap.get(attack).put(en.getKey(), new Attack(true, initWordIndex, finalWordIndex, en.getKey(), attack));
						break;
					}
					initWordIndex = finalWordIndex;
					finalWordIndex += size;
				}
			}
			(new CheckSlaveThread(this,attack)).start();
			
			while(checkFinalizedAttack(attack) != true)
			{
				try {
					Thread.sleep(10000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			System.out.println("Ataque"+ attack+" finalizado com sucesso!" );
			return getPossibleSolutions(attack);
		}else{ return null;}
	}
	
	public void checkStatusAttack()
	{
		for (Map.Entry<Integer, Map<UUID,Attack>> mapSlaves : attackSlaveList.entrySet()) {
			for (Map.Entry<UUID, Attack> attack : mapSlaves.getValue().entrySet()) {
				if(attack.getValue().isStatus() == false && attack.getValue().isFinalized() == false )
				{
					try {
						this.removeSlave(attack.getValue().getSlaveIdentifier());
						for (Map.Entry<UUID, Slave> en: slaveList.entrySet()){ 
							en.getValue().startSubAttack(ciphertext, knowntext, attack.getValue().getCheckPoint(), attack.getValue().getFinalWordIndex(), attack.getValue().getAttackNumber(), this); 
							attackRecoverErrorMap.get(attack.getValue().getAttackNumber()).put(en.getKey(),new Attack(true, attack.getValue().getCheckPoint(), attack.getValue().getFinalWordIndex(), en.getKey(), attack.getValue().getAttackNumber()));
							attack.getValue().close();
							break;
						}
					} catch (RemoteException e) {
						e.printStackTrace();
					}
				}
			}
		}
		
//		for (Map.Entry<Integer, Map<UUID,Attack>> mapSlaves : attackRecoverErrorMap.entrySet()) {
//			for (Map.Entry<UUID, Attack> attack : mapSlaves.getValue().entrySet()) {
//				if(attack.getValue().isStatus() == false && attack.getValue().isFinalized() == false )
//				{
//					try {
//						this.removeSlave(attack.getValue().getSlaveIdentifier());
//						for (Map.Entry<UUID, Slave> en: slaveList.entrySet()){ 
//							en.getValue().startSubAttack(ciphertext, knowntext, attack.getValue().getCheckPoint(), attack.getValue().getFinalWordIndex(), attack.getValue().getAttackNumber(), this); 
//							attackRecoverErrorMap.get(attack.getValue().getAttackNumber()).put(en.getKey(),new Attack(true, attack.getValue().getCheckPoint(), attack.getValue().getFinalWordIndex(), en.getKey(), attack.getValue().getAttackNumber()));
//							attack.getValue().close();
//							break;
//						}
//					} catch (RemoteException e) {
//						e.printStackTrace();
//					}
//				}
//			}
//		}
		
		
	}
	
	public void setStatusAttack()
	{
		for (Map.Entry<Integer, Map<UUID,Attack>> mapSlaves : attackSlaveList.entrySet()) {
			for (Map.Entry<UUID, Attack> attack : mapSlaves.getValue().entrySet()) {
				attack.getValue().setStatus(false);
			}
		}
			
	}
	
	public boolean checkFinalizedAttack(int attack)
	{
		for (Map.Entry<UUID, Attack> slaveAttack : attackSlaveList.get(attack).entrySet()) {
			if(slaveAttack.getValue().isFinalized())
			{
				continue;
			}else{ return false;}
		}
		
		for (Map.Entry<UUID, Attack> slaveAttack : attackRecoverErrorMap.get(attack).entrySet()) {
			if(slaveAttack.getValue().isFinalized())
			{
				continue;
			}else{ return false;}
		}
		return true;
	}
	
	public Guess[] getPossibleSolutions(int attack)
	{
		Set<Guess> possibleSolutions = new HashSet<>();
		Set<Guess> subList;
		for (Map.Entry<UUID, Attack> slaveAttack : attackSlaveList.get(attack).entrySet()) {
			subList = slaveAttack.getValue().getPossibleSolutions();
			if(subList.size() >0)
			{
				possibleSolutions.addAll(subList);
			}
		}
		
		for (Map.Entry<UUID, Attack> slaveAttack : attackRecoverErrorMap.get(attack).entrySet()) {
			subList = slaveAttack.getValue().getPossibleSolutions();
			if(subList.size() >0)
			{
				possibleSolutions.addAll(subList);
			}
		}
		
		Guess[] guess = new Guess[possibleSolutions.size()];
		possibleSolutions.toArray(guess);
		return guess;
	}

}


class CheckSlaveThread extends Thread
{
	private Master master;
	private int attack;
	public CheckSlaveThread(Master master,int attack) {
		this.master = master;
		this.attack = attack;
	}
	
	public void run()
	{
		
		try {
			
			while(master.checkFinalizedAttack(attack) != true)
			{
				master.checkStatusAttack();
				master.setStatusAttack();
				Thread.sleep(20000);
			}
			
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}
