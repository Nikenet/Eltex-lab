
#!/bin/bash
nuls='00000000000000000000000000000000'
ones='11111111111111111111111111111111'

if [ -n "$2" ]
then
    varprefix=${2}_
fi

ip=( $( echo $1 | sed 's/[.\/]/ /g') )
ipbin=$(printf "%08d%08d%08d%08d" $(echo "ibase=10;obase=2;${ip[0]};${ip[1]};${ip[2]};${ip[3]};" | bc))
cdir=${ip[4]}

bintoip() {
    addr=($(echo $1 | sed 's/\([01]\{8\}\)\([01]\{8\}\)\([01]\{8\}\)\([01]\{8\}\)/\1 \2 \3 \4/' ))
    echo "obase=10;ibase=2;${addr[0]};${addr[1]};${addr[2]};${addr[3]};" | bc | tr '\n' '.' | cut -d '.' -f 1-4
}


echo ${varprefix}ip=${ip[0]}.${ip[1]}.${ip[2]}.${ip[3]}
echo ${varprefix}cdir=$cdir
echo -n "${varprefix}netmask="
bintoip ${ones:0:$cdir}${nuls:$cdir}
echo -n "${varprefix}netaddr="
bintoip ${ipbin:0:$cdir}${nuls:$cdir}