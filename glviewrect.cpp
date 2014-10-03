#include "glviewrect.h"

glViewRect::glViewRect(int ImageWidth, int ImageHeight, int ViewPortWidth, int ViewPortHeight):QImage()
{
    ScaleValue = 0;
    ImageRect.setCoords(0, 0, ImageWidth, ImageHeight);
    ViewPortRect.setCoords(0, 0, ViewPortWidth, ViewPortHeight);
    file_mask ="";
    x_start = 0;
    y_start = 0;
    x_end   = 0;
    y_end   = 0;
}

QImage* glViewRect::_Scale(int xCenter, int yCenter, int Value)
{
    ScaleValue = Value;
    switch (ScaleValue)

    {
    case 0:
    {
        CurrentRect = ViewPortRect;
        break;
    }
    case 1:
    {
        xC = xCenter * (ImageRect.width()/ViewPortRect.width());
        yC = yCenter * (ImageRect.height()/ViewPortRect.height());
        CurrentRect.setLeft(xC - ViewPortRect.width()/2);
        CurrentRect.setRight(xC + ViewPortRect.width()/2);
        CurrentRect.setTop(yC - ViewPortRect.height()/2);
        CurrentRect.setBottom(yC + ViewPortRect.height()/2);
        break;
    }
    }

    Load();
    return this;

}

QImage *glViewRect::_Move(double X, double Y)
{

    switch(ScaleValue)
    {
    case 0:
    {
        CurrentRect = ViewPortRect;
        break;
    }
    case 1:
    {
        //if ((CurrentRect.right()  + X) > ImageRect.right())  {X = ImageRect.right()  - CurrentRect.right(); }
        //if ((CurrentRect.bottom() + Y) > ImageRect.bottom()) {Y = ImageRect.bottom() - CurrentRect.bottom();}
        CurrentRect.setCoords(CurrentRect.left() + X, CurrentRect.top() + Y, CurrentRect.right() + X, CurrentRect.bottom() + Y);
        break;
    }
    }
    Load();
    return this;
}

void glViewRect::Load()
{
    switch(ScaleValue)
    {
    case 0:
    {
        x_start = 0;
        y_start = 0;
        x_end   = 0;
        y_end   = 0;
        break;
    }
    case 1:
    {
        x_start = CurrentRect.left()/1000;
        x_end   = CurrentRect.right()/1000;
        y_start = CurrentRect.top()/1000;
        y_end   = CurrentRect.bottom()/1000;

        for (int i = x_start; i <= x_end; i++)
        {
            for (int j = y_start; j <=y_end; j++)
            {
                QString file_name = file_mask;
                file_name.replace('X', QString::number(i));
                file_name.replace('Y', QString::number(j));
               // QImage image(file_name);
                //QPainter painter(&image);
                //painter.begin();
               // painter.drawImage();
                //painter.end();

            }
        }
        break;
    }
    }

}


QImage* glViewRect::GetImageRect()
{
    return this;
}

QRect& glViewRect::GetTileNumbers()
{
    QRect r;
    r.setCoords(x_start, y_start, x_end, y_end);
    return r;
}

QRect &glViewRect::GetCurrentRect()
{
    return CurrentRect;
}
