#ifndef GLVIEWRECT_H
#define GLVIEWRECT_H

#include <QRect>
#include <QImage>
#include <QPainter>



class glViewRect:public QImage
{
public:
    glViewRect(int ImageWidth, int ImageHeight, int ViewPortWidth, int ViewPortHeight);
    QImage*  _Scale(int xCenter, int yCenter, int Value); //between 0.0 - 100.0
    QImage*  _Move (double X, double Y);
    QImage*  GetImageRect();
    QRect&    GetTileNumbers();
    QRect&   GetCurrentRect();

private:
    QRect  ImageRect;
    QRect  ViewPortRect;
    QRect  CurrentRect;
    int ScaleValue;
    int xC;
    int yC;

    //-----------------------view image array
    int l_count;
    int r_count;

    int x_start;
    int x_end;
    int y_start;
    int y_end;

    QString       file_mask;
    void Load();

};

#endif // GLVIEWRECT_H
