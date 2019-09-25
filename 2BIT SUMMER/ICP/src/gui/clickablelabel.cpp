/**
 * @file 	clickablelabel.cpp
 * @brief 	Implementations for clickable label Qt
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */


#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit this->clicked();
}

void ClickableLabel::set_cord(int row, int col)
{
    this->cord.row = row;
    this->cord.col = col;
}

QString ClickableLabel::get_figure()
{
    return this->figure;
}

void ClickableLabel::set_figure(QString figureToBeSet)
{
    this->figure = figureToBeSet;
    QPixmap pix(figureToBeSet);
    this->setPixmap(pix);
}

Square ClickableLabel::get_cord()
{
    return this->cord;
}
