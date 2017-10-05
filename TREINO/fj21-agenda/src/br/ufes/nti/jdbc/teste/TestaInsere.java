package br.ufes.nti.jdbc.teste;

import java.util.Calendar;

import br.ufes.nti.jdbc.modelo.Contato;
import br.ufes.nti.jdbc.modelo.ContatoDao;

public class TestaInsere {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Contato contato = new Contato();

		contato.setNome("Igor Ventorim");
		contato.setEmail("igor.ventorim@ufes.br");
		contato.setEndereco("R. Sta. Terezinha, Edf. Paraná, Apt. 102 A");
		contato.setDataNascimento(Calendar.getInstance());

		ContatoDao dao = new ContatoDao();

		dao.adiciona(contato);

		System.out.println("Gravado!");
	}


		

	
}
