#!/bin/sh


source /etc/profile
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/hxbj
cd /hxbj
echo "QT(app2025) Will Start"
./app2025 &

