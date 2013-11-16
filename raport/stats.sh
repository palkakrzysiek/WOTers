#! /bin/bash
cp ../imgproc imgproc

filename=$1
echo -e "Mean\t`./imgproc -f ${filename} --cmeanh`"
echo -e "Variance\t`./imgproc -f ${filename} --cvariance`"
echo -e "Standard deviation\t`./imgproc -f ${filename} --cstdev`"
echo -e "Variation coefficient I\t`./imgproc -f ${filename} --cvarcoi`"
echo -e "Variation coefficient II\t`./imgproc -f ${filename} --cvarcoii`"
echo -e "Asymmetry coefficient\t`./imgproc -f ${filename} --casyco`"
echo -e "Flattening coefficient\t`./imgproc -f ${filename} --cmeanh`"
echo -e "Information source entropy\t`./imgproc -f ${filename} --centropy`"
