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

public class Client {
	
	/**
	 * 
	 * @param fileName
	 * @return
	 * @throws IOException
	 */
	public static byte[] getFile(String fileName) throws IOException
	{
		byte[] vector;
		try {
			
			File file = new File(fileName);
			vector = new byte[(int)file.length()];
			InputStream is = new FileInputStream(file);
			is.read(vector, 0, (int) file.length());
			is.close();
			return vector;
			
		} catch (FileNotFoundException e) {
			Random r = new Random();
			int lengthVector = 1000 + r.nextInt(10000);
			vector = new byte[(int)lengthVector];
			r.nextBytes(vector);
			FileOutputStream fos = new FileOutputStream(fileName);
			fos.write(vector);
			fos.close();
			return vector;
		}
	}
	
	/**
	 * 
	 * @param fileName
	 * @param lengthVector
	 * @return
	 * @throws IOException
	 */
	public static byte[] getFile(String fileName,int lengthVector) throws IOException
	{
		byte[] vector;
		try {
			File file = new File(fileName);
			vector = new byte[(int)file.length()];
			InputStream is = new FileInputStream(file);
			is.read(vector, 0, (int) file.length());
			is.close();
			return vector;
		} catch (FileNotFoundException e) {
			Random r = new Random();
			vector = new byte[(int)lengthVector];
			r.nextBytes(vector);
			FileOutputStream fos = new FileOutputStream(fileName);
			fos.write(vector);
			fos.close();
			return vector;
		}
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
				
				switch (args.length) 
				{
					case 4:
						try {
							long tempoInicio = System.currentTimeMillis();
							cipherText = getFile(args[1],Integer.parseInt(args[3]));
							knownText = args[2].getBytes("UTF-8");
							possibleSolutions = master.attack(cipherText, knownText);
							generateFiles(possibleSolutions);
							System.out.println("Tempo Total: "+(System.currentTimeMillis()-tempoInicio)/1000);
						} catch (NumberFormatException | IOException e1) {
							e1.printStackTrace();
						}
						break;
					case 3:
						try {
							long tempoInicio = System.currentTimeMillis();
							cipherText = getFile(args[1]);
							knownText = args[2].getBytes("UTF-8");
							possibleSolutions = master.attack(cipherText, knownText);
							generateFiles(possibleSolutions);
							System.out.println("Tempo Total: "+(System.currentTimeMillis()-tempoInicio)/1000);
						} catch (IOException e) {
							e.printStackTrace();
						}
						break;
					default:
						System.out.println("Parâmetros inválidos.");
						System.exit(1);
				}
			}catch(RemoteException | NotBoundException e3){ e3.printStackTrace();}
	}
}
