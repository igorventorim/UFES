import java.io.*;
import java.text.*;
import java.util.*;
import java.util.Map.*;
/**
 * CLASSE RESPONSÁVEL PELA LEITURA E ESCRITA DE ARQUIVOS
 * 
 * @author Igor Ventorim (IVentorim) e Fernando Neto(Febane)
 *
 */

public class FileIO{
	
	private static Scanner scanner;
	/**
	 * Le generos de arquivo de generos
	 * @param generosFile - Nome do arquivo que contem a lista de generos para leitura
	 * @return ArrayLIst de generos guardado na memoria
	 * @throws FileNotFoundException
	 */
	public static Map<String,Genero> readGenero(String generosFile)
	{
		//List<Genero> listGenero = new ArrayList<>();
		Map<String,Genero> mapGenero = new HashMap<>();
		
		try {
			scanner = new Scanner(new FileReader(generosFile));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			System.out.println("Erro de I/O");
			return null;
		}
		scanner = scanner.useDelimiter("[;\\n]+");
		
//		System.out.println(scanner.nextLine());
		scanner.nextLine();
		
		while(scanner.hasNext())
		{
			String sigla = scanner.next();
			String nome = scanner.next();
			mapGenero.put(sigla, new Genero(sigla,nome));
		}
		scanner.close();
		return mapGenero;
	}
	
	/**
	 * Le pessoas de arquivos de pessoas
	 * @param pessoaFile - Nome do arquivo que contem a lista de pessoas para leitura
	 * @return Lista de pessoas cadastradas no sistema
	 * @throws FileNotFoundException
	 */
	public static List<Pessoa> readPessoa(String pessoaFile)
	{
		List<Pessoa> listPessoa = new ArrayList<>();
		
		try {
			scanner = new Scanner(new FileReader(pessoaFile));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			System.out.println("Erro de I/O");
			return null;
		}
		scanner = scanner.useDelimiter("[;\\n]+"); // EXPRESSÃO REGULAR JAVA
		
		//System.out.println(scanner.nextLine());
		scanner.nextLine();
		while(scanner.hasNext())
		{
			int cod = 0;
			try{
			cod = Integer.parseInt(scanner.next());
			}catch(NumberFormatException ex)
			{
				System.out.println("Erro de formatação");
				return null;
			}
			String nome = scanner.next();
			listPessoa.add(new Pessoa(cod,nome));
		}
		scanner.close();

		return listPessoa;
	}
	
	/**
	 * Le midias de arquivo de midias
	 * @param midiaFile - Nome do arquivo que contem a lista de midias para a leitura
	 * @param listPessoas - Lista de pessoas cadastradas no sistema
	 * @param mapGenero - Lista de generos cadastrados no sistema
	 * @return	Lista de mÃ­dias cadastradas no sistema
	 */
	public static List<Midia> readMidia(String midiaFile,List<Pessoa> listPessoas, Map<String,Genero> mapGenero)
	{
		List<Midia> listMidia = new ArrayList<>();
		Midia novo;
		Genero gnr;
		
		try {
			scanner = new Scanner(new FileReader(midiaFile));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			System.out.println("Erro de I/O");
			return null;
			
		}
		scanner = scanner.useDelimiter("[;\\n]");
		
		// LOOP para descartar a linha de descriÃ§Ã£o do arquivo
		//for(int i = 0; i < 13; i++)
		
//		System.out.println(scanner.nextLine());
		scanner.nextLine();
		while(scanner.hasNext())
		{
			try{
			Pessoa diretor = new Pessoa();
			int codigo = scanner.nextInt();
			String nome = scanner.next();
			char type = scanner.next().charAt(0);
			String dir = scanner.next();
			//int id = 0;
			if(!dir.equals(""))
			{
				int id = Integer.parseInt(dir)-1;
				try{
					
					diretor = listPessoas.get(id);
				}catch(IndexOutOfBoundsException ex)
				{
					System.out.println("Dados inconsistentes (Diretor:"+(id+1)+")");
					return null;
				}
			}
			String listaAutores = scanner.next();
			List<Pessoa> elenco = listAtores(listaAutores,listPessoas);
			int tamanho = scanner.nextInt();
			String gen = scanner.next();
			try{
			gnr = mapGenero.get(gen);
			}catch(NullPointerException | ClassCastException ex)
			{
				System.out.println("Dados inconsistentes (Genero:"+gen);
				return null;
			}
			String serie = scanner.next();
			String temporada = scanner.next();
			boolean possui = (scanner.next()).equals("x");
			boolean consumiu = scanner.next().equals("x");
			boolean deseja = scanner.next().equals("x");
			double preco = Double.parseDouble((scanner.next()).replace(",", "."));
			
			switch(type)
			{
				case 'L': novo = new Livro(codigo,nome,tamanho,gnr,possui,consumiu,deseja,preco,elenco);	
					listMidia.add(novo);
					gnr.addMidiaGen(novo);
					relationPessoaMidia(novo, elenco);
					break;
				case 'F':	novo = new Filme(codigo,nome,tamanho,gnr,possui,consumiu,deseja,preco,diretor,elenco); 
					listMidia.add(novo);
					gnr.addMidiaGen(novo);
					relationPessoaMidia(novo, elenco);
					try{
						diretor.addMidia(novo);
					}catch(NullPointerException ex)
					{
						System.out.println("Erro de formatação");
					}
					break;
				case 'S':	novo = 	new Serie(codigo,nome,tamanho,gnr,possui,consumiu,deseja,preco,elenco,temporada,serie);
					listMidia.add(novo);
//					((Serie)novo).addNewSerie(serie);
					gnr.addMidiaGen(novo);
					relationPessoaMidia(novo, elenco);
					break;
				default: System.out.println("Este tipo de midia não pode ser cadastrado!");
			}
			}catch(NumberFormatException | InputMismatchException ex )
			{
				System.out.println("Erro de formatação");
				return null;
			}
			
		}
		
		return listMidia;
	}
	
	/**
	 * Método que adiciona a midia em que uma pessoa trabalhou
	 * @param m - Midia ao qual a pessoa trabalhou
	 * @param p - Lista de pessoas que trabalharam nesta midia
	 */
	private static void relationPessoaMidia(Midia m, List<Pessoa> p)
	{
		for (Pessoa pessoa : p) {
			pessoa.addMidia(m);
		}
	}
	
	/**
	 * 
	 * @param codAtores - String com  a lista de código de autores
	 * @param l	- Lista de pessoas com os códigos de todas as pessoas cadastradas no sistema
	 * @return	- Lista de atores que participaram de um filme ou serie
	 * @throws FileNotFoundException
	 */
	private static List<Pessoa> listAtores(String codAtores, List<Pessoa> l)
	{
		List<Pessoa> lista = new ArrayList<>();
		@SuppressWarnings("resource")
		Scanner s = new Scanner(codAtores).useDelimiter("[,\\n]+");
		
		while(s.hasNextInt())
		{
			int idPessoa = s.nextInt()-1;
			try{
			lista.add(l.get(idPessoa));
			}catch(InputMismatchException e)
			{
				System.out.println("Erro de formatação");
				return null;
			}catch(IndexOutOfBoundsException ex)
			{
				System.out.println("Dados inconsistentes (A(u)tor:"+(idPessoa+1)+")");
				return null;
			}
		}
		
		return lista;
	}
	
	/**
	 * 
	 * @param emprestimoFile - Nome do arquivo que contem a lista de emprestimos para a leitura
	 * @param midiaList - Lista de midias cadastradas no sistema
	 * @return - Lista de emprestimos cadastrados no sistema
	 * @throws FileNotFoundException
	 * @throws ParseException
	 */
	public static List<Emprestimo> readEmprestimos(String emprestimoFile,List<Midia> midiaList)
	{
		List<Emprestimo> listEmprestimo = new ArrayList<>(); 
		SimpleDateFormat format = new SimpleDateFormat("dd/MM/yyyy"); 
		try {
			scanner = new Scanner(new FileReader(emprestimoFile));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			System.out.println("Erro de I/O");
			return null;
		}
		scanner = scanner.useDelimiter("[;\\n]+"); // EXPRESSÃƒO REGULAR JAVA
		
		//System.out.println(scanner.nextLine());
		scanner.nextLine();
		
		while(scanner.hasNext())
		{
			Midia emprestada = null;
			int pos = scanner.nextInt()-1;
			try{
			emprestada = midiaList.get(pos);
			}catch(InputMismatchException ex)
			{
				System.out.println("Erro de formatação");
				return null;
			}catch(IndexOutOfBoundsException ex1)
			{
				System.out.println("Dados inconsistentes (Midia:"+(pos+1)+")");
				return null;
			}
			String nome = scanner.next();
			
			Date emprestimo = null;
			Date devolucao = null;
			try {
				emprestimo = (Date)format.parse(scanner.next());
				devolucao = (Date)format.parse(scanner.next());
			} catch (ParseException e) {
				// TODO Auto-generated catch block
				//e.printStackTrace();
				System.out.println("Erro de formatação");
				//System.exit(0);
				return null;
			}
			
			listEmprestimo.add(new Emprestimo(emprestada,nome,emprestimo,devolucao));
			
		}
		scanner.close();
		
		return listEmprestimo;
		
	}
	
	/**
	 * Geracao de relatorio de emprestimos efetuados
	 * @param e lista de emprestimos
	 */
	public static void writeEmprestimos(List<Emprestimo> e){
		try{
		Date hoje = null;
		
		Collections.sort(e);
		
		try{
			hoje = new SimpleDateFormat("dd/MM/yyyy").parse("06/11/2015");
		}
		catch(ParseException ex){
			//ex.printStackTrace();
			System.out.println("Erro de formatação");
			return;
		}
		
		BufferedWriter bw = null;
		try
		{
		    bw = new BufferedWriter( new FileWriter("3-emprestimos.csv"));
		    bw.write("Data;Tomador;Atrasado?;Dias de Atraso\n");
		    
		    for(Emprestimo emp : e){
		    	
		    	String s = new SimpleDateFormat("dd/MM/yyyy").format(emp.getEmprestimo());
		    	
		    	bw.write(s+";"+emp.getTomador()+";");
		    	if(emp.getDevolucao().after(hoje)){
		    		
		    		bw.write("Não;0\n");
		    		
		    	}
		    	else{
		    		
		    		int dias = (int)((hoje.getTime() - emp.getDevolucao().getTime())/86400000);
		    		
		    		bw.write("Sim;"+dias+"\n");
		    		
		    		
		    	}
		    	
		    }
		    bw.close();

		}
		catch ( IOException ex)
		{
			//ex.printStackTrace();
			System.out.println("Erro de I/O");
		}
		finally
		{
		    try
		    {
		        if ( bw != null)
		        bw.close( );
		    }
		    catch ( IOException ex)
		    {
		    	System.out.println("Erro de I/O");
		    }
		}
		}catch(NullPointerException ex )
		{
			//System.out.println("Erro de I/O");
			return;
		}
		
	}
	
	
	
	/**
	 * Método responsável por gerar a WhishList
	 * 
	 * @param m - Lista de midias cadastradas no sistema
	 * @throws IOException
	 */
	public static void generatorWishList(List<Midia> m)
	{
		Collections.sort(m);
		
		Locale locale = new Locale("pt", "BR");
		NumberFormat numerFormatLocate = NumberFormat.getCurrencyInstance(locale);
		
		FileWriter file;
		try {
			file = new FileWriter("4-wishlist.csv");
		
			PrintWriter saveFile = new PrintWriter(file);
			
			saveFile.println("Tipo;Mídia;Gênero;Preço");
			
			for (Midia midia : m) {
				
				if(midia.isDeseja())
				{
					switch(midia.getType())
					{
						case 'L':	saveFile.println("Livro;"+midia.getNome()+";"+midia.getGenero().getNome()+";"+numerFormatLocate.format(midia.getPreco()));
							break;
						case 'F':	saveFile.println("Filme;"+midia.getNome()+";"+midia.getGenero().getNome()+";"+numerFormatLocate.format(midia.getPreco()));
							break;
						case 'S': saveFile.println("Série;"+midia.getNome()+";"+midia.getGenero().getNome()+";"+numerFormatLocate.format(midia.getPreco()));
							break;
						default:
					}
				}
			
			
			
			}
		file.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			System.out.println("Erro de I/O");
		}
				
	}
	
	/**
	 * Método responsável por gerar as estatisticas do sistema e gravar em um arquivo txt
	 * @param m - Lista de Midias cadastradas no sistema
	 * @param g - Lista de Gêneros cadastrados no sistema
	 */
	public static void generatorEstatisticas(List<Midia> m, Map<String,Genero> g)
	{
		int horasConsumidas = 0;
		int horasConsumir = 0;
		List<Genero> listGenero = new ArrayList<>();
		List<Serie> listSeries = new ArrayList<>();
		Set<String> series = null;
		for (Midia midia : m) {
			
			if(midia.getType() != 'L')
			{				
				if(midia.isConsumiu())
					horasConsumidas += midia.getTamanho();
				if(midia.isDeseja())		
					horasConsumir += midia.getTamanho();					
				if(midia.getType() == 'S')	
					listSeries.add((Serie) midia);		
			}
		}
		
		FileWriter file;
		try {
			file = new FileWriter("1-estatisticas.txt");
			PrintWriter saveFile = new PrintWriter(file);
			saveFile.println("Horas consumidas: "+horasConsumidas+" minutos\nHoras a consumir: "+horasConsumir+" minutos\n");
			saveFile.println("Mídias por gênero:");
			
			// POPULANDO LISTA DE GÊNEROS
			for(Entry<String, Genero> genero: g.entrySet())
			{
				listGenero.add(genero.getValue());
			}
			// ORDENANDO LISTA DE GÊNEROS
			Collections.sort(listGenero);
			//GRAVANDO NO ARQUIVO LISTA DE GÊNEROS
			for (Genero gen : listGenero) {
				saveFile.println("\t"+gen.getNome()+": "+gen.qtdGenero());	
			}
			
			// PARTE DE SÉRIES
			series = FileIO.seriesInv(listSeries);
			saveFile.println("\nTemporadas por série:");			
			for (String string : series) {
				int contAssistida = 0, contAssistir = 0;
				for (Serie s : listSeries) {
					if(s.getNomeSerie().equals(string))
					{
						if(s.isConsumiu())
							contAssistida++;
						else
							contAssistir++;
					}
				}
				saveFile.println("\t"+string+": "+contAssistida+" assistidas, "+contAssistir+" a assistir");
			}
									
			file.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			System.out.println("Erro de I/O");
		}
				
	
	}
	
	/**
	 * Metodo para conferir o nome de todas as series cadastradas no inventário
	 * @param s lista de séries que possuem no inventário
	 * @return	nome das séries que possui no inventário
	 */
	private static Set<String> seriesInv(List<Serie> s)
	{
		Set<String> seriesInventario = new TreeSet<>();
		
		for (Serie serie : s) {
			seriesInventario.add(serie.getNomeSerie());
		}
		
		return seriesInventario;
	}
	
	/**
	 * Metodo para geracao de relatorio de midias por pessoa
	 * @param m lista de midias
	 * @param p lista de pessoas
	 */
	public static void writeMidiaPessoas(List<Midia> m, List<Pessoa> p){
		
		Collections.sort(p);
		BufferedWriter bw = null;
		
		try
		{
		    bw = new BufferedWriter( new FileWriter("2-porpessoa.csv"));
		    bw.write("Pessoa;Produção\n");
		    
		    for(Pessoa pes : p){
		    	
		    	List<String> temp = new LinkedList<String>();
		    	
		    	for(Midia mid : pes.getTrabalhos()){
		    		temp.add(mid.getNome());    	
		    	}
		    	
		    	Collections.sort(temp);
	    		
	    		if(temp.size()>0){
	    			bw.write(pes.getNome()+";");
	    			for(int i=0;i<temp.size()-1;i++){
	    				bw.write(temp.get(i)+", ");
	    			}
	    			bw.write(temp.get(temp.size()-1)+"\n");
	    		}
		    	
		    }
		    
		}
		catch ( IOException ex)
		{
			System.out.println("Erro de I/O");
			return;
		}
		finally
		{
		    try
		    {
		        if ( bw != null)
		        bw.close( );
		    }
		    catch ( IOException ex)
		    {
		    	System.out.println("Erro de I/O");
		    }
		}
		
	}
	

}