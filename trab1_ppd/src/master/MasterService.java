package master;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class MasterService {

	public static void main(String[] args) throws IOException {
		
		if(args.length == 2)
		{
			String host = args[0];
			Master obj = new Master();
			
			obj.readDictionary(args[1]);
			
			try {
				br.inf.ufes.pp2017_01.Master objRef = (br.inf.ufes.pp2017_01.Master) UnicastRemoteObject.exportObject(obj,0);
				Registry registry = LocateRegistry.getRegistry(host);
				System.err.println("Server binding...");
				registry.rebind("mestre", objRef);
				System.err.println("Master is ready!");
				
							
			} catch (RemoteException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}else{
			System.out.println("Parâmetros inválidos!");
		}
	}

}
