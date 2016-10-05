#-------------------------------------------------
#
# Project created by QtCreator 2015-09-05T10:20:46
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = danton
TEMPLATE = app


SOURCES += main.cpp\
    about.cpp \
    preferences.cpp \
    danton.cpp \
    dialogconversion.cpp \
    dvdtofile.cpp \
    disctoiso.cpp \
    musiccdtofile.cpp \
    mediainfo.cpp

HEADERS  += \
    about.h \
    preferences.h \
    danton.h \
    dialogconversion.h \
    dvdtofile.h \
    disctoiso.h \
    musiccdtofile.h \
    mediainfo.h

FORMS    +=

RESOURCES += \
    icons.qrc
