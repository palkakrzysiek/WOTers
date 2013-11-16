#! /bin/bash
cp ../imgproc imgproc
    

filter_name="raleigh"
for operation in cmeanh cvariance cstdev cvarcoi cvarcoii casyco cflatco centropy;
do
    echo "" > $filter_name_$operation.tab;
done


filename=${1:0:-4}
#generate images 
for alpha in {0..1500..30};
do
    echo -ne "\nChecking raleigh data, alpha: ${alpha}... "
    for operation in cmeanh cvariance cstdev cvarcoi cvarcoii casyco cflatco;
    do
        ./imgproc -f ${filename}.bmp --channel B --hraleigh $alpha -o ${filename}_raleigh_${alpha}.bmp
        echo -e "$alpha\t`./imgproc --channel B \
            -f ${filename}_raleigh_${alpha}.bmp \
            --$operation`" >> $filter_name_$operation.tab
    done
    echo "Done."

done
