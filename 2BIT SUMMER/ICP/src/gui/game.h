#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <list>
#include "clickablelabel.h"
#include "game.h"


class game
{
public:
    game();

private:
    ClickableLabel *board[8][8];
    QWidget *fields[8][8];
};

#endif // GAME_H
