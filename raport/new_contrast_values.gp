set terminal pngcairo size 1400,1028 enhanced font 'Droid Sans,22pt'
set output 'new_contrast_values.png'
set title "New intensity values"
set xlabel "Old values"
set ylabel "New values"
set key left top Left title 'Legend' box 0
set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12


p [0:255] [0:255] (x - 128) * ((259.0 * (-200 + 255.0)) / (255.0 * (259.0 + 200))) + 128 lw 3 title "{/Italic c}= -200", \
(x - 128) * ((259.0 * (-128 + 255.0)) / (255.0 * (259.0 + 128))) + 128 lw 3 title "{/Italic c} = -128", \
(x - 128) * ((259.0 * (-60 + 255.0)) / (255.0 * (259.0 + 60))) + 128 lw 3 title "{/Italic c} = -60", \
(x - 128) * ((259.0 * (60 + 255.0)) / (255.0 * (259.0 - 60))) + 128 lw 3 title "{/Italic c} = 60", \
(x - 128) * ((259.0 * (128 + 255.0)) / (255.0 * (259.0 - 128))) + 128 lw 3 title "{/Italic c} = 128", \
(x - 128) * ((259.0 * (200 + 255.0)) / (255.0 * (259.0 - 200))) + 128 lw 3 title "{/Italic c} = 200"

