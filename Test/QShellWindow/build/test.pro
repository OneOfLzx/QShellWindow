######################################################################
# Automatically generated by qmake (3.1) Mon Aug 2 11:16:23 2021
######################################################################

TEMPLATE = app
TARGET = test
INCLUDEPATH += $$system(find ../../../Common -type d)
INCLUDEPATH += $$system(find ../../../TerminalWrapper -type d)

DEFINES += QT_DEPRECATED_WARNINGS

# Input
HEADERS += ../../../Widget/QShellWindow.h
SOURCES += $$system(find .. | grep .cpp)
SOURCES += $$system(find ../../../Common | grep .cpp)
SOURCES += $$system(find ../../../TerminalWrapper | grep .cpp)
SOURCES += $$system(find ../../../Widget | grep .cpp)

QT += widgets core gui

CONFIG += console
