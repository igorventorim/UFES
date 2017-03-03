package com.sample;

import java.util.Scanner;

import org.kie.api.KieServices;
import org.kie.api.runtime.KieContainer;
import org.kie.api.runtime.KieSession;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String question;
        // load up the knowledge base
        KieServices ks = KieServices.Factory.get();
	    KieContainer kContainer = ks.getKieClasspathContainer();
    	KieSession kSession = kContainer.newKieSession("ksession-rules");
    	
    	
		do{
			
			Animal animal = new Animal();
			animal.setParameters();
			kSession.insert(animal);
			kSession.fireAllRules();
			
			System.out.println("\n\nDeseja realizar uma nova busca?");
			System.out.print("[s/n]: ");
			Scanner scanner = new Scanner(System.in);
			question = scanner.nextLine().toLowerCase();
		}while(question.equals("s"));
	}

}
