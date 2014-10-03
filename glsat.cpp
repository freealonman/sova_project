#include "glsat.h"

glSat::glSat(const int& _Radius, const bool& _is_filled):glEObject(_Radius, _is_filled)
{

}


void glSat::draw(QPainter *_painter)
{
    //отрисовка трассы спутника

    //-------------------------
    //отрисовка текущегно положения
   glEObject::draw(_painter);
}



void glSat::drawText(QPainter *_painter)
{
    glEObject::drawText(_painter);
    //QRect doRect()
}
