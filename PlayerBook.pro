TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    character.cpp \
    database.cpp \
    monster.cpp \
    race.cpp \
    spell.cpp \
    feature.cpp \
    ditem.cpp \
    feat.cpp \
    level.cpp \
    contentlist.cpp \
    choice.cpp \
    castingpage.cpp

RESOURCES += qml.qrc \
    Images.qrc \
    libraries.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

OTHER_FILES +=

HEADERS += \
    character.h \
    database.h \
    monster.h \
    race.h \
    spell.h \
    feature.h \
    ditem.h \
    feat.h \
    level.h \
    contentlist.h \
    choice.h \
    castingpage.h
