#ifndef GLSAT_H
#define GLSAT_H

#include "gleobject.h"
#include "smodel/main.h"

class glSat:public glEObject
{
public:
    glSat(const int& _Radius, const bool& _is_filled);
    virtual void draw(QPainter *_painter);
protected:
    virtual void drawText(QPainter* _painter);
};

#endif // GLSAT_H
