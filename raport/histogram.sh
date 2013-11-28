#! /bin/bash
cp ../program1 program1
    
# md.tab: org\t

for operation in mse pmse snr psnr md;
do
    echo "" > $operation.tab
done

#generate images 
for noise in lena_impulse lena_normal lena_uniform;
do
    echo "File: $noise.bmp"
    ./program1 -f lena_original.bmp --md "${noise}.bmp"
    for operation in mse pmse snr psnr md;
    do
    echo -e "\"${noise:5} original\"\t `./program1 -f lena_original.bmp --$operation \
        ${noise}.bmp`" >> $operation.tab
    done
    echo "Generating alpha images"
    for alpha in 0 2 4 6 8;
    do
        ./program1 -f $noise.bmp --alpha $alpha -o ${noise}_alpha${alpha}.bmp
        for operation in mse pmse snr psnr md;
        do
        echo -e "\"${noise:5} aplha $alpha\"\t`./program1 -f lena_original.bmp --$operation \
        ${noise}_alpha${alpha}.bmp`" >> $operation.tab
        done 
        
    done

    echo "Generating cmean images"
    for Q in "-3" "-1" 0 "0.5" 1 3;
    do
        ./program1 -f $noise.bmp --cmean $Q -o ${noise}_cmean${Q}.bmp
        for operation in mse pmse snr psnr md;
        do
        echo -e "\"${noise:5} cmean $Q\"\t`./program1 -f lena_original.bmp --$operation \
        ${noise}_cmean${Q}.bmp`" >> $operation.tab
        done
    done

    echo "Generating double cmean images"
    for Q in 2 5;
    do
        ./program1 -f $noise.bmp --cmean -$Q -o temp.bmp
        ./program1 -f temp.bmp --cmean $Q -o ${noise}_mcmean${Q}.bmp
        for operation in mse pmse snr psnr md;
        do
        echo -e "\"${noise:5} mcmean $Q\"\t`./program1 -f lena_original.bmp --$operation \
        ${noise}_mcmean${Q}.bmp`" >> $operation.tab
        done
    done
    echo "Done."
done

