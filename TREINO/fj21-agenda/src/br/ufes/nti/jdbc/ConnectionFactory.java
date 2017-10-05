package br.ufes.nti.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectionFactory {

	public Connection getConnection() {
		
		try 
		{
			 try {
				Class.forName("com.mysql.jdbc.Driver");
				return DriverManager.getConnection( "jdbc:mysql://localhost/fj21", "root", "ig2014100498");
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return null;
			}
			
		} catch (SQLException e) 
		{
			throw new RuntimeException(e);
		}
	}
	
}
