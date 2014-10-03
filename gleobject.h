#ifndef GLEOBJECT_H
#define GLEOBJECT_H

#include <glrenderable.h>

class glEObject:public glRenderable
{
public:
    glEObject(const int& _Radius, const bool& _is_filled);
    virtual void draw(QPainter* _painter);
protected:
     virtual void drawText(QPainter* _painter);
     double text_angle;//угол наклона текста
     QRect   text_rect;
};

#endif // GLEOBJECT_H
