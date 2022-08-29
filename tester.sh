#!/bin/bash

make

echo "Press any key to start"
read -rsn1

for map in ./maps/*; do
	clear
	echo "Map: $map"
	cat "$map"
	echo ""
	echo "Press any key to see result"
	read -rsn1
	clear
	echo "Map: $map"
	./a_star "$map"
	echo ""
	echo "Press any key to continue"
	read -rsn1
done

clear
echo "It's over! Hopefully everything has gone right"
