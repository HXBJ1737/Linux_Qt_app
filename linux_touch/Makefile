
all:	
	$(CROSS_COMPILE)gcc -o testdef testdef.c
	$(CROSS_COMPILE)gcc -o touch_test touch_test.c
	$(CROSS_COMPILE)gcc -c -fPIC touch_lib.c -o touch_lib.o
	$(CROSS_COMPILE)gcc -shared -o libtouch.so touch_lib.o




