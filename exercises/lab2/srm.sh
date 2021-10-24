#!/bin/bash

BASK=~/basket
counter=0

if [ -d BASK ]; then
	echo "Folder already exists"
else
	mkdir $BASK
	if ! [ -d BASK ]; then
		echo "Folder successfully created"
	else
		echo "Folder could not created"
	fi
fi

for i in $@ #With this for loop you can remove more than 1 file										
do
	if [ -e $i ]; then
		mv $i $BASK
		if [ -e $i ]; then
			echo "$i could not removed"
		else
			echo "$i successfully removed"
			let "counter+=1"
		fi
	else
		echo "There is no such file: $i"
	fi
done

echo "$counter files successfully removed"