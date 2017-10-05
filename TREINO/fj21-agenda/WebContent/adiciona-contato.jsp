<!DOCTYPE html>
<html>
<head>
	<link href="css/jquery.css" rel="stylesheet">
	<script src="js/jquery.js"></script>
	<script src="js/jquery-ui.js"></script>
</head>
<body>
	<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
	<%@taglib tagdir="/WEB-INF/tags" prefix="ventorim" %>
	<c:import url="cabecalho.jsp"/>
	
	<form action="adicionaContato">
			Nome: <input type="text" name="nome" /><br /> 
			E-mail: <input type="text" name="email" /><br /> 
			Endereço: <input type="text" name="endereco" /><br />
			Data Nascimento: <input type="text" name="dataNascimento" /><br /> 
			<input type="submit" value="Gravar" />
	</form>
	<c:import url="rodape.jsp"/>
	
</body>
</html>