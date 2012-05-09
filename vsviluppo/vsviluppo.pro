#-------------------------------------------------
#
# Project created by QtCreator 2011-10-16T21:19:59
#
#-------------------------------------------------

QT       += core gui sql
QT       += xml
CONFIG +=static
TARGET = vsviluppo
TEMPLATE = app
SOURCES += main.cpp\
        mainwindow.cpp \
    QTable.cpp \
    database.cpp \
    sqlconnection.cpp \
    DbConnection/dconnection.cpp \
    DbConnection/sconnection.cpp \
    DbConnection/connection.cpp \
    qcquerylist.cpp \
    edittext.cpp \
    projectdata.cpp


HEADERS  += mainwindow.h \
    QTable.h \
    database.h \
    sqlconnection.h \
    DbConnection/connection.h \
    DbConnection/sconnection.h \
    DbConnection/cexception.h   \
    DbConnection/dconnection.h \
    qcquerylist.h \
    edittext.h \
    Exception\listisempty.h \
    Exception\filenotfound.h \
    projectdata.h \
    Definition.h
FORMS    += mainwindow.ui









































