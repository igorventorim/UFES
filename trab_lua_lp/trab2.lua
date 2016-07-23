-- SCRIPT PRINCIPAL 
-- Script principal responsável por realizar todas as chamadas para rodar o programa
-- @AUTHOR IGOR VENTORIM
-- DATE BEGIN: 04/30/2016
-- package.path = package.path .. ';/?.lua'
-- local Util = require("Util")
dofile("Catalogo.lua")
dofile("Util.lua")

local l = Catalogo()
readCatalogo("catalogo.txt",l)
readUpdate("atual.txt",l)
writeOutput(l)
writeCatalogo("catalogo.txt",l)

