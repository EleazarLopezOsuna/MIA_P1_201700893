QT += core
QT -= gui

CONFIG += c++11

TARGET = P1MIA
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    parser.cpp \
    scanner.cpp \
    MKDISK.cpp \
    RMDISK.cpp \
    FDISK.cpp \
    lista.cpp \
    MOUNT.cpp \
    fs.cpp \
    RMUSR.cpp \
    RMGRP.cpp \
    REP.cpp \
    MKGRP.cpp \
    MKFS.cpp \
    MKFILE.cpp \
    MKDIR.cpp \
    LOGOUT.cpp \
    LOGIN.cpp \
    CAT.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DISTFILES += \
    parser.y \
    lexico.l \
    generador.sh

HEADERS += \
    parser.h \
    scanner.h \
    MKDISK.h \
    RMDISK.h \
    FDISK.h \
    lista.h \
    MOUNT.h \
    objetos.h \
    fs.h \
    RMUSR.h \
    RMGRP.h \
    REP.h \
    MKGRP.h \
    MKFS.h \
    MKFILE.h \
    MKDIR.h \
    LOGOUT.h \
    LOGIN.h \
    CAT.h
