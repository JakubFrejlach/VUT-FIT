/**
 * @file 	clickablelabel.h
 * @brief 	header file for clickable label class
 * @author 	Tomáš Venkrbec (xvenkr01), Jakub Frejlach (xfrejl00)
 */


#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include "../square.hpp"

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    void set_cord(int row, int col);
    Square get_cord();
    void set_figure(QString figureToBeSet);
    QString get_figure();

    ~ClickableLabel();

signals:
    void clicked();

private:
    Square cord;
    QString figure;

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // CLICKABLELABEL_H
