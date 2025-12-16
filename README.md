# Linux_Qt5_Camera

## 此分支scr_6i 适用于 6寸 & 固定分辨率1280x720
## 一、Window编译方法
    使用VSCode或Qtcreater可直接编译（需要Qt环境搭建）
## 二、Linux交叉编译ARM版编译方法
    以泰山派RK3566+buildroot系统为例
    主机为VMware：Ubuntu22.04
## 0.buildroot添加Qt
### ！！！注意要用到项目 conf 文件夹下图片上标明的的库，请在编译buildroot文件系统时勾选，添加Qt5参考立创开发板文章 
    https://wiki.lckfb.com/zh-hans/tspi-rk3566/documentation/transplant-qt5.html
## 1.获取工程+配置环境变量
    git clone https://github.com/HXBJ1737/Linux_Qt_app
    export ARCH=arm64
    export CROSS_COMPILE=aarch64-rockchip-linux-gnu-
    export PATH=$PATH:/home/hxbj/tspi/linux_sdk/prebuilts/gcc/linux-x86/aarch64/gcc-buildroot-9.3.0-2020.03-x86_64_aarch64-rockchip-linux-gnu/bin
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/hxbj/tspi/linux_sdk/prebuilts/gcc/linux-x86/aarch64/gcc-buildroot-9.3.0-2020.03-x86_64_aarch64-rockchip-linux-gnu/lib
    export PATH=$PATH:/home/hxbj/tspi/linux_sdk/buildroot/output/rockchip_rk3566/host/bin
    ## 注意路径换成自己的，并且后续操作使用这一个终端
## 2.交叉编译库文件libtouch
#### (tips：由于某种未知原因，泰山派(ARM Linux)打开照相机应用后需要手动触摸一下屏幕才会开始显示摄像头画面，先尝试用Qt自带的模拟触摸或鼠标事件，没用，故使用Linux的uinput产生系统级原生触摸事件，来模拟手动点击刷新)
#### 也可以直接使用我编译好的libtouch.so(位于项目linux_touch下)
    cd linux_touch
    make
    ## 如果步骤1操作成功，可以看到make后输出的编译器是aarch64-rockchip-linux-gnu-gcc ，不是gcc.
    cp libtouch ../

## 3.交叉编译此Qt项目
    cd ../      #cd到工程根目录
    qmake app2025.pro   #若提示找不到qmake，看步骤1配置环境变量。
    make
## 4.上传文件至ARM开发板（以泰山派为例）
### 4.1方法一：编译进文件系统在重新烧录rootfs.img
    将项目中的 hxbj 文件夹复制到linux_sdk/buildroot/board/rockchip/common/base下
    (hxbj文件夹里面是我编译后的app2025和libtouch.so和后面用到的自启动脚本,你可以换成你刚才编译的)

    cd 到你的LinuxSDK目录
    ./build.sh rootfs   
    # 然后重新烧录rootfs.img
   

### 4.2方法二：直接上传至开发板
#### 我使用ADB，以此为例
    adb shell
    cd /
    mkdir hxbj

#### 再开一个终端
    adb push "Z:\Qt_projects\app2025\app2025" /hxbj
    adb push "Z:\Qt_projects\app2025\linux_touch\libtouch\libtouch.so" /hxbj
    ## 以此为例，将项目hxbj文件夹下的其他文件的也上传到开发板
## 5.运行
### 现在开发板hxbj目录下有这些文件
    QDesktop 正点原子例程可执行文件
    b.jpg    背景图片
    libtouch.so  模拟触摸动态库
    src          音视频图资源 
    wifi.conf     wifi配置
    app2025       此项目可执行文件
    cam_app1      此项目旧版可执行文件(可以弃用删除)
    rtsp.sh       ffmpeg推流测试
    start_app2025.sh  app2025启动脚本
    auto.sh           app2025启动+wifi连接脚本
    camera_demo       相机Demo
    saveimg           相册存储目录
    video.sh          ffmpeg推流+屏幕显示测试
    weston.ini        桌面配置文件
    
### 5.1.简单运行
    ./start_app2025.sh
### 5.2进一步配置（全屏+旋转屏幕）
    vi /etc/xdg/weston/weston.ini
    ## 对照/hxbj/weston.ini，将/etc/xdg/weston/weston.ini改成和/hxbj/weston.ini一样的
### 5.3开机自启动
    vi /etc/init.d/rcS
    在最后一行加上 /hxbj/auto.sh 
### 5.4将上述文件操作都编译进rootfs.img
#### linux_sdk/buildroot/board/rockchip/common/base下的文件会在编译rootfs.img时编译追加进文件系统，这在menuconfig中已经配置，称为overlay目录或文件。
    故在步骤4的方法一中，
    也可以在linux_sdk/buildroot/board/rockchip/common/base下
    创建etc/xdg/weston/weston.ini,并修改内容
    创建etc/init.d/rcS,并追加内容，
    然后重新编译rootfs.img烧录值开发板即可。
## 6.问题解答
### 6.1摄像头无法显示，参考 https://hx.sn.cn/archives/L2R8QU6o 解决
## 欢迎讨论 QQ：2437224636


