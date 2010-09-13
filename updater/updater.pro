CONFIG += release
QT += network
TEMPLATE = app

unix: TARGET = ../Updater
win32: TARGET = ../../Updater

DEPENDPATH += . \
    headers \
    tpl \
    src \
    ui \
    ../qns/src \
    ../qns/headers

INCLUDEPATH += . \
    headers \
    tpl \
    ../qns/headers

# Input
FORMS += ui/Updater.ui ui/CredentialsDialog.ui

HEADERS += headers/Updater.h \
headers/Credentials.h \
headers/CredentialsDialog.h

SOURCES += src/main.cpp \
src/Updater.cpp \
src/Credentials.cpp \
src/CredentialsDialog.cpp

# Common
SOURCES += ../qns/src/Encryption.cpp
HEADERS += ../qns/headers/Encryption.h

# Output
DESTDIR = .
OBJECTS_DIR = obj
MOC_DIR = moc
UI_SOURCES_DIR = ui
UI_HEADERS_DIR = headers
win32:RC_FILE = appIcon/windows.rc
#macx:ICON = appIcon/updater.icns
