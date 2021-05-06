QT       += core gui sql printsupport charts network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    aicha.cpp \
    authentification.cpp \
    clients.cpp \
    commande.cpp \
    connection.cpp \
    employe.cpp \
    fournisseur.cpp \
    gest_cl_co.cpp \
    gestion_fournisseur.cpp \
    login.cpp \
    mailling.cpp \
    main.cpp \
    mainwindow.cpp \
    matiere.cpp \
    nour.cpp \
    poste.cpp \
    produits.cpp \
    promotions.cpp \
    reservation.cpp \
    reservationinter.cpp \
    smtp.cpp \
    smtpp.cpp \
    smtppp.cpp \
    tables.cpp

HEADERS += \
    aicha.h \
    authentification.h \
    clients.h \
    commande.h \
    connection.h \
    employe.h \
    fournisseur.h \
    gest_cl_co.h \
    gestion_fournisseur.h \
    login.h \
    mailling.h \
    mainwindow.h \
    matiere.h \
    nour.h \
    poste.h \
    produits.h \
    promotions.h \
    reservation.h \
    reservationinter.h \
    smtp.h \
    smtpp.h \
    smtppp.h \
    tables.h

FORMS += \
    aicha.ui \
    gest_cl_co.ui \
    gestion_fournisseur.ui \
    login.ui \
    mainwindow.ui \
    nour.ui \
    reservationinter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Projet2A.pro.user

SUBDIRS += \
    Nour.pro
