#!/bin/bash

DATA=/home/igor/Documentos/UFES/7/Compiladores/trab4_compiladores
IN=$DATA/in
OUT=$DATA/outSolution

EXE=./trab4

for infile in `ls $IN/*.cm`; do
    base=$(basename $infile)
    dotfile=$OUT/${base/.cm/.dot}
    pdffile=$OUT/${base/.cm/.pdf}
    $EXE < $infile > $dotfile
    dot -Tpdf $dotfile -o $pdffile
done
