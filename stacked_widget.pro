QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    page_2players.cpp \
    page_allplayers.cpp \
    page_onetournament.cpp \
    page_rules.cpp \
    page_welcome.cpp \
    widget.cpp

HEADERS += \
    page_2players.h \
    page_allplayers.h \
    page_onetournament.h \
    page_rules.h \
    page_welcome.h \
    widget.h

FORMS += \
    page_2players.ui \
    page_allplayers.ui \
    page_onetournament.ui \
    page_rules.ui \
    page_welcome.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
