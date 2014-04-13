TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    position.c \
    game.c

HEADERS += \
    position.h \
    game.h

OTHER_FILES += \
    README.md

