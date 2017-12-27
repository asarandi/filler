#!/bin/bash

student='./asarandi.filler'
players='./resources/players/*.filler'
maps='./resources/maps/map0*'
filler_vm='./resources/filler_vm'

seed_start=0
seed_end=5

show_result()
{
	p1=`cat result1.tmp | grep 'launched ' -m1 | tail -n1 | sed 's/launched\ //' | xargs basename`
	p2=`cat result1.tmp | grep 'launched ' -m2 | tail -n1 | sed 's/launched\ //' | xargs basename`
	r1=`cat result1.tmp | grep ' fin: ' -m1 | tail -n1 | sed 's/.*\ fin:\ //'`
	r2=`cat result1.tmp | grep ' fin: ' -m2 | tail -n1 | sed 's/.*\ fin:\ //'`

	echo $p1 vs $p2
	echo result: $r1-$r2
}

for player in $players; do
	for map in $maps; do
		for seed in `seq $seed_start $seed_end`; do
			rm -rf result1.tmp
			$filler_vm -p1 $student -p2 $player -f $map -s $seed -q > result1.tmp
			echo -n map: `basename $map`, 
			echo " seed: $seed"
			show_result
			rm -rf result1.tmp
			$filler_vm -p1 $player -p2 $student -f $map -s $seed -q > result1.tmp
			show_result
			echo ""
		done;
	done;
done;

rm -rf result1.tmp
