
ARCH=arm64
CROSS_COMPILE=aarch64-rockchip-linux-gnu-
PATH=$PATH:/home/hxbj/tspi/linux_sdk/prebuilts/gcc/linux-x86/aarch64/gcc-buildroot-9.3.0-2020.03-x86_64_aarch64-rockchip-linux-gnu/bin

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/hxbj/tspi/linux_sdk/prebuilts/gcc/linux-x86/aarch64/gcc-buildroot-9.3.0-2020.03-x86_64_aarch64-rockchip-linux-gnu/lib
KERN_DIR = /home/hxbj/tspi/linux_sdk/kernel

all:	
	$(CROSS_COMPILE)gcc -o testdef testdef.c
	$(CROSS_COMPILE)gcc -o touch_test touch_test.c
	$(CROSS_COMPILE)gcc -c -fPIC touch_lib.c -o touch_lib.o
	$(CROSS_COMPILE)gcc -shared -o libtouch.so touch_lib.o




