package br.ufes.nti.jdbc;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.Calendar;

//import com.mysql.jdbc.Connection;
//import com.mysql.jdbc.PreparedStatement;

public class JDBCInsere {

	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		// conectando
		Connection con = null;
		con = (Connection) new ConnectionFactory().getConnection();
		// cria um preparedStatement
		String sql = "insert into contatos" + " (nome,email,endereco,dataNascimento)" +" values (?,?,?,?)";
		PreparedStatement stmt;
		try {
			stmt = con.prepareStatement(sql);
			stmt.setString(1, "Caelum");
			stmt.setString(2, "contato@caelum.com.br");
			stmt.setString(3, "R. Vergueiro 3185 cj57");
			stmt.setDate(4, new java.sql.Date(
			Calendar.getInstance().getTimeInMillis()));
			// executa
			stmt.execute();
			stmt.close();
			System.out.println("Gravado!");
			con.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// preenche os valores
		
		

	}

}
