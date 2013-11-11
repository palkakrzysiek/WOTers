#/bin/bash

# version without openmp
for i in `LANG="en_us" seq 1 290`
do
	echo -ne "$i/2900\r"
  ./noomp b img_$i.jpg >> noomp_b_$i.log
done

echo

for i in `LANG="en_us" seq 1 290`
do
	echo -ne "$((i+290))/2900\r"
  ./noomp c img_$i.jpg >> noomp_c_$i.log
done

echo

for i in `LANG="en_us" seq 1 290`
do
	echo -ne "$((i+600))/2900\r"
  ./noomp n img_$i.jpg >> noomp_n_$i.log
done

echo

for i in `LANG="en_us" seq 1 290`
do
	echo -ne "$((i+900))/2900\r"
  ./noomp h img_$i.jpg >> noomp_h_$i.log
done

echo

for i in `LANG="en_us" seq 1 290`
do
	echo -ne "$((i+1200))/2900\r"
  ./noomp v img_$i.jpg >> noomp_v_$i.log
done

echo

####
# open mp version

for i in `LANG="en_us" seq 1 290`
do
	echo -ne "$((i+1500))/2900\r"
  ./omp b img_$i.jpg >> omp_b_$i.log
done

echo

for i in `LANG="en_us" seq 1 290`
do
	echo -ne "$((i+1800))/2900\r"
  ./omp c img_$i.jpg >> omp_c_$i.log
done

echo

for i in `LANG="en_us" seq 1 290`
do
	echo -ne "$((i+2100))/2900\r"
  ./omp n img_$i.jpg >> omp_n_$i.log
done

echo

for i in `LANG="en_us" seq 1 290`
do
	echo -ne "$((i+2400))/2900\r"
  ./omp h img_$i.jpg >> omp_h_$i.log
done

echo

for i in `LANG="en_us" seq 1 290`
do
	echo -ne "$((i+2700))/2900\r"
  ./omp v img_$i.jpg >> omp_v_$i.log
done
