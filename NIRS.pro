QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NIRS
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11 console

SOURCES += \
        annealing/annealing.cpp \
        annealing/bounds.cpp \
        annealing/optim_funcs.cpp \
        annealing/optimizer.cpp \
        annealing/options.cpp \
        annealing/result.cpp \
        annealingsettings.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        annealing/annealing.h \
        annealing/bounds.h \
        annealing/help_types.h \
        annealing/optim_funcs.h \
        annealing/optimizer.h \
        annealing/options.h \
        annealing/result.h \
        annealingsettings.h \
        mainwindow.h

FORMS += \
    annealingsettings.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# GNU Scientific Library
unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lgsl
INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include
unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libgsl.a
# ......................
unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lgslcblas
INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include
unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libgslcblas.a

# QCustomPlot shared library
unix:!macx: LIBS += -L$$PWD/../../qcustomplotlib/lib/ -lqcustomplot
INCLUDEPATH += $$PWD/../../qcustomplotlib/include
DEPENDPATH += $$PWD/../../qcustomplotlib/include
# ..........................
unix:!macx: LIBS += -L$$PWD/../../qcustomplotlib/lib/ -lqcustomplotd
INCLUDEPATH += $$PWD/../../qcustomplotlib/include
DEPENDPATH += $$PWD/../../qcustomplotlib/include
