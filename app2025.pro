QT += core gui widgets multimedia multimediawidgets virtualkeyboard

CONFIG += c++17
win32-msvc*:QMAKE_CXXFLAGS += /utf-8

SOURCES += \
    src/main.cpp \
    src/index/app2025.cpp \
    src/cam/cam.cpp \
    src/gallery/gallery.cpp \
    src/test/test.cpp \
    
    

HEADERS += \
    src/index/app2025.h \
    src/cam/cam.h \
    src/gallery/gallery.h \
    src/test/test.h \
    
   

FORMS +=  \
    src/distance/distance.ui \
    src/distance/usage.ui \
    src/index/app2025.ui \
    src/cam/cam.ui \
    src/gallery/gallery.ui \
    src/test/test.ui \
    src/yoloapp/yolo_app.ui \

RESOURCES += \
    img.qrc

linux{
    # ====== RK3568 交叉编译配置 ======
    TARGET_SOC = rk356x
    MAKE_SYSTEM_NAME = Linux
    MAKE_SYSTEM_PROCESSOR = aarch64
    CONFIG += release
    
 # 交叉编译工具链路径
    RK356X_TOOLCHAIN_PATH = /home/hxbj/tspi/linux_sdk/buildroot/output/rockchip_rk3566/host/bin
    RK356X_SYSROOT = /home/hxbj/tspi/linux_sdk/buildroot/output/rockchip_rk3566/host/aarch64-buildroot-linux-gnu/sysroot

SOURCES += \
    yolo11/cpp/rknpu2/yolo11.cc \
    yolo11/cpp/postprocess.cc \
    yolo11/utils/image_utils.c \
    yolo11/utils/file_utils.c \
    yolo11/utils/image_drawing.c \
    src/distance/distance.cpp \
    src/yoloapp/yolo_app.cpp \
    src/distance/usage.cpp \

HEADERS += \
    yolo11/cpp/postprocess.h \
    yolo11/cpp/yolo11.h \
    yolo11/utils/image_utils.h \
    yolo11/utils/file_utils.h \
    yolo11/utils/image_drawing.h \
    src/distance/distance.h \
    src/yoloapp/yolo_app.h \
    src/distance/usage.h \

   
INCLUDEPATH += \
    ./yolo11/3rdparty/rknpu2/include \
    ./yolo11/3rdparty/jpeg_turbo/include \
    ./yolo11/3rdparty/librga/include \
    ./yolo11/3rdparty/stb_image \
    ./yolo11/utils \
    ./yolo11/cpp \
    ./src \
    ./yolo11 \
    $$RK356X_SYSROOT/usr/include \

    # ====== 链接库配置 ======
    # RKNNRT 库
    LIBS += -lrknnrt
    # 其他系统库
    LIBS += -ldl -lpthread
    LIBS += -lturbojpeg
    LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs
    LIBS += -L$$PWD -ltouch
    # 条件编译选项
    DISABLE_RGA = false
    DISABLE_LIBJPEG = false

    !DISABLE_RGA {
        DEFINES += USE_RGA
        LIBS += -lrga
    }

    !DISABLE_LIBJPEG {
        DEFINES += USE_LIBJPEG
        LIBS += -ljpeg
    }

    # ====== 预处理器定义 ======
    DEFINES += TARGET_SOC_$${TARGET_SOC}
    DEFINES += MAKE_SYSTEM_PROCESSOR_$${MAKE_SYSTEM_PROCESSOR}
    linux: DEFINES += LINUX_PLATFORM
    QMAKE_CXXFLAGS += -pthread
    QMAKE_LFLAGS += -pthread
    message("build for linux")
    # 地址消毒器
    ENABLE_ASAN = false
    ENABLE_ASAN {
        QMAKE_CXXFLAGS_DEBUG += -fno-omit-frame-pointer -fsanitize=address
        QMAKE_CFLAGS_DEBUG += -fno-omit-frame-pointer -fsanitize=address
        QMAKE_LFLAGS_DEBUG += -fno-omit-frame-pointer -fsanitize=address
        message("BUILD WITH ADDRESS SANITIZER")
    }

    # ====== 部署配置 ======
    qnx: target.path = /tmp/$${TARGET}/bin
    else: unix:!android: target.path = /opt/$${TARGET}/bin
    !isEmpty(target.path): INSTALLS += target
	
	unix:OBJECTS_DIR = ./build
    # ====== 调试信息 ======
    message("=== 项目配置信息 ===")
    message("目标平台: $$MAKE_SYSTEM_NAME")
    message("处理器: $$MAKE_SYSTEM_PROCESSOR")
    message("SOC: $$TARGET_SOC")
    message("Building for Linux ARM64")
    
}
