#---------------------------------------------------------------------+
# Fichier de commandes gnuplot : output/Heapsort/Heapsort_ordonne.plt |
#---------------------------------------------------------------------+
#
set style data lines
set xlabel "Nombre d'éléments"
set ylabel "Nombre d'opérations"
set title  "HEAPSORT"
set grid
set terminal png
set output 'output/Heapsort/png/Heapsort_ordonne_op.png'
plot 'output/Heapsort/Heapsort_ordonne.dat' using 1:2 title 'ordonne'
set ylabel "Nombre de comparaisons"
set terminal png
set output 'output/Heapsort/png/Heapsort_ordonne_cmp.png'
plot 'output/Heapsort/Heapsort_ordonne.dat' using 1:3 title 'ordonne'
quit
