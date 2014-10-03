#-------------------------------------------------
#
# Project created by QtCreator 2014-08-25T12:46:12
#
#-------------------------------------------------

QT       += core gui widgets opengl declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui widgets opengl declarative

TARGET = tes2
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    glviewer.cpp \
    glviewrect.cpp \
    glmaploader.cpp \
    csovamain.cpp \
    smodel/CEarthObject.cpp \
    smodel/CSattelite.cpp \
    mainWn.cpp \
    gltext.cpp \
    glrenderable.cpp \
    glsun.cpp \
    glsat.cpp \
    gleobject.cpp \
    gltrace.cpp \
    glimage.cpp \
    glmybutton.cpp

HEADERS  += mainwindow.h \
    glviewer.h \
    glviewrect.h \
    glmaploader.h \
    csovamain.h \
    smodel/CEarthObject.h \
    smodel/CSattelite.h \
    smodel/main.h \
    smodel/SEarthObject.h \
    smodel/SECICoordinate.h \
    smodel/SLLACoordinate.h \
    smodel/SSatelliteFileDesc.h \
    smodel/Utils.h \
    gltext.h \
    glrenderable.h \
    glsun.h \
    glsat.h \
    gleobject.h \
    gltrace.h \
    glimage.h \
    glmybutton.h



LIBS += -LE://Sources//OrbitTools2013//orbitToolsDemo//x64//debug// -lorbitTools.core
LIBS += -LE://Sources//OrbitTools2013//orbitToolsDemo//x64//release// -lorbitTools.orbit
INCLUDEPATH += E://Sources//OrbitTools2013//orbitTools//core
INCLUDEPATH += E://Sources//OrbitTools2013//orbitTools//orbit
INCLUDEPATH += C://Projects//tes2

OTHER_FILES += \
    main.qml

RESOURCES += \
    resorces.qrc

