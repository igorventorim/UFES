import os

itens = os.listdir('./in/')

for item in itens:
	if "." in item:
		os.system("./trab2 < in/"+item+" | diff out2/"+item[:item.find(".")+1]+"out -")