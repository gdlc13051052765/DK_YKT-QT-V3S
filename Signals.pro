#-------------------------------------------------
#
# Project created by QtCreator 2019-12-24T23:43:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = posAppQT
TEMPLATE = app
#QT       += multimedia
#QT       += sql

LIBS +=-L/usr/lib -lasound 
INCLUDEPATH += ./
#LIBS += ./libsqlite3.so

SOURCES += main.cpp\
    cJSON.c \
    mainwindow.cpp \
    modifysystimeui.cpp \
    rfal_thread.cpp \
    setup.cpp \
    ipinformation.cpp \
    devmsg.cpp \
    setconsumemode.cpp \
    queryconsumerecord.cpp \
    querydayconsumemoney.cpp \
    dialog.cpp \
    mainconsumeinterface.cpp \
    sqlite3Qt.cpp

HEADERS  += \
    CalucationFile.H \
    Delay.h \
    ISO7816.H \
    MFRC522.h \
    dialog.h \
    mainwindow.h \
    modifysystimeui.h \
    readWriteCard.h \
    rfal_thread.h \
    setup.h \
    ipinformation.h \
    sqlite3.h \
    devmsg.h \
    setconsumemode.h \
    queryconsumerecord.h \
    querydayconsumemoney.h \
    mainconsumeinterface.h \
    sqlite3Qt.h

FORMS    += \
    mainconsumewindow.ui \
    mainwindow.ui \
    setup.ui \
    ipinformation.ui \
    devmsg.ui \
    setconsumemode.ui \
    queryconsumerecord.ui \
    querydayconsumemoney.ui \
    dialog.ui \
    mainconsumeinterface.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lsqlite3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lsqlite3
else:unix: LIBS += -L$$PWD/./ -lsqlite3

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lreadcard
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lreadcard
else:unix: LIBS += -L$$PWD/./ -lreadcard

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

