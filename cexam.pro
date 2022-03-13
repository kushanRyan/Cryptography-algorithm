#-------------------------------------------------
#
# Project created by QtCreator 2021-06-11T10:40:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cexam
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    CryptographicAlgorithms/addRoundKey.cpp \
    CryptographicAlgorithms/addRoundTowArray.cpp \
    CryptographicAlgorithms/AES.cpp \
    CryptographicAlgorithms/deAES.cpp \
    CryptographicAlgorithms/deMixColumns.cpp \
    CryptographicAlgorithms/DES.cpp \
    CryptographicAlgorithms/deShiftRows.cpp \
    CryptographicAlgorithms/deSubBytes.cpp \
    CryptographicAlgorithms/DH.cpp \
    CryptographicAlgorithms/Elgamal.cpp \
    CryptographicAlgorithms/euclidean.cpp \
    CryptographicAlgorithms/expandedKey.cpp \
    CryptographicAlgorithms/MD5.cpp \
    CryptographicAlgorithms/mixColumn.cpp \
    CryptographicAlgorithms/PrimalityTesting.cpp \
    CryptographicAlgorithms/sBoxSpawner.cpp \
    CryptographicAlgorithms/SHA1.cpp \
    CryptographicAlgorithms/shiftRow.cpp \
    CryptographicAlgorithms/subBytes.cpp \
    CryptographicAlgorithms/tools.cpp \
    euclideanw.cpp \
    exeuclideanw.cpp \
    isprimew.cpp \
    elgamalw.cpp \
    aesw.cpp \
    desw.cpp \
    dhw.cpp \
    md5w.cpp \
    rsaw.cpp \
    sha1w.cpp \
    deswarn.cpp \
    complete.cpp \
    aeswarn.cpp \
    CryptographicAlgorithms/RSA.cpp \
    elgamalwarn.cpp

HEADERS  += mainwindow.h \
    CryptographicAlgorithmsH/AES.h \
    CryptographicAlgorithmsH/deAES.h \
    CryptographicAlgorithmsH/DES.h \
    CryptographicAlgorithmsH/DH.h \
    CryptographicAlgorithmsH/Elgamal.h \
    CryptographicAlgorithmsH/euclidean.h \
    CryptographicAlgorithmsH/MD5.h \
    CryptographicAlgorithmsH/PrimalityTesting.h \
    CryptographicAlgorithmsH/sBoxSpawner.h \
    CryptographicAlgorithmsH/SHA1.h \
    euclideanw.h \
    exeuclideanw.h \
    isprimew.h \
    elgamalw.h \
    aesw.h \
    desw.h \
    dhw.h \
    md5w.h \
    rsaw.h \
    sha1w.h \
    deswarn.h \
    complete.h \
    aeswarn.h \
    rsa.h \
    CryptographicAlgorithmsH/RSA.h \
    elgamalwarn.h

FORMS    += mainwindow.ui \
    euclideanw.ui \
    exeuclideanw.ui \
    isprimew.ui \
    elgamalw.ui \
    aesw.ui \
    desw.ui \
    dhw.ui \
    md5w.ui \
    rsaw.ui \
    sha1w.ui \
    deswarn.ui \
    complete.ui \
    aeswarn.ui \
    elgamalwarn.ui
