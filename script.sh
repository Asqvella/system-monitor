#!/bin/bash
hdd_temp=$(sudo hddtemp /dev/your_hdd | awk '{print $4}' |  rev | cut -c 4- | rev)
time=$(cat /proc/uptime | awk '{print $1}' | cut -f1 -d.)
ram=$(free | grep -i 'mem' | awk '{print ($2-$7)*100/$2}' | cut -f1 -d.)
hdd=$(df | grep -i '/dev/sda1' | awk '{print $5}' | cut -f1 -d%)
cpu=$(mpstat | grep -i 'all' | awk '{print $3}'| cut -f1 -d,)
cpu_temp=$(sensors | grep -i 'cpu temperature' | awk '{print $3}'| cut -f1 -d.|cut -c 2-)
traffic=$(($(ifconfig your_network | grep -i 'RX bytes:' | awk '{print  $2}' | cut -c 7-)/1000000))
mb_temp=$(sensors | grep -i 'mb temperature' | awk '{print $3}'| cut -f1 -d.|cut -c 2-)
echo $time $traffic $ram $hdd $cpu $cpu_temp $hdd_temp $mb_temp



