#/bin/bash

if [ ! -f "image.bmp" ]; then
    echo "copy any image with name 'image.bmp' to folder with this script"
    exist 1
fi

operation=$1
if [ -z $operation ]; then
    operation="all"
fi

echo $operation
program_name=program1_st
gnuplot_file=graph.gp
    
if [ $operation = clean ]; then
    rm img_*
    rm *.log
    echo "Done."
    rm $gnuplot_file
    rm img_original.jpg
    rm out.bmp
    rm $program_name
    exit
fi

from=$2
if [ -z $from ]; then
    from=100
fi
to=$3
if [ -z $3 ]; then
    to=1500
fi
range="$from $to"
echo "Range form $from to $to"

cd ..
make clean_compilation_type
make speed_test
mv $program_name benchmark/$program_name
cd benchmark


convert image.bmp -resize 100x100 img_original.jpg

echo "Generating temporary images..."
for i in `LANG="en_us" seq $range`
do
    echo -ne "Element $i / $to\t$(( (($i - $from) * 100) / ($to-$from) ))%                 \r"
    if [ -f img_$i.jpg ]; then
        echo -ne "img_$i.jpg exist, skipping                            \r"
    else
        convert img_original.jpg -resize $i% img_$i.jpg
    fi
done
echo -e "\nDone."

echo -e "set terminal pngcairo size 1400,1028 enhanced font 'Droid Sans,22pt'" > $gnuplot_file
echo -e "set output 'graph.png' \n\
set title \"Time of operations\" \n\
set format x \"%.1t×10^{%01T}\" \n\
set xlabel \"Number of pixels\" \n\
set format y \"%.1t×10^{%01T}\" \n\
set style line 11 lc rgb '#808080' lt 1 \n\
set border 3 back ls 11 \n\
set tics nomirror \n\
set style line 12 lc rgb '#808080' lt 0 lw 1 \n\
set grid back ls 12 \n\
set ylabel \"Time of the operation [s]\"" >> $gnuplot_file


if [ $operation = "vflip" ] || [ $operation = "all" ]; then
    echo "Testing --Vflip operation..."
    echo -n "" > vflip.log
    for i in `LANG="en_us" seq $range`
    do
        echo -ne "Element $i / $to\t$(( (($i - $from) * 100) / ($to-$from) ))%                 \r"
        echo -ne "$i\t" >> vflip.log
        prog_out=`./$program_name -r 150 -f img_$i.jpg`
        prog_out=${prog_out//s/} # remove 's' form string
        echo -ne "$prog_out\n" >> vflip.log
    done
    echo -e "\nDone."
    echo -n "plot [$(( $from * $from )):$(( $to * $to ))] \
'vflip.log' using (\$1 * \$1):2 with points pt 13 lc rgb '#771212' ps 1 title 'Vertical Flip \
(measured points) ', \
'vflip.log' using (\$1 * \$1):2 smooth sbezier lc rgb '#771212' lw 5 title 'Vertical Flip \
(approximation)'" >> $gnuplot_file
fi



gnuplot $gnuplot_file
