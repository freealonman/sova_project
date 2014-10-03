#ifndef GLMYBUTTON_H
#define GLMYBUTTON_H


#include <QPushButton>
#include <QPainter>
#include <QDebug>
class glMyButton: public QPushButton
{
public:
    glMyButton(QWidget *parent);
    void paintEvent(QPaintEvent*);
};

#endif // GLMYBUTTON_H
