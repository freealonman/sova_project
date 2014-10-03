#include "glsun.h"

glSun::glSun(const int &_Radius, const bool &_is_filled):glRenderable(_Radius, _is_filled)
{

}

void glSun::draw(QPainter *_painter)
{
    glRenderable::draw(_painter);
}

void glSun::drawAdditional(QPainter *_painter)
{


}

void glSun::drawText(QPainter *_painter)
{
    QString s("СОЛНЦЕ");
    _painter->save();
    setOptimalFont(s, radius*2, _painter);
    text_start.setX(vp_position.x() - _painter->fontMetrics().width(s)/2);
    text_start.setY(vp_position.y() - radius - 10);
    _painter->drawText(text_start, s);

    _painter->restore();

}
