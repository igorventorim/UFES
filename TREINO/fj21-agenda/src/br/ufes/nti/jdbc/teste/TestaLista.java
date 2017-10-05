package br.ufes.nti.jdbc.teste;

import java.util.List;

import br.ufes.nti.jdbc.modelo.Contato;
import br.ufes.nti.jdbc.modelo.ContatoDao;

public class TestaLista {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ContatoDao dao = new ContatoDao();
		List<Contato> contatos = dao.getLista();

		for (Contato contato : contatos) 
		{
			System.out.println("Nome: " + contato.getNome());
			System.out.println("Email: " + contato.getEmail());
			System.out.println("Endereço: " + contato.getEndereco());
			System.out.println("Data de Nascimento: " + contato.getDataNascimento().getTime() + "\n");
		}

	}

}
