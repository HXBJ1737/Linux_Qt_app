#!/bin/sh


source /etc/profile
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/hxbj
cd /hxbj
echo "QT Will Start"
./app2025 &
echo "WiFi Will Start"
wpa_supplicant -B -i wlan0 -c /hxbj/wifi.conf
