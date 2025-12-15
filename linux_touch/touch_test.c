
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>

static int touch_fd = -1;

void touch_init() {
    touch_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (touch_fd < 0) {
        perror("open uinput");
        return;
    }
    
    ioctl(touch_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(touch_fd, UI_SET_KEYBIT, BTN_TOUCH);
    ioctl(touch_fd, UI_SET_EVBIT, EV_ABS);
    ioctl(touch_fd, UI_SET_ABSBIT, ABS_X);
    ioctl(touch_fd, UI_SET_ABSBIT, ABS_Y);
    
    struct uinput_abs_setup abs = {0};
    abs.code = ABS_X;
    abs.absinfo.minimum = 0;
    abs.absinfo.maximum = 1280;
    ioctl(touch_fd, UI_ABS_SETUP, &abs);
    
    abs.code = ABS_Y;
    abs.absinfo.maximum = 720;
    ioctl(touch_fd, UI_ABS_SETUP, &abs);
    
    struct uinput_setup setup = {0};
    setup.id.bustype = BUS_USB;
    strcpy(setup.name, "Qt Touch Device");
    ioctl(touch_fd, UI_DEV_SETUP, &setup);
    ioctl(touch_fd, UI_DEV_CREATE);
    
    sleep(1);
}

void touch_simulate(int x, int y) {
    if (touch_fd < 0) return;
    
    struct input_event ev;
    
    // 移动到位置
    ev.type = EV_ABS;
    ev.code = ABS_X;
    ev.value = x;
    write(touch_fd, &ev, sizeof(ev));
    
    ev.code = ABS_Y;
    ev.value = y;
    write(touch_fd, &ev, sizeof(ev));
    
    ev.type = EV_SYN;
    ev.code = SYN_REPORT;
    ev.value = 0;
    write(touch_fd, &ev, sizeof(ev));
    
    // 按下
    ev.type = EV_KEY;
    ev.code = BTN_TOUCH;
    ev.value = 1;
    write(touch_fd, &ev, sizeof(ev));
    
    ev.type = EV_SYN;
    ev.code = SYN_REPORT;
    ev.value = 0;
    write(touch_fd, &ev, sizeof(ev));
    
    usleep(1000);  // 1ms
    
    // 释放
    ev.type = EV_KEY;
    ev.code = BTN_TOUCH;
    ev.value = 0;
    write(touch_fd, &ev, sizeof(ev));
    
    ev.type = EV_SYN;
    ev.code = SYN_REPORT;
    ev.value = 0;
    write(touch_fd, &ev, sizeof(ev));
    printf("111222");
}

void touch_cleanup() {
    if (touch_fd >= 0) {
        ioctl(touch_fd, UI_DEV_DESTROY);
        close(touch_fd);
        touch_fd = -1;
    }
}

int main()
{
	touch_init();
	touch_simulate(255,255);
	touch_cleanup();
}
