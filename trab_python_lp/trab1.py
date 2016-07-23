#!/usr/bin/env python
# -'- coding: utf-8 -'-

from Catalogo import Catalogo
from Livro import Livro
from IO import IO

livros = Catalogo()
IO.readCatalogo("catalogo.txt",livros)
IO.readUpdate("atual.txt",livros)
IO.writeOutput(livros)
IO.writeCatalogo("catalogo.txt",livros)