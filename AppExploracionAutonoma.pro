#-------------------------------------------------
#
# Project created by QtCreator 2014-01-27T16:34:54
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestOpengl01
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    manipulador.cpp \
    poligono.cpp \
    punto3d.cpp \
    modelosensorial.cpp \
    objeto3D.cpp \
    escena.cpp \
    geneticoinversa.cpp \
    individuoinversa.cpp \
    sort_map.cpp \
    individuo.cpp \
    genetico.cpp \
    parescaneo.cpp \
    set.cpp \
    nodoset.cpp \
    geneticoset.cpp \
    individuoset.cpp \
    srt.cpp \
    nodosrt.cpp \
    linea.cpp \
    MatLabProc.cpp \
    movil.cpp \
    rrt.cpp \
    nodorrt.cpp \
    grafo.cpp \
    vertice.cpp \
    arista.cpp \
    heuristica.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    manipulador.h \
    poligono.h \
    punto3d.h \
    modelosensorial.h \
    objeto3D.h \
    escena.h \
    geneticoinversa.h \
    individuoinversa.h \
    sort_map.h \
    individuo.h \
    genetico.h \
    parescaneo.h \
    set.h \
    nodoset.h \
    geneticoset.h \
    individuoset.h \
    srt.h \
    nodosrt.h \
    linea.h \
    MatLabProc.h \
    movil.h \
    rrt.h \
    nodorrt.h \
    grafo.h \
    vertice.h \
    arista.h \
    heuristica.h
FORMS    += mainwindow.ui
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/external
INCLUDEPATH += $$PWD/common

LIBS += -L$$PWD/lib/ -lglui32
LIBS += -L$$PWD/lib/ -lgloop
LIBS += -L$$PWD/lib/ -lglew
LIBS += -L$$PWD/lib/ -lcarve
