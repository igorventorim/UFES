package com.sample;

import java.util.Scanner;

public class Animal {
	
	private Habitat habitat;
	private Revestimento revestimento;
	private Locomocao locomocao;
	private Reproducao reproducao;
	private Alimentacao alimentacao;
	private Respiracao respiracao;
	
	public Habitat getHabitat() {
		return habitat;
	}

	public void setHabitat(Habitat habitat) {
		this.habitat = habitat;
	}

	public Revestimento getRevestimento() {
		return revestimento;
	}

	public void setRevestimento(Revestimento revestimento) {
		this.revestimento = revestimento;
	}

	public Locomocao getLocomocao() {
		return locomocao;
	}

	public void setLocomocao(Locomocao locomocao) {
		this.locomocao = locomocao;
	}

	public Reproducao getReproducao() {
		return reproducao;
	}

	public void setReproducao(Reproducao reproducao) {
		this.reproducao = reproducao;
	}

	public Alimentacao getAlimentacao() {
		return alimentacao;
	}

	public void setAlimentacao(Alimentacao alimentacao) {
		this.alimentacao = alimentacao;
	}

	public Respiracao getRespiracao() {
		return respiracao;
	}

	public void setRespiracao(Respiracao respiracao) {
		this.respiracao = respiracao;
	}
	
	public void setParameters()
	{
		
		System.out.println("Seja bem vindo");
		System.out.println("Informe o número correspondente a característica escolhida.");
		/* Invocando métodos para setar objeto por UI*/
		uiSetHabitat();
		uiSetRevestimento();
		uiSetLocomocao();
		uiSetReproducao();
		uiSetAlimentacao();
		uiSetRespiracao();
		
		System.out.println("\nFind animal: ["+this.getHabitat().name()+","+this.getRevestimento().name()+","+
		this.getLocomocao().name()+","+this.getReproducao().name()+","+this.getAlimentacao().name()+","+
		this.getRespiracao().name()+"]\n");
		System.out.print("Resultado: ");
	}
	
	public void uiSetHabitat()
	{
		int value;
		Scanner scan = new Scanner(System.in);
		
		System.out.println("\n1 - Aquatico");
		System.out.println("2 - Terrestre");
		System.out.println("3 - Aereo");
		System.out.println("0 - Indetermindado");
		
		System.out.print("Habitat: ");
		value = scan.nextInt();
		
		switch(value)
		{
			case 1:
					this.setHabitat(Habitat.AQUATICO);
					break;
			case 2:
					this.setHabitat(Habitat.TERRESTRE);
					break;
			case 3:
					this.setHabitat(Habitat.AEREO);
					break;
			default:
					this.setHabitat(Habitat.INDETERMINADO);
		}
	}
	
	public void uiSetRevestimento()
	{
		int value;
		Scanner scan = new Scanner(System.in);
		
		System.out.println("\n1 - Escamas");
		System.out.println("2 - Cartilagem");
		System.out.println("3 - Pele");
		System.out.println("4 - Carapaça");
		System.out.println("5 - Pena");
		System.out.println("6 - Pelo");
		System.out.println("0 - Indetermindado");
	
		System.out.print("Revestimento: ");
		value = scan.nextInt();
		switch(value)
		{
			case 1:
					this.setRevestimento(Revestimento.ESCAMAS);
					break;
			case 2:
					this.setRevestimento(Revestimento.CARTILAGEM);
					break;
			case 3:
					this.setRevestimento(Revestimento.PELE);
					break;
					
			case 4:
					this.setRevestimento(Revestimento.CARAPACA);
					break;
					
			case 5:
					this.setRevestimento(Revestimento.PENA);
					break;
					
			case 6:
					this.setRevestimento(Revestimento.PELO);
					break;
					
			default:
					this.setRevestimento(Revestimento.INDETERMINADO);
		}
	}
	
	public void uiSetLocomocao()
	{
		int value;
		Scanner scan = new Scanner(System.in);
		
		System.out.println("\n1 - Nadar");
		System.out.println("2 - Andar");
		System.out.println("3 - Rastejar");
		System.out.println("4 - Voar");
		System.out.println("0 - Indetermindado");
	
		System.out.print("Locomoção: ");
		value = scan.nextInt();
		switch(value)
		{
			case 1:
					this.setLocomocao(Locomocao.NADAR);
					break;
			case 2:
					this.setLocomocao(Locomocao.ANDAR);
					break;
			case 3:
					this.setLocomocao(Locomocao.RASTEJAR);
					break;
					
			case 4:
					this.setLocomocao(Locomocao.VOAR);
					break;
					
			default:
					this.setLocomocao(Locomocao.INDETERMINADO);
		}
	}
	
	public void uiSetReproducao()
	{
		int value;
		Scanner scan = new Scanner(System.in);
		
		System.out.println("\n1 - Ovoliparo");
		System.out.println("2 - Oviparo");
		System.out.println("3 - Viviparo");
		System.out.println("0 - Indetermindado");
		
		System.out.print("Reproducao: ");
		value = scan.nextInt();
		
		switch(value)
		{
			case 1:
					this.setReproducao(Reproducao.OVOLIPARO);
					break;
			case 2:
					this.setReproducao(Reproducao.OVIPARO);
					break;
			case 3:
					this.setReproducao(Reproducao.VIVIPARO);
					break;
			default:
					this.setReproducao(Reproducao.INDETERMINADO);
		}
	}
	
	public void uiSetAlimentacao()
	{
		int value;
		Scanner scan = new Scanner(System.in);
		
		System.out.println("\n1 - Carnivoro");
		System.out.println("2 - Herbivoro");
		System.out.println("0 - Indetermindado");
		
		System.out.print("Alimentação: ");
		value = scan.nextInt();
		
		switch(value)
		{
			case 1:
					this.setAlimentacao(Alimentacao.CARNIVORO);
					break;
			case 2:
					this.setAlimentacao(Alimentacao.HERBIVORO);
					break;

			default:
					this.setAlimentacao(Alimentacao.INDETERMINADO);
		}
	}
	
	public void uiSetRespiracao()
	{
		int value;
		Scanner scan = new Scanner(System.in);
		
		System.out.println("\n1 - Branquial");
		System.out.println("2 - Cutânea");
		System.out.println("3 - Pulmonar");
		System.out.println("0 - Indetermindado");
		
		System.out.print("Respiração: ");
		value = scan.nextInt();
		
		switch(value)
		{
			case 1:
					this.setRespiracao(Respiracao.BRANQUIAL);
					break;
			case 2:
					this.setRespiracao(Respiracao.CUTANEA);
					break;
			case 3:
					this.setRespiracao(Respiracao.PULMONAR);
					break;
			default:
					this.setRespiracao(Respiracao.INDETERMINADO);
		}
	}

	
}
