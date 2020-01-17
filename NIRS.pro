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
        help_funcs.cpp \
        main.cpp \
        mainwindow.cpp \
        rocket/rocket.cpp \
        rocket/rocket_types.h.cpp \
        scene/scene.cpp \
        scene/scene_types.cpp

HEADERS += \
        annealing/annealing.h \
        annealing/bounds.h \
        annealing/help_types.h \
        annealing/optim_funcs.h \
        annealing/optimizer.h \
        annealing/options.h \
        annealing/result.h \
        annealingsettings.h \
        help_funcs.h \
        mainwindow.h \
        rocket/rocket.h \
        rocket/rocket_types.h \
        scene/scene.h \
        scene/scene_types.h

FORMS += \
    annealingsettings.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# GNU Scientific Library
unix:!macx: LIBS += -L$$PWD/gsl/lib/ -lgsl
INCLUDEPATH += $$PWD/gsl/include
DEPENDPATH += $$PWD/gsl/include
unix:!macx: PRE_TARGETDEPS += $$PWD/gsl/lib/libgsl.a
# ---------------------------------------------------------------------------------------------------
unix:!macx: LIBS += -L$$PWD/gsl/lib/ -lgslcblas
INCLUDEPATH += $$PWD/gsl/include
DEPENDPATH += $$PWD/gsl/include
unix:!macx: PRE_TARGETDEPS += $$PWD/gsl/lib/libgslcblas.a

# QCustomPlot shared library
unix:!macx: LIBS += -L$$PWD/qcustomplot/lib/ -lqcustomplot
INCLUDEPATH += $$PWD/qcustomplot/include
DEPENDPATH += $$PWD/qcustomplot/include

DISTFILES += \
    Scene/atmosphere.txt \
    scene/atmosphere.txt
