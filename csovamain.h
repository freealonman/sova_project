#ifndef CSOVAMAIN_H
#define CSOVAMAIN_H

#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>

#include "glmaploader.h"
#include "glviewrect.h"
#include "glviewer.h"
#include "smodel/main.h"
#include "gltext.h"
#include "glrenderable.h"
#include "glsun.h"
#include "glsat.h"
#include "gltrace.h"
#include "glimage.h"
#include "glmybutton.h"


class CSovaMain:public QWidget
{
    Q_OBJECT
public:
    CSovaMain(QWidget* parent);
    CSovaMain(QWidget* parent, int pWidth, int pHeight);
    void Start();
    void Stop();
    void Pause();
    void Init(int pWidth, int pHeight);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);
    void resizeEvent(QResizeEvent *);

public slots:
    virtual void Render();

private:
    void Resize();
private:

    glMapLoader mapLoader;
    glViewRect*  viewRect;
    glViewer*    viewer;

    bool MouseRPressed;
    bool MouseLPressed;

    QTimer*      sceneTimer;

    int lastX;
    int lastY;


private:
    glText* tScaleFator;
    glText* tViewableRect;
    int     iScaleFactor;
    int     iViewableRect;


    QString       Statistics;
    glText*      testText;
    int           testCounter;
    CSattelite    Sat1;
    CEarthObject  eob;
    glRenderable* renderable;
    glRenderable* r2;
    glRenderable* Satel;
    glRenderable* sun;
    glRenderable* satTrace;
    glRenderable* sunTerm;
    glRenderable* map;
    glMyButton*   but1;


};

#endif // CSOVAMAIN_H
