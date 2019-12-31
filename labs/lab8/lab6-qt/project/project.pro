QT += xml sql
QT -= gui

CONFIG += c++1z console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    csvstorage.cpp \
    filestorage.cpp \
    cui.cpp        \
    sqlitestorage.cpp \
    storage.cpp \
    xmlstorage.cpp

HEADERS +=          \
  csvstorage.hpp \
  cui.hpp \
  filestorage.hpp \
  founder.hpp \
  organisation.hpp \
  sqlitestorage.hpp \
  storage.hpp \
  xmlstorage.hpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../csvlab/release/ -lcsvlab
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../csvlab/debug/ -lcsvlab
else:unix: LIBS += -L$$OUT_PWD/../csvlab/ -lcsvlab

INCLUDEPATH += $$PWD/../csvlab
DEPENDPATH += $$PWD/../csvlab

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../csvlab/release/libcsvlab.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../csvlab/debug/libcsvlab.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../csvlab/release/csvlab.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../csvlab/debug/csvlab.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../csvlab/libcsvlab.a
