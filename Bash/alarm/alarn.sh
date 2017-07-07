#!/bin/bash

echo "What time you should the alarm go? (HH:MM)"
read target

#convert targetdata in second
target_h=`echo $target | awk -F: '{print $1}'`
target_m=`echo $target | awk -F: '{print $2}'`

# dc - an arbitrary precision calculator
target_s=`dc -e "$target_h 60 60 ** $target_m 60 *+p"`

#convert systemdata in second
clock=`date | awk '{print $4}'`
clock_h=`echo $clock | awk -F: '{print $1}'`
clock_m=`echo $clock | awk -F: '{print $2}'`
clock_s=`echo $clock | awk -F: '{print $3}'`
clock_s=`dc -e "$clock_h 60 60 ** $clock_m 60 * $clock_s ++p"`

#whaiting targetdata
sec_until=`dc -e "24 60 60 **d $target_s $clock_s -+r%p"`
echo "Whaiting alarm data."

sleep $sec_until
mpg321 Gorillaz\ -\ Saturnz\ Barz.mp3
