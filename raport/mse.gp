set terminal png size 1400,1028 enhanced font 'Droid Sans,22pt'
set output 'mse.png'
set title "Mean square error"
set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12
set xtics rotate by 60 right

set style fill solid 1.0 border rgb "black"
p \
'mse.tab' using ($0):2:($0):xtic(1) with boxes lc variable notitle
