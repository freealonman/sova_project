#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <QGLWidget>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>>
#include "glviewrect.h"
#include "glmaploader.h"
#include <QStaticText>
#include <qopengl.h>
#include <vector>
#include "gltext.h"
#include "glrenderable.h"

class glViewer : public QGLWidget
{
    Q_OBJECT
public:

     explicit glViewer(QWidget *parent, int Width, int Height);
     void AddTextData(glText *str);
     void AddRenderable(glRenderable* _renderable);

private:
     std::vector<glText*>  textData;
     std::vector<glRenderable*> renderable;

protected:
     void paintEvent(QPaintEvent *event);



};

#endif // GLVIEWER_H
