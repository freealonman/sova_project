#include "csovamain.h"

CSovaMain::CSovaMain(QWidget *parent):QWidget(parent)
{
    Init(width(), height());
}

CSovaMain::CSovaMain(QWidget *parent, int pWidth, int pHeight):QWidget(parent)
{
    Init(pWidth, pHeight);
}

void CSovaMain::Start()
{
    sceneTimer->start();
}

void CSovaMain::Stop()
{
    sceneTimer->stop();
}

void CSovaMain::Pause()
{
    sceneTimer->stop();
}

void CSovaMain::Init(int pWidth, int pHeight)
{
    setMouseTracking(true);



    viewRect = new glViewRect(84800, 42400, pWidth, pHeight);
    viewer = new glViewer(this,pWidth, pHeight);

    sceneTimer = new QTimer(this);
    QObject::connect(sceneTimer, SIGNAL(timeout()), SLOT(Render()));
    sceneTimer->start(1000);

    QPen pen(QColor(255,255,255,150));
    pen.setWidth(3);
    lastX = lastY = 0;
    Sat1  = CSattelite();
    Sat1.LoadTLE("C:\\stations.tle");
    //---------------------init  view data
    testText   = new glText("TEWST", QRect(0, 0, 300, 300));
    tScaleFator = new glText("", QRect(0, 50, 100, 100));
    viewer->AddTextData(testText);
    //---------------------ISS---------------
    Satel = new glSat(20, false);
    Satel->SetObjectName("МКС");
    Satel->setViewPortSize(1920,1080);
    Satel->SetPen(pen);
    //---------------------------------------
    //---------------------SUN---------------
    sun = new glSun(30, false);
    sun->setViewPortSize(1920, 1080);
    sun->SetPen(QPen(Qt::yellow));
    //---------------------------------------
    //trace
    satTrace = new glTrace(false, FILL_DOWN);
    satTrace->setViewPortSize(1920, 1080);

    satTrace->SetPen(pen);
    satTrace->setData(Sat1.GetTrace(time(NULL), 1920));
    //---------------------------------------
    //---------------terminator
    sunTerm = new glTrace(true, FILL_DOWN);
    sunTerm->setViewPortSize(1920, 1080);
    QPen st(Qt::yellow);
    st.setWidth(1);
    sunTerm->SetPen(st);
    sunTerm->setFillPen(QPen(QColor(0,0,0,170)));
    sunTerm->setData(GetTerminatorLine(time(NULL), 1920));
    //-------------------------
    //---------------map---------------------
    map = new glImage();
    //---------------------------------------
    viewer->AddRenderable(map);
    viewer->AddRenderable(sunTerm);
    viewer->AddRenderable(sun);
    viewer->AddRenderable(Satel);
    viewer->AddRenderable(satTrace);

    but1 = new glMyButton(viewer);
    but1->setFixedSize(100, 100);
    but1->show();

}

void CSovaMain::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int deltaX = event->x() - lastX;
        int deltaY = event->y() - lastY;

        viewRect->_Move(deltaX, deltaY);

        lastX = event->x();
        lastY = event->y();
        event->accept();
    } else
    {
        lastX = event->x();
        lastY = event->y();
    }
}

void CSovaMain::wheelEvent(QWheelEvent *event)
{

    if (event->delta() > 0)
    {
        viewRect->_Scale(event->x(), event->y(), 1);
    }
    else
    {
        viewRect->_Scale(event->x(), event->y(), 0);
    }
    event->accept();
}

void CSovaMain::resizeEvent(QResizeEvent *)
{
    Resize();
}



void CSovaMain::Render()
{
    CEarthObject eObj;
    //qDebug() << Sat1.GetEarthObject(eObj, time(NULL));

    SLLACoordinate LLA = Sat1.GetPositionLLA(time(NULL));
    Satel->SetPosition(QPointF(LLA.Longitude, LLA.Latitude));
    LLA = GetSunPosition(time(NULL));
    sun->SetPosition(QPointF(LLA.Longitude, LLA.Latitude));

    //----------------------trace
    satTrace->setData(Sat1.GetTrace(time(NULL), 1920));
    //---------------------------
    //---------------terminator
    sunTerm->setData(GetTerminatorLine(time(NULL),1920));
    //-------------------------
    viewer->repaint();
}

void CSovaMain::Resize()
{
    viewer->setFixedSize(width(), height());
}

