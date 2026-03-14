#!/bin/sh

# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/hxbj

cp /hxbj/lib/*.so /usr/lib
source /etc/profile
export TERM=linux
echo userspace > /sys/devices/system/cpu/cpufreq/policy0/scaling_governor
echo 1800000 > /sys/devices/system/cpu/cpufreq/policy0/scaling_setspeed
echo userspace > /sys/class/devfreq/fde40000.npu/governor
echo 900000000 > /sys/class/devfreq/fde40000.npu/userspace/set_freq
echo userspace > /sys/class/devfreq/fde60000.gpu/governor
echo 800000000 > /sys/class/devfreq/fde60000.gpu/userspace/set_freq
cd /hxbj
echo "QT Will Start"
chmod +x app2025
./app2025 &

echo "WiFi Will Start"
wpa_supplicant -B -i wlan0 -c /hxbj/wifi.conf

