#-------------------------------------------------
#
# Project created by QtCreator 2019-11-09T15:51:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Emulator
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
        blitter.cpp \
        cortexm0cpu.cpp \
        cortexm0cpuhelper.cpp \
        ddrcontroller.cpp \
        debuggerdialog.cpp \
        gfxcore.cpp \
        i2ccontroller.cpp \
        igfxdevicedelegate.cpp \
        main.cpp \
        mainwindow.cpp \
        megabrain.cpp \
        nvic.cpp \
        peripheral.cpp \
        rom.cpp \
        sdcardcontroller.cpp \
        spicontroller.cpp \
        spidevice.cpp \
        sram.cpp \
        sysctl.cpp \
        systembus.cpp \
        uart.cpp \
        winbondflashmemory.cpp

HEADERS += \
        blitter.h \
        cortexm0cpu.h \
        ddrcontroller.h \
        debuggerdialog.h \
        gfxcore.h \
        i2ccontroller.h \
        igfxdevicedelegate.h \
        mainwindow.h \
        megabrain.h \
        nvic.h \
        peripheral.h \
        rom.h \
        sdcardcontroller.h \
        spicontroller.h \
        spidevice.h \
        sram.h \
        sysctl.h \
        systembus.h \
        thumbinstructions.h \
        uart.h \
        winbondflashmemory.h

FORMS += \
        debuggerdialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
