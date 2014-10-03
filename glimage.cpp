#include "glimage.h"

glImage::glImage():glRenderable()
{

   image = new QImage("E:\\Sources\\SModel\\EARTH_MAPS\\world.topo.bathy.200401.3x5400x2700.png");
   qDebug() << image->width();
}

void glImage::draw(QPainter *_painter)
{
    _painter->save();
    QRect r(0,0, 1920, 1080);
    _painter->drawImage(r,*image);
    _painter->restore();
}
