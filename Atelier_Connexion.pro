#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------
QT += widgets
QT += core gui sql
QT += core gui serialport
QT +=core gui charts
QT +=sql
QT +=serialport
QT += network
QT += multimedia
QT += core gui network
QT += printsupport

include(C:\Users\USER\Desktop\Projet C++\Integration finale\Atelier_Connexion\libs\qzxing-master\src\QZXing.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
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
    bijou.cpp \
    employes.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    oublie.cpp \
    client.cpp \
    reclammations.cpp \
    fournisseur.cpp \
    historique.cpp \
    smtp.cpp\
    arduino.cpp

HEADERS += \
    bijou.h \
    employes.h \
    mainwindow.h \
    connection.h \
    oublie.h \
    client.h \
    fournisseur.h \
    smtp.h \
    historique.h \
    reclammations.h\
    arduino.h



FORMS += \
        mainwindow.ui \
        oublie.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
