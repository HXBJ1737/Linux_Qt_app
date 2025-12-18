QT += core gui widgets multimedia multimediawidgets

CONFIG += c++17

win32-msvc*:QMAKE_CXXFLAGS += /utf-8
# QMAKE_LFLAGS += "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\""

SOURCES += \
    src/main.cpp \
    src/index/app2025.cpp \
    src/cam/cam.cpp \
    src/gallery/gallery.cpp \
    src/yoloapp/yolo_app.cpp \

HEADERS += \
   src/index/app2025.h \
   src/cam/cam.h \
   src/gallery/gallery.h \
   src/yoloapp/yolo_app.h \

FORMS +=  \
    src/index/app2025.ui \
    src/cam/cam.ui \
    src/gallery/gallery.ui \
    src/yoloapp/yolo_app.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
    
unix:!macx {
# Linux特定设置
    message("Building for Linux")
    LIBS += -L$$PWD -ltouch
    
}
