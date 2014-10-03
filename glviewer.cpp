#include "glviewer.h"


glViewer::glViewer(QWidget *parent, int Width, int Height):QGLWidget(parent)
{
    QGLFormat format;
    format.setDoubleBuffer(true);
    format.setSampleBuffers(true);
    format.setSamples(32);
    format.setDirectRendering(true);
    setFormat(format);
    //glEnable();
    //setAutoFillBackground(true);
    setFixedSize(Width, Height);
    move(0,0);
}


void glViewer::AddTextData(glText *str)
{
    textData.push_back(str);


}

void glViewer::AddRenderable(glRenderable *_renderable)
{
    renderable.push_back(_renderable);
}


void glViewer::paintEvent(QPaintEvent *event)
{

    QPainter qp1;
    qp1.begin(this);
    qp1.setRenderHint(QPainter::TextAntialiasing, true);
    qp1.setRenderHint(QPainter::Antialiasing, true);

    //-----------------------------------------------------------------
    for (int i = 0; i < renderable.size(); i++)
    {
        renderable[i]->draw(&qp1);
    }
    for (int i=0; i < textData.size(); i++)
    {
        qp1.setPen(*textData[i]->GetPen());
        qp1.setFont(*textData[i]->GetFont());
        qp1.drawText(*textData[i]->GetRect(), *textData[i]);
    }
    //-----------------------------------------------------------------
    qp1.end();
}



