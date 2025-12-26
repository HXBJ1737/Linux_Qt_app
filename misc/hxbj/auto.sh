#!/bin/sh

# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/hxbj
cp /hxbj/lib/*.so /usr/lib
source /etc/profile

cd /hxbj
echo "QT Will Start"
./app2025 &

echo "WiFi Will Start"
wpa_supplicant -B -i wlan0 -c /hxbj/wifi.conf

