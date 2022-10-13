QT -= gui
QT += network
QT +=core
CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        client/client.cpp \
        client/clientreceiver.cpp \
        client/clientsender.cpp \
        libfocus/loghelper.cpp \
        libfocus/messageapi.cpp \
        libfocus/storemessages.cpp \
        main.cpp \
        server/serverapi.cpp \
        tester/testmessages.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


HEADERS += \
    client/client.h \
    client/clientreceiver.h \
    client/clientsender.h \
    libfocus/libfocus.h \
    libfocus/loghelper.h \
    libfocus/messageapi.h \
    libfocus/storemessages.h \
    server/serverapi.h \
    tester/tester.h \
    tester/testmessages.h
