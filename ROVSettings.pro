#-------------------------------------------------
#
# Project created by QtCreator 2019-05-18T16:13:36
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += core
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ROVSettings
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
        packets.h

FORMS += \
        mainwindow.ui


INCLUDEPATH += "C:\OpenCV\OpenCV_bin\install\include"
        LIBS += -L"C:\OpenCV\OpenCV_bin\install\x86\vc15\lib" \
                -lopencv_calib3d410 \
                -lopencv_core410 \
                -lopencv_dnn410 \
                -lopencv_features2d410 \
                -lopencv_flann410 \
                -lopencv_highgui410 \
                -lopencv_imgcodecs410 \
                -lopencv_imgproc410 \
                -lopencv_ml410 \
                -lopencv_objdetect410 \
                -lopencv_photo410 \
                -lopencv_stitching410 \
                -lopencv_video410 \
                -lopencv_videoio410 \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
