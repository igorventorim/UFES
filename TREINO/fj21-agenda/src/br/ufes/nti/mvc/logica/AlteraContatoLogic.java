package br.ufes.nti.mvc.logica;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import javax.servlet.RequestDispatcher;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import br.ufes.nti.jdbc.modelo.Contato;
import br.ufes.nti.jdbc.modelo.ContatoDao;
import br.ufes.nti.mvc.Logica;

public class AlteraContatoLogic implements Logica {

	@Override
	public void executa(HttpServletRequest req, HttpServletResponse res) throws Exception {
		// TODO Auto-generated method stub
		
		Contato contato = new Contato();
		String id = req.getParameter("id");
		contato.setId(Long.parseLong(id));
		contato.setNome(req.getParameter("nome"));
		contato.setEndereco(req.getParameter("endereco"));
		contato.setEmail(req.getParameter("email"));
		
		//Converte a data de String para Calendar
		String dataEmTexto = req.getParameter("dataNascimento");
		Date date = new SimpleDateFormat("dd/MM/yyyy").parse(dataEmTexto);
		Calendar dataNascimento = Calendar.getInstance();
		dataNascimento.setTime(date);
		contato.setDataNascimento(dataNascimento);
		ContatoDao dao = new ContatoDao();
		dao.altera(contato);
		RequestDispatcher rd = req.getRequestDispatcher("/lista-contatos-elegante.jsp");
		rd.forward(req, res);
		System.out.println("Alterando contato ..." + contato.getNome());

	}

}
