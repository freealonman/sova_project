#include "gltrace.h"

glTrace::glTrace(const bool& _is_filled, const FILL_TYPE& _fill_type ):glRenderable(0, _is_filled),fill_type(_fill_type)
{
    position = QPoint(0, 0);
    jk=0;
    path = NULL;
}

void glTrace::setData(SLLACoordinate *_data)
{
    if (path != NULL) {delete path;}
    path = new QPainterPath();
    path->moveTo((_data[0].Longitude + 180)*x_scale,(90- _data[0].Latitude)*y_scale);
    for (int i=1; i < vp_width; i++)
    {
        if (is_filled)
        {
            path->lineTo((_data[i].Longitude + 180)*x_scale,(90- _data[i].Latitude)*y_scale);
        } else
        {
            int x0 = (180 + _data[i - 1].Longitude)*x_scale;
            //int y0 = (90  - _data[i - 1].Latitude)*y_scale;
            int x1 = (180 + _data[i].Longitude)*x_scale;
            int y1 = (90  - _data[i].Latitude)*y_scale;
            if (abs(x1 - x0) <= 2)
            {
                path->lineTo(x1,y1);
            } else
            {
                path->moveTo(x1,y1);
            }
        }



    }
    free(_data);
}

void glTrace::draw(QPainter *_painter)
{
    _painter->save();
    _painter->setRenderHint(QPainter::HighQualityAntialiasing, true);
    _painter->setPen(pen);

    if (is_filled)
    {

        switch(fill_type)
        {
        case FILL_DOWN:
        {
            _painter->setPen(pen);
            _painter->drawPath(*path);

            _painter->setPen(pen);
            path->lineTo(vp_width, vp_height);
            path->lineTo(0, vp_height);
            _painter->fillPath(*path, QBrush(QColor(0,0,0,125)));
            break;
        }
        case FILL_UP:
        {
            break;
        }
        }
    } else
    {
        _painter->drawPath(*path);
    }
    _painter->restore();
}

void glTrace::setFillPen(const QPen &_fill_pen)
{
    fill_pen = _fill_pen;
}



