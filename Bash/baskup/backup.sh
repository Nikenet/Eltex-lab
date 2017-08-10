#!/bin/bash

if (($(id -g) != 0)); then
	echo "Permition denied"
	exit 1
fi

sudo echo "Backuper"

. /home/nikenet/Eltex/Bash/baskup/config.config

echo "Path in:  " $PathIn
echo "Path out: " $PathOut

if [[ -d $PathIn ]]; then
	echo "This is directory"
	rsync -a $PathIn $PathOut
	echo "Create crontab's rule"
	crontab -l ; echo "12 0 * * * ./backup.sh " | crontab - #need edit
	crontab -l
	echo "Exit"
	exit 0
fi

if [[ -f $PathIn ]]; then
	echo "This is file"
	tar -cf $PathOut/backup.tar $PathIn
	echo "Create crontab's rule"
	crontab -l ; echo "12 0 * * * ./backup.sh " | crontab - #need edit
	crontab -l
	echo "Exit"
	exit 0
fi

if [[ -b $PathIn ]]; then
	echo "This is external device"
	dd if=$PathIn of=$PathOut/devbackup.img conv=noerror,sync
	echo "Create crontab's rule"
	crontab -l ; echo "12 0 * * * ./backup.sh " | crontab - #need edit
	crontab -l
	echo "Exit"
	exit 0
fi

