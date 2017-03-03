import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.TreeMap;

/**
 * 
 * @author igor
 *
 *	Markov Chain
 *
 */
public class MC {
	
	Map<String, ArrayList<Character> > cadeiaMarkov;
	
	/**
	 * Método que constrói a estrutura da cadeia de markov
	 * @param path
	 * @param k
	 */
	public void structsBuild(String path, int k)
	{
		cadeiaMarkov = new HashMap<>();
		String dados = readFile(path);
		ArrayList<Character> ref;
		String key = dados.substring(0,k);
		
		for(int i = k; i < dados.length();i++)
		{
			ref = cadeiaMarkov.get(key.toString());
			char caracter = dados.charAt(i);
			
			if (ref == null)
			{
				ArrayList<Character> novo = new ArrayList<>();
				novo.add(caracter);
				cadeiaMarkov.put(key.toString(), novo);
			}else{ ref.add(caracter); }
			
			key += caracter;
			key = key.substring(1);
					
		}
	}
	
	/**
	 * Método para a escrita aleatória para K > 0
	 * @param l
	 */
	public void write(int l)
	{
		ArrayList<Character> ref;
		Random rn = new Random();
		final int chainLimit = cadeiaMarkov.keySet().size();
		int limit;
		String key = (String)cadeiaMarkov.keySet().toArray()[rn.nextInt(chainLimit)];

		System.out.print(key);
		for(int count = key.length(); count < l; count++)
		{
			ref = cadeiaMarkov.get(key);
			if(ref == null)
			{
				key = (String) cadeiaMarkov.keySet().toArray()[rn.nextInt(chainLimit)];
				ref = cadeiaMarkov.get(key); 
			} 
			limit = ref.size();
			char value =  ref.get(rn.nextInt(limit));
			key += value;
			System.out.print(value);
			key = key.substring(1);
	
		}
		
	}
	
	/**
	 * Método para a escrita aleatória para k = 0
	 * @param path
	 * @param l
	 */
	public void writeNotStruct(String path,int l)
	{
		Random rn = new Random();
		String dados = readFile(path);
		
		for(int i = 0; i < dados.length(); i++)
		{
			System.out.print(dados.charAt(rn.nextInt(dados.length())));
		}
	}
	
	
	/**
	 * Método que efetua a leitura do arquivo
	 * @param path
	 * @return
	 */
	public String readFile(String path)
	{
		try {
			File file = new File(path);
			return new String(Files.readAllBytes(file.toPath())); 
		} catch (IOException e) {
			System.out.println("Erro ao ler o arquivo!");
			return null;
		}
	}
	
	
	// Método principal para executar o algoritmo
	public static void main(String[] args) {
		
		if(args.length == 3)
		{
			MC mc = new MC();
			int k = Integer.parseInt(args[1]);
			
			if(k > 0){
				mc.structsBuild(args[0], Integer.parseInt(args[1]));
				mc.write(Integer.parseInt(args[2]));
			}else{ mc.writeNotStruct(args[0], Integer.parseInt(args[2]));}		
		}else
		{
			System.out.println("Argumentos inválidos, tente novamente! Exemplo: java -jar writeRandom <nome do arquivo> <nivel da analise> <tamanho da saída>");
		}

	}
	
}
