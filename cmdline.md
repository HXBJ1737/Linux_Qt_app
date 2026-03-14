
GPU温度

    cat /sys/class/thermal/thermal_zone1/temp

CPU温度

    cat /sys/class/thermal/thermal_zone0/temp

设置cpu定频为定频模式userspace

    echo userspace > /sys/devices/system/cpu/cpufreq/policy0/scaling_governor

设置npu定频为定频模式userspace

    echo userspace > /sys/class/devfreq/fde40000.npu/governor

设置gpu定频为定频模式userspace

    echo userspace > /sys/class/devfreq/fde60000.gpu/governor

设置gpu频率（可选 800000000 700000000 600000000 400000000 300000000 200000000）

    echo 800000000 > /sys/class/devfreq/fde60000.gpu/userspace/set_freq

设置NPU频率（可选 200000000 297000000 400000000 600000000 700000000 800000000 900000000）
   
    echo 900000000 > /sys/class/devfreq/fde40000.npu/userspace/set_freq

设置CPU频率（可选408000 600000 816000 1104000 1416000 1608000 1800000）

    echo 1800000 > /sys/devices/system/cpu/cpufreq/policy0/scaling_setspeed

NPU占用

    cat /sys/kernel/debug/rknpu/load

DDR带宽占用率
    
    cat /sys/devices/platform/dmc/devfreq/dmc/load

截屏

    weston-screenshooter

