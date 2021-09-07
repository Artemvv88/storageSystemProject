QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    tst_test.cpp \
    ../storageSystem/database.cpp \
    ../storageSystem/product.cpp \
    ../storageSystem/rack.cpp \
    ../storageSystem/systemuser.cpp \
    ../storageSystem/task.cpp

HEADERS +=  \
    ../storageSystem/database.h \
    ../storageSystem/product.h \
    ../storageSystem/rack.h \
    ../storageSystem/systemuser.h \
    ../storageSystem/task.h
