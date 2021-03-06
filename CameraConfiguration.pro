QT -= gui

QT += serialport

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        caliobration_group.cpp \
        camera_config.cpp \
        detector_group.cpp \
        dre_or_ago_group.cpp \
        engineering_group.cpp \
        filters_group.cpp \
        graphics_group.cpp \
        imager_configuration_group.cpp \
        lens_group.cpp \
        main.cpp \
        serial.cpp \
        status_group.cpp \
        tracker_group.cpp \
        user_interface_group.cpp \
        video_group.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    camera_config.h \
    serial.h
