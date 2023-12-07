#!/usr/bin/env bash

# edit the code below and add your code
# отредактируйте код ниже и добавьте свой

# Переменная с номером варианта (константа):
TASKID=3

# Дополнительные переменные (должны вычисляться динамически):
VAR_1=$(cat ./dns-tunneling.log | wc -l)
awk '{print $5}' ./dns-tunneling.log | sort -u -t . -nk 1,1 -nk 2,2 -nk 3,3 -nk 4,4 > results.txt
sec_id=$(sed -n '2p' results.txt)
#echo $sec_id
VAR_2=$(awk '$5~/'$sec_id'/' ./dns-tunneling.log | wc -l)
#echo $VAR_1
#echo $VAR_2
