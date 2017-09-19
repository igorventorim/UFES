import os

itens = os.listdir('./in/')

for item in itens:
	if "." in item:
		os.system("./trab4 < in/"+item+" | diff out4/"+item[:item.find(".")+1]+"out -")