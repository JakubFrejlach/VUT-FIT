#-------------------------------------------------
#
# Project created by QtCreator 2019-05-08T11:31:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    clickablelabel.cpp \
    game.cpp \
    ../chess.cpp \
    ../board.cpp \
    ../move.cpp \
    ../bishop.cpp \
    ../king.cpp \
    ../knight.cpp \
    ../piece.cpp \
    ../queen.cpp \
    ../rook.cpp \
    ../pawn.cpp \
    ../parser.cpp

HEADERS += \
        mainwindow.h \
    clickablelabel.h \
    game.h \
    ../chess.hpp \
    ../board.hpp \
    ../move.hpp \
    ../parser.hpp \
    ../square.hpp \
    ../board_model.hpp \
    ../Pieces/rook.hpp \
    ../piece.hpp \
    ../Pieces/bishop.hpp \
    ../Pieces/king.hpp \
    ../Pieces/knight.hpp \
    ../Pieces/pawn.hpp \
    ../Pieces/queen.hpp

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES +=
