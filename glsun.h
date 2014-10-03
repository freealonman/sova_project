#ifndef GLSUN_H
#define GLSUN_H

#include "glrenderable.h"
#include "smodel/main.h"

class glSun:public glRenderable
{
public:
    glSun(const int& _Radius, const bool& _is_filled);
    virtual void draw(QPainter* _painter);
protected:
    virtual void drawAdditional(QPainter* _painter);
    virtual void drawText(QPainter *_painter);
};

#endif // GLSUN_H
