#-------------------------------------------------
#
# Project created by QtCreator 2014-05-24T09:37:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = display-simulator
TEMPLATE = app


SOURCES  += \
    main.cpp \
    program.cpp \
    widget.cpp \
    ../src/display.cpp \
    SmartMatrix/CircularBuffer.cpp \
    SmartMatrix/MatrixColor.cpp \
    SmartMatrix/MatrixConfiguration.cpp \
    SmartMatrix/MatrixFont.cpp \
    SmartMatrix/MatrixForeground.cpp \
    SmartMatrix/MatrixGraphics.cpp \
    SmartMatrix/SmartMatrix.cpp \
    SmartMatrix/Font_apple4x6_256.c \
    SmartMatrix/Font_apple5x7_256.c \
    SmartMatrix/Font_apple6x10.c \
    SmartMatrix/Font_apple8x13.c

HEADERS  += \
    Arduino.h \
    program.h \
    widget.h \
    ../src/display.h \
    SmartMatrix/CircularBuffer.h \
    SmartMatrix/MatrixFontCommon.h \
    SmartMatrix/MatrixHardware_KitV1_16x32.h \
    SmartMatrix/MatrixHardware_KitV1_16x96.h \
    SmartMatrix/MatrixHardware_KitV1_32x32.h \
    SmartMatrix/SmartMatrix.h \
    SmartMatrix/SmartMatrix_16x32.h \
    SmartMatrix/SmartMatrix_32x32.h

FORMS    += widget.ui

INCLUDEPATH += "SmartMatrix"
INCLUDEPATH += "../src"
