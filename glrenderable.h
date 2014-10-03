#ifndef GLRENDERABLE_H
#define GLRENDERABLE_H

#include "smodel/SLLACoordinate.h"
#include <QPainter>
#include <QString>
#include <QPoint>
#include <QFont>
#include <QPen>
#include <QDebug>



class glRenderable
{
public:
    glRenderable();
    glRenderable(const int &_Radius, const bool &_is_filled);
    void setViewPortSize(int _width, int _height);
    void setOptimalFont(const QString& _text, const int& srcWidth, QPainter *_painter);
    void SetObjectName(const QString& _name);
    virtual void SetPen(const QPen& _pen);
    virtual void SetPosition(const QPointF &_position);
    virtual void Update();
    virtual void draw(QPainter* _painter);
    virtual void setData(SLLACoordinate* _data);
    virtual void setFillPen (const QPen& _fill_pen);

private:
    virtual void drawText(QPainter *_painter);
    virtual void drawAdditional(QPainter *_painter);
protected:
    int    vp_width;
    int    vp_height;
    bool   is_filled;
    int    radius;
    double x_scale;
    double y_scale;
    double vp_scale;

    QPoint  text_start;
    QPoint  vp_position;
    QPointF position;
    QString obj_name;
    QPen    pen;

};

#endif // GLRENDERABLE_H
