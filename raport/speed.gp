set terminal pngcairo size 1400,1028 enhanced font 'Droid Sans,22pt'
set output 'speed.png'
set title "Comparison of time complexity of Alpha-trimmed mean filter and Contraharmonic mean filter"
set xlabel "Number of pixels"
set ylabel "Time of operations [s]"
set format x '%.1t×10^{%01T}'
set format y '%.1f'
set key left top Left box 0
set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12
a(x) = a*x + b
fit a(x) 'alpha.log' using ($1 * $1):2 via a,b
c(x) = d*x + e
fit c(x) 'cmean.log' using ($1 * $1):2 via d,e

p [0: 1500*1500] \
'alpha.log' using ($1 * $1):2 with points pt 1 lc rgb '#771212' ps 1 title 'Alpha-trimmed mean filter', \
a(x) lc rgb '#771212' lw 5 title 'Alpha-trimmed mean filter (approximation)', \
'cmean.log' using ($1 * $1):2 with points pt 1 lc rgb '#181898' ps 1 title 'Contraharmonic mean filter', \
c(x) lc rgb '#181898' lw 5 title 'Contraharmonic mean filter (approximation)'

