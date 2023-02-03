#-----------------------------------------------------------------------+
# Fichier de commandes gnuplot : output/Heapsort/Heapsort_aleatoire.plt |
#-----------------------------------------------------------------------+
#
set style data lines
set xlabel "Nombre d'éléments"
set ylabel "Nombre d'opérations"
set title  "HEAPSORT"
set grid
set terminal png
set output 'output/Heapsort/png/Heapsort_aleatoire_op.png'
plot 'output/Heapsort/Heapsort_aleatoire.dat' using 1:2 title 'aleatoire'
set ylabel "Nombre de comparaisons"
set terminal png
set output 'output/Heapsort/png/Heapsort_aleatoire_cmp.png'
plot 'output/Heapsort/Heapsort_aleatoire.dat' using 1:3 title 'aleatoire'
quit
