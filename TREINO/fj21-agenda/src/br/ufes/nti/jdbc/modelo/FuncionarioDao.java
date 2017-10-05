package br.ufes.nti.jdbc.modelo;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.SQLException;

//import com.mysql.jdbc.Connection;

import br.ufes.nti.jdbc.ConnectionFactory;

public class FuncionarioDao {

	// a conexão com o banco de dados
		private Connection connection;

		public FuncionarioDao() 
		{
			this.connection = (Connection) new ConnectionFactory().getConnection();
		}
		
		
		public void adiciona(Funcionario funcionario) {
			String sql = "insert into contatos " + "(nome,user,password)" + " values (?,?,?)";
			try {
				// prepared statement para inserção
				PreparedStatement stmt = connection.prepareStatement(sql);
				// seta os valores
				stmt.setString(1, funcionario.getNome());
				stmt.setString(2, funcionario.getUser());
				stmt.setString(3, funcionario.getPassword());
				// executa
				stmt.execute();
				stmt.close();
			} catch (SQLException e) {
				throw new RuntimeException(e);
			}
		}
	
}
