<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ taglib tagdir="/WEB-INF/tags" prefix="caelum"%>

<c:import url="cabecalho.jsp" />
Formulário para alteração de contatos:
<br />
<form action="mvc" method="POST">
	Id: <input name="id"><br> 
	Nome: <input name="nome"><br>
	E-mail: <input name="email"><br> 
	Endereço: <input type="text" name="endereco"><br>
	Data de Nascimento: <input name="dataNascimento"><br>
	<input type="hidden" name="logica" value="AlteraContatoLogic">
	<input type="submit" value="Enviar">
</form>
<c:import url="rodape.jsp" />