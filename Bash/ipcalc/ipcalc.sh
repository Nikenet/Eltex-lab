#!/bin/bash

echo "You run IP calculator"

echo ""
echo "Enter IP, syntax: <***.***.***.***>"
read ip
echo "Enter mask, syntax: <***.***.***.***>"
read mask

ip1=`echo $ip | awk -F. '{print $1}'`
ip2=`echo $ip | awk -F. '{print $2}'`
ip3=`echo $ip | awk -F. '{print $3}'`
ip4=`echo $ip | awk -F. '{print $4}'`

mask1=`echo $mask | awk -F. '{print $1}'`
mask2=`echo $mask | awk -F. '{print $2}'`
mask3=`echo $mask | awk -F. '{print $3}'`
mask4=`echo $mask | awk -F. '{print $4}'`

wildcard1=$((255-$mask1))
wildcard2=$((255-$mask2))
wildcard3=$((255-$mask3))
wildcard4=$((255-$mask4))

D2B=({0..1}{0..1}{0..1}{0..1}{0..1}{0..1}{0..1}{0..1})

ip1=${D2B[$ip1]}
ip2=${D2B[$ip2]}
ip3=${D2B[$ip3]}
ip4=${D2B[$ip4]}

mask1=${D2B[$mask1]}
mask2=${D2B[$mask2]}
mask3=${D2B[$mask3]}
mask4=${D2B[$mask4]}

wildcard1=${D2B[$wildcard1]}
wildcard2=${D2B[$wildcard2]}
wildcard3=${D2B[$wildcard3]}
wildcard4=${D2B[$wildcard4]}

a1="$ip1"
a2="$ip2"
a3="$ip3"
a4="$ip4"

b1="$wildcard1"
b2="$wildcard2"
b3="$wildcard3"
b4="$wildcard4"

out1=""
out2=""
out3=""
out4=""

for ((i=0; i < ${#a1}; i++ )); do
   out1=${out1}$((${a1:$i:1} ^ ${b1:$i:1}))
done

for ((i=0; i < ${#a2}; i++ )); do
   out2=${out2}$((${a2:$i:1} ^ ${b2:$i:1}))
done

for ((i=0; i < ${#a3}; i++ )); do
   out3=${out3}$((${a3:$i:1} ^ ${b3:$i:1}))
done

for ((i=0; i < ${#a4}; i++ )); do
   out4=${out4}$((${a4:$i:1} ^ ${b4:$i:1}))
done

nout1=`echo "ibase=2;$out1" | bc`
nout2=`echo "ibase=2;$out2" | bc`
nout3=`echo "ibase=2;$out3" | bc`
nout4=`echo "ibase=2;$out4" | bc`

c1="$ip1"
c2="$ip2"
c3="$ip3"
c4="$ip4"

d1="$mask1"
d2="$mask2"
d3="$mask3"
d4="$mask4"

o1=""
o2=""
o3=""
o4=""

nw1=""
nw2=""
nw3=""
nw4=""

for ((i=0; i < ${#c1}; i++ )); do
   o1=${o1}$((${c1:$i:1} & ${d1:$i:1}))
done

for ((i=0; i < ${#c2}; i++ )); do
   o2=${o2}$((${c2:$i:1} & ${d2:$i:1}))
done

for ((i=0; i < ${#c3}; i++ )); do
   o3=${o3}$((${c3:$i:1} & ${d3:$i:1}))
done

for ((i=0; i < ${#c4}; i++ )); do
   o4=${o4}$((${c4:$i:1} & ${d4:$i:1}))
done

nout1=`echo "ibase=2;$out1" | bc`
nout2=`echo "ibase=2;$out2" | bc`
nout3=`echo "ibase=2;$out3" | bc`
nout4=`echo "ibase=2;$out4" | bc`

no1=`echo "ibase=2;$o1" | bc`
no2=`echo "ibase=2;$o2" | bc`
no3=`echo "ibase=2;$o3" | bc`
no4=`echo "ibase=2;$o4" | bc`

nw1=`echo "ibase=2;$wildcard1" | bc`
nw2=`echo "ibase=2;$wildcard2" | bc`
nw3=`echo "ibase=2;$wildcard3" | bc`
nw4=`echo "ibase=2;$wildcard4" | bc`

net1="$ip1"
net2="$ip2"
net3="$ip3"
net4="$ip4"

wil1="$wildcard1"
wil2="$wildcard2"
wil3="$wildcard3"
wil4="$wildcard4"

wout1=""
wout2=""
wout3=""
wout4=""

for ((i=0; i < ${#net1}; i++ )); do
   wout1=${wout1}$((${net1:$i:1} & ${wil1:$i:1}))
done

for ((i=0; i < ${#net2}; i++ )); do
   wout2=${wout2}$((${net2:$i:1} & ${wil2:$i:1}))
done

for ((i=0; i < ${#net3}; i++ )); do
   wout3=${wout3}$((${net3:$i:1} & ${wil3:$i:1}))
done

for ((i=0; i < ${#net4}; i++ )); do
   wout4=${wout4}$((${net4:$i:1} & ${wil4:$i:1}))
done

nwout1=`echo "ibase=2;$wout1" | bc`
nwout2=`echo "ibase=2;$wout2" | bc`
nwout3=`echo "ibase=2;$wout3" | bc`
nwout4=`echo "ibase=2;$wout4" | bc`

echo ""
echo "IP: decimal: $ip binary: $ip1.$ip2.$ip3.$ip4"
echo "MASK: decimal: $mask binary: $mask1.$mask2.$mask3.$mask4"
echo "WILDCARD: decimal: $nw1.$nw2.$nw3.$nw4 binary: $wildcard1.$wildcard2.$wildcard3.$wildcard4"
echo ""

echo "NETWORK: decimal: $no1.$no2.$no3.$no4 binary: $o1.$o2.$o3.$o4"
echo "BROADCAST: decimal: $nout1.$nout2.$nout3.$(($nout4+1)) binary: $out1.$out2.$out3.$(($out4+00000001))"
echo "MAXHOST: decimal: $nout1.$nout2.$nout3.$nout4 binary: $out1.$out2.$out3.$out4"
