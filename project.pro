QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boomerang.cpp \
    brain.cpp \
    braincontainer.cpp \
    bullet.cpp \
    changepass.cpp \
    character.cpp \
    forgetpass.cpp \
    game.cpp \
    ground.cpp \
    jalapeno.cpp \
    login.cpp \
    main.cpp \
    peashooter.cpp \
    plant.cpp \
    plantcards.cpp \
    plumMine.cpp \
    signup.cpp \
    square.cpp \
    sun.cpp \
    suncontainer.cpp \
    twoPeashotter.cpp \
    userinfo.cpp \
    walnut.cpp \
    zombie.cpp \
    zombiecards.cpp

HEADERS += \
    boomerang.h \
    brain.h \
    braincontainer.h \
    bullet.h \
    changepass.h \
    character.h \
    forgetpass.h \
    game.h \
    ground.h \
    jalapeno.h \
    login.h \
    peashooter.h \
    plant.h \
    plantcards.h \
    plumMine.h \
    signup.h \
    square.h \
    sun.h \
    suncontainer.h \
    twoPeashotter.h \
    userinfo.h \
    walnut.h \
    zombie.h \
    zombiecards.h

FORMS += \
    changepass.ui \
    forgetpass.ui \
    login.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
