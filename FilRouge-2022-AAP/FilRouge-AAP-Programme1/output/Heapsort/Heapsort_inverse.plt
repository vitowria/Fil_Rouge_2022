#---------------------------------------------------------------------+
# Fichier de commandes gnuplot : output/Heapsort/Heapsort_inverse.plt |
#---------------------------------------------------------------------+
#
set style data lines
set xlabel "Nombre d'éléments"
set ylabel "Nombre d'opérations"
set title  "HEAPSORT"
set grid
set terminal png
set output 'output/Heapsort/png/Heapsort_inverse_op.png'
plot 'output/Heapsort/Heapsort_inverse.dat' using 1:2 title 'inverse'
set ylabel "Nombre de comparaisons"
set terminal png
set output 'output/Heapsort/png/Heapsort_inverse_cmp.png'
plot 'output/Heapsort/Heapsort_inverse.dat' using 1:3 title 'inverse'
quit
