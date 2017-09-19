package client;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Random;

import br.inf.ufes.pp2017_01.Guess;

public class ClientTeste {
	
	
	public static byte[] getFile(String fileName,int lengthVector) throws IOException
	{
		byte[] vector;
			Random r = new Random();
			vector = new byte[(int)lengthVector];
			r.nextBytes(vector);
			FileOutputStream fos = new FileOutputStream(fileName);
			fos.write(vector);
			fos.close();
			return vector;
	}
	
	
	public static void generateFiles(Guess[] possibleSolutions) throws IOException
	{
		try{
			for (Guess guess : possibleSolutions) 
			{
				File file = new File(guess.getKey()+".msg");
				FileOutputStream fos = new FileOutputStream(file);
				fos.write(guess.getMessage());
				fos.close();
			}
		}catch(NullPointerException e)
		{
			System.out.println("Nenhuma possível solução foi encontrada!!!");
		}
	}
	
	public static void main(String[] args)
	{
		String host = args[0];
		byte[] knownText;
		byte[] cipherText;
		Guess[] possibleSolutions;
		try{
			Registry registry = LocateRegistry.getRegistry(host);
			br.inf.ufes.pp2017_01.Master master = (br.inf.ufes.pp2017_01.Master) registry.lookup("mestre");
				
			for(int i = 50000; i <= 300000 ; i+=50000){
						try {
							long tempoInicio = System.currentTimeMillis();
							cipherText = getFile(args[1],i);
							knownText = args[2].getBytes("UTF-8");
							possibleSolutions = master.attack(cipherText, knownText);
							generateFiles(possibleSolutions);
							long fim = (System.currentTimeMillis()-tempoInicio)/1000;
							System.out.println("TAM "+i+":"+fim+"\n");
						} catch (IOException e) {
							e.printStackTrace();
						}

			}
			}catch(RemoteException | NotBoundException e3){ e3.printStackTrace();}
	}

}
