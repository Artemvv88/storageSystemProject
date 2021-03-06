QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    main.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    newproductdialog.cpp \
    newrackdialog.cpp \
    newtaskdialog.cpp \
    product.cpp \
    productflowdialog.cpp \
    rack.cpp \
    registrationwindow.cpp \
    systemuser.cpp \
    task.cpp

HEADERS += \
    database.h \
    loginwindow.h \
    mainwindow.h \
    newproductdialog.h \
    newrackdialog.h \
    newtaskdialog.h \
    product.h \
    productflowdialog.h \
    rack.h \
    registrationwindow.h \
    systemuser.h \
    task.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    newproductdialog.ui \
    newrackdialog.ui \
    newtaskdialog.ui \
    productflowdialog.ui \
    registrationwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
