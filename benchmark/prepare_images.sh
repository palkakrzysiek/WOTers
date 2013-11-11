#/bin/bash

for i in `LANG="en_us" seq 1 290`
do
  convert img_original.jpg -resize $i% img_$i.jpg
done
