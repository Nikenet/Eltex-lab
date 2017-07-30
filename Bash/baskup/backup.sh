#!/bin/bash

sudo echo "Вы запустили backuper scrypt"
config.sh

while getopt "a:s:d:t"
do
	case $Options in
	esac

sudo dd if=$target of=/home/nikenet/Eltex/Bash/backup/backup.img conv=noerror,sync 

sudo tar -cf ~$target
mkdir backup
rsync -a $target backup/