#!/bin/bash

echo "Lancement..."
v=5
h=35
m=1

for i in $(seq 1 $h)
do
#gnome-terminal -- run
./bin/p2p_test $((3000 + $i)) $v 127.0.0.1:8080 127.0.0.1:8081> /dev/null &
done
echo "$h noeuds honnete lancé !"

for i in $(seq 1 $m)
do
#gnome-terminal -- run
./bin/p2p_test_m $((3000 + $i + $h)) $v 127.0.0.1:8080 127.0.0.1:8081> /dev/null &
done
echo "$m noeuds malicieux lancé !"


wait
echo "Terminé !"
