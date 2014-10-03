#ifndef GLTRACE_H
#define GLTRACE_H

#include "glrenderable.h"
#include "smodel/SLLACoordinate.h"



enum FILL_TYPE {FILL_UP, FILL_DOWN};

class glTrace:public glRenderable
{
public:
    glTrace(const bool& _is_filled = false, const FILL_TYPE& _fill_type = FILL_DOWN);
    virtual void setData(SLLACoordinate *_data);
    virtual void draw(QPainter *_painter);
    virtual void setFillPen(const QPen& _fill_pen);
protected:
    QPen      fill_pen;
    QPainterPath* path;
    FILL_TYPE fill_type;
    int jk;
};

#endif // GLTRACE_H
