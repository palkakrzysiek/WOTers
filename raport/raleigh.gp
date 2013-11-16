set terminal png size 1400,1028 enhanced font 'Droid Sans,22pt'
set output 'raleigh.png'
set title "Raleigh Filter"
set xlabel "{/Symbol a} coefficient"
set ylabel "Standard deviation"
set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12
set xtics rotate by 60 right


p \
'cstdev.tab' using 1:2 with lines lw 3 title 'Standard deviation'
