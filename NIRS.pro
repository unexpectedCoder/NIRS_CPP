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
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/gsl/lib/release/ -lgsl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/gsl/lib/debug/ -lgsl
else:unix:!macx: LIBS += -L$$PWD/gsl/lib/ -lgsl
INCLUDEPATH += $$PWD/gsl/include
DEPENDPATH += $$PWD/gsl/include
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/gsl/lib/release/libgsl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/gsl/lib/debug/libgsl.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/gsl/lib/release/gsl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/gsl/lib/debug/gsl.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/gsl/lib/libgsl.a
# ---------------------------------------------------------------------------------------------------
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/gsl/lib/release/ -lgslcblas
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/gsl/lib/debug/ -lgslcblas
else:unix:!macx: LIBS += -L$$PWD/gsl/lib/ -lgslcblas
INCLUDEPATH += $$PWD/gsl/include
DEPENDPATH += $$PWD/gsl/include
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/gsl/lib/release/libgslcblas.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/gsl/lib/debug/libgslcblas.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/gsl/lib/release/gslcblas.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/gsl/lib/debug/gslcblas.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/gsl/lib/libgslcblas.a

# QCustomPlot shared library
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/qcustomplot/lib/ -lqcustomplot
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/qcustomplot/lib/ -lqcustomplotd
else:unix:!macx: LIBS += -L$$PWD/qcustomplot/lib/ -lqcustomplot
INCLUDEPATH += $$PWD/qcustomplot/include
DEPENDPATH += $$PWD/qcustomplot/include
