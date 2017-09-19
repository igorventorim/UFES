import os

itens = os.listdir('./in/')

for item in itens:
	if "." in item:
		os.system("./trab3 < in/"+item+" | diff out3/"+item[:item.find(".")+1]+"out -")