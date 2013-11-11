set terminal pngcairo size 1400,1028 enhanced font 'Droid Sans,22pt'
set output 'contrast_factor.png'
set title "Contrast factor"
set xlabel "{/Italic c} coefficient"
set ylabel "Value of contrast factor"
set key left top Left box 0
set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12


p [-255:255] (259.0 * (x + 255.0)) / (255.0 * (259.0 -x)) lw 3 title "contrast factor"
