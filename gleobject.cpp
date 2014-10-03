#include "gleobject.h"

glEObject::glEObject(const int &_Radius, const bool &_is_filled):glRenderable(_Radius, _is_filled)
{
    text_angle = - 30;
}

void glEObject::draw(QPainter *_painter)
{
    _painter->save();
    QPoint lStart(radius*cos((text_angle*3.14f)/180.0) +    vp_position.x(),radius*sin((text_angle*3.14f)/180.0) +      vp_position.y());
    QPoint lEnd((radius+20)*cos((text_angle*3.14f)/180.0) + vp_position.x(),(radius+20)*sin((text_angle*3.14f)/180.0) + vp_position.y());
    QPoint lPEnd(lEnd.x() + radius*4, lEnd.y());
    _painter->setPen(pen);
    text_start = lEnd;
    _painter->drawLine(lStart, lEnd);
    _painter->drawLine(lEnd,  lPEnd);
    _painter->restore();
    glRenderable::draw(_painter);
}

void glEObject::drawText(QPainter *_painter)
{
    QPoint upText(text_start.x(), text_start.y() - 5);
    QPoint doText(text_start.x(), text_start.y() + 5);
    //отрисовка имени объекта
    _painter->save();
    setOptimalFont(obj_name, radius*4, _painter);
    _painter->drawText(upText, obj_name);
    //------------------------
    //отрисовка параметров объекта
    QString latS("Широта: " + QString::number(position.y()));
    QString lonS("Долгота: " + QString::number(position.x()));

    if (latS.size() > lonS.size())
    {
        setOptimalFont(latS, radius*4, _painter);
    }
    else
    {
        setOptimalFont(lonS, radius*4, _painter);
    }
    QRect doRect(doText, QPoint(doText.x()+radius*4, doText.y() + _painter->fontMetrics().height()*2));
    _painter->drawText(doRect ,latS + "\n" + lonS);
    text_rect.setCoords(upText.x(), upText.y(), doRect.right(), doRect.bottom());
    _painter->restore();
}
