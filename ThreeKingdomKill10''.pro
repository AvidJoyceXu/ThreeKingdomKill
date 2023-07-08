QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
TARGET = ThreeKingdomKill
TEMPLATE = app


SOURCES += \
    AIDecision.cpp \
    Talent.cpp \
    Warrior.cpp \
    cards.cpp \
    choosemenu.cpp \
    endscene.cpp \
    main.cpp \
    mainwindow.cpp \
    mymenu.cpp \
    mypushbutton.cpp \
    playscene.cpp \
    shapedwindow.cpp

HEADERS += \
    AIDecision.h \
    choosemenu.h \
    endscene.h \
    heroes_and_cards_base.h \
    mainwindow.h \
    mymenu.h \
    mypushbutton.h \
    playscene.h \
    shapedwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.


RESOURCES += \
    res.qrc

CONFIG += resources_big
