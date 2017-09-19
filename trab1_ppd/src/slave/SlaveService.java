package slave;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.UUID;

public class SlaveService {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		if(args.length == 3){
		String host = args[0];
		
		try {
				Slave slave = new Slave(args[1]);
				slave.readDictionary(args[2]);
				br.inf.ufes.pp2017_01.Slave slaveRef = (br.inf.ufes.pp2017_01.Slave) UnicastRemoteObject.exportObject(slave, 0);
				Registry registry = LocateRegistry.getRegistry(host);

				br.inf.ufes.pp2017_01.Master master = (br.inf.ufes.pp2017_01.Master) registry.lookup("mestre");
				(new RegisterSlaveThread(slaveRef, slave.getSlaveName(), slave.getIdentifier(), master, registry)).start();;
								
		} catch (RemoteException | NotBoundException e ) {
			e.printStackTrace();
		}
	}else{
		System.out.println("Parâmetros inválidos!");
	}
	}
	
}


