#include "glrenderable.h"

glRenderable::glRenderable()
{

}

glRenderable::glRenderable(const int &_Radius, const bool &_is_filled)
{
    radius     = _Radius;
    is_filled = _is_filled;
}

void glRenderable::setViewPortSize(int _width, int _height)
{
    vp_width  = _width;
    vp_height = _height;
    x_scale   = vp_width / 360.0;
    y_scale   = vp_height/ 180.0;
}

void glRenderable::setOptimalFont(const QString &_text, const int &srcWidth, QPainter* _painter)
{
    QFont font("Calibri");
    font.setBold(true);
    font.setStyleStrategy(QFont::OpenGLCompatible);
    font.setStyleStrategy(QFont::PreferAntialias);
    font.setStyleStrategy(QFont::PreferQuality);
    font.setPixelSize(1);
    _painter->setFont(font);

    int fW =_painter->fontMetrics().width(_text);
    while (fW < srcWidth)
    {
        font.setPixelSize(font.pixelSize() + 1);
        _painter->setFont(font);
        fW = _painter->fontMetrics().width(_text);
    }

    font.setPixelSize(font.pixelSize() - 1);
    _painter->setFont(font);
}

void glRenderable::SetObjectName(const QString &_name)
{
    obj_name = _name;
}

void glRenderable::SetPen(const QPen &_pen)
{
    pen = _pen;
}

void glRenderable::SetPosition(const QPointF &_position)
{
    position = _position;
    vp_position.setX((_position.x() + 180)*x_scale);
    vp_position.setY((90   -_position.y())*y_scale);
}

void glRenderable::Update()
{

}

void glRenderable::draw(QPainter* _painter)
{
    if (is_filled)
    {
        QBrush brush;
        brush.setColor(pen.color());
        brush.setStyle(Qt::SolidPattern);
        _painter->setBrush(brush);
        _painter->drawEllipse(vp_position, radius, radius);

    }else
    {
        pen.setWidth(2);
        _painter->setPen(pen);
        _painter->drawEllipse(vp_position, 1, 1);
        _painter->drawEllipse(vp_position, radius, radius);
    }

    drawAdditional(_painter);
    drawText(_painter);

}

void glRenderable::setData(SLLACoordinate* _data)
{

}

void glRenderable::setFillPen(const QPen &_fill_pen)
{

}

void glRenderable::drawText(QPainter *_painter)
{

}

void glRenderable::drawAdditional(QPainter *_painter)
{

}
