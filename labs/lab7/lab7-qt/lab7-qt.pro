QT       += core gui xml
CONFIG += c++1z
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    csvlab.cpp \
    csvstorage.cpp \
    filestorage.cpp \
    string_table.cpp \
    adddialog.cpp \
    editdialog.cpp

HEADERS += \
    mainwindow.hpp \
    csvlab.hpp \
    csvstorage.hpp \
    filestorage.hpp \
    string_table.hpp \
    organisation.hpp \
    adddialog.hpp \
    editdialog.hpp

FORMS += \
    mainwindow.ui \
    adddialog.ui \
    editdialog.ui
