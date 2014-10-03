#ifndef GLIMAGE_H
#define GLIMAGE_H

#include "glrenderable.h"
#include <QImage>
#include <QDebug>
class glImage:public glRenderable
{
public:
    glImage();
    virtual void draw(QPainter *_painter);
protected:
    QImage* image;
};

#endif // GLIMAGE_H
