package slave;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Serializable;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.Registry;
import java.security.InvalidKeyException;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

import br.inf.ufes.pp2017_01.Guess;
import br.inf.ufes.pp2017_01.SlaveManager;

public class Slave implements br.inf.ufes.pp2017_01.Slave, Serializable{

	private List<String> dictionaryWordsList;
	private String slaveName;
	private UUID identifier;
	
	public Slave(String name) {
		this.slaveName = name;
		this.identifier = UUID.randomUUID();
		System.out.println(name+" inicializado com sucesso!");
	}
	
	public String getSlaveName() {
		return slaveName;
	}

	public UUID getIdentifier() {
		return identifier;
	}

		
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
	
	
	@Override
	public void startSubAttack(byte[] ciphertext, byte[] knowntext, long initialwordindex, long finalwordindex,
			int attackNumber, SlaveManager callbackinterface) throws RemoteException 
	{
//		System.out.println("Ataque do "+slaveName+" inicializado com sucesso!");
//		System.out.println("Indice:"+initialwordindex+" - "+finalwordindex);
//		System.out.println("Ataque "+attackNumber);
		(new SubAttackThread(ciphertext, knowntext, initialwordindex, finalwordindex, attackNumber, callbackinterface, dictionaryWordsList, identifier)).start();;
	}

}

class RegisterSlaveThread extends Thread
{
	
	private String slaveName;
	private br.inf.ufes.pp2017_01.Slave slave;
	private UUID identifier;
	private br.inf.ufes.pp2017_01.Master master;
	private Registry registry;
	
	public RegisterSlaveThread(br.inf.ufes.pp2017_01.Slave slave, String slaveName, UUID slaveKey, br.inf.ufes.pp2017_01.Master master, Registry registry) {
		this.slaveName = slaveName;
		this.identifier = slaveKey;
		this.slave = slave;
		this.master = master;
		this.registry = registry;
	}
	
	public void run()
	{
		while(true)
		{	
			try
			{
				try
				{
					master.addSlave(slave, slaveName, identifier);
					Thread.sleep(30000);
				} catch (RemoteException e) 
				{
					e.printStackTrace();
					System.out.println("Problemas no Master! Tentando se recuperar da falha em 30s...");
					Thread.sleep(30000);					
					try 
					{
						master = (br.inf.ufes.pp2017_01.Master) registry.lookup("master");
						master.addSlave(slave, slaveName, identifier);
					} catch (RemoteException | NotBoundException e1) {
						System.out.println("Não foi possível se recuperar da falha, tentando novamente em breve...");
					}
					
				} 
			}catch (InterruptedException e) {}
		}
	}
	
}

class SubAttackThread extends Thread
{
	private byte[] ciphertext;
	private byte[] knowntext;
	private long initialwordindex;
	private long finalwordindex;
	private int attackNumber;
	private SlaveManager callbackinterface;
	private List<String> dictionaryWordsList;
	private UUID identifier;
	
	public SubAttackThread(byte[] ciphertext, byte[] knowntext, long initialwordindex, long finalwordindex,
			int attackNumber, SlaveManager callbackinterface, List<String> dictionaryWordsList, UUID identifier) {
		this.ciphertext = ciphertext;
		this.knowntext = knowntext;
		this.initialwordindex =  initialwordindex;
		this.finalwordindex = finalwordindex;
		this.attackNumber = attackNumber;
		this.callbackinterface = callbackinterface;
		this.dictionaryWordsList = dictionaryWordsList;
		this.identifier = identifier;
	}
	
	public void run()
	{
		List<String> subDictionary = dictionaryWordsList.subList((int)initialwordindex,(int)finalwordindex);
		(new CheckPointerThread(attackNumber, identifier, callbackinterface,this)).start();
		for (String key : subDictionary) {
			initialwordindex++;
			try {
				SecretKeySpec keySpec = new SecretKeySpec(key.getBytes(), "Blowfish");
				Cipher cipher;
				cipher = Cipher.getInstance("Blowfish");
				cipher.init(Cipher.DECRYPT_MODE, keySpec);
				byte[] decrypted = cipher.doFinal(ciphertext);
				String messageDecrypted = new String(decrypted);
				
				if(messageDecrypted.contains(new String(knowntext)))
				{
					
					Guess guess = new Guess();
					guess.setKey(key);
					guess.setMessage(decrypted);
					callbackinterface.foundGuess(identifier, attackNumber, initialwordindex, guess);
					
				}
			} catch (javax.crypto.BadPaddingException e) {
//				System.out.println(key+": chave inválida");
//				e.printStackTrace();
			} catch (Exception e) {
				e.printStackTrace();
			}
	
		}
		
		try {
			callbackinterface.checkpoint(identifier, attackNumber, finalwordindex);
		} catch (RemoteException e) {
			e.printStackTrace();
			System.out.println("Problemas no mestre!");
		}
	}
	
	public Integer getInitialwordindex()
	{
		return (int) initialwordindex;
	}
	
	public Integer getFinalwordindex()
	{
		return (int) finalwordindex;
	}
}


class CheckPointerThread extends Thread
{
	private int attack;
	private UUID slaveKey;
	private SlaveManager callbackinterface;
	private SubAttackThread subAttackThread;
	
	public CheckPointerThread(int attack,UUID slavekey, SlaveManager callbackinterface, SubAttackThread subAttackThread) {
		this.attack = attack;
		this.slaveKey = slavekey;
		this.callbackinterface = callbackinterface;
		this.subAttackThread = subAttackThread;
	}
	
	public void run()
	{
		while(subAttackThread.getInitialwordindex() < subAttackThread.getFinalwordindex() )
		{
			try {
				callbackinterface.checkpoint(slaveKey, attack, subAttackThread.getInitialwordindex());
				Thread.sleep(10000);
			} catch (RemoteException e) {
				e.printStackTrace();
				System.out.println("Problemas no Master!");
				break;
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
