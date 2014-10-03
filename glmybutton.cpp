#include "glmybutton.h"

glMyButton::glMyButton(QWidget *parent):QPushButton(parent)
{
    setFlat(true);
}

void glMyButton::paintEvent(QPaintEvent *)
{

    //this->style()->
    QPainter qp;
    qp.begin(this);
    qp.setPen(QPen(Qt::white));
    qp.drawEllipse(QPoint(50, 50), 30, 30);
    qp.end();
    qDebug() << "GOOD";
}


