#!/bin/sh

cp /hxbj/weston.ini /etc/xdg/weston/weston.ini
echo "Successfully replaced weston.ini"

cp /hxbj/rcS /etc/init.d/
echo "Successfully replaced rcS"

ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
echo "Successfully Set Time"

echo "Please reboot to take effects"
#echo "OS will reboot"
# reboot
