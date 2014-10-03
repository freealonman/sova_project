#include "gltext.h"



glText::glText()
{
    _rect = QRect(0, 0, 100, 100);
    _font.setPointSize(12);
    _font.setFamily("Calibri");
    _pen.setColor(Qt::black);
}

glText::glText(const QRect &rect):glText()
{
    _rect = rect;
}
glText::glText(const QString &text, const QRect& rect):glText(rect)
{
    append(text);
}

glText::glText(const QString &text, const QRect &rect, const int &font_size):glText(text, rect)
{
    _font.setPointSize(font_size);
}

glText::glText(const QString &text, const QRect &rect, const int &font_size, const QPen &font_color):glText(text, rect, font_size)
{
    _pen = font_color;
}

glText::glText(const QString &text, const QRect &rect, const int &font_size, const QPen &font_color, const QString &font_family):glText(text,rect,
                                                                                                                                        font_size,
                                                                                                                                        font_color)
{
    _font.setFamily(font_family);
}

void glText::SetRect(const QRect &rect)
{
    _rect = rect;
}
void glText::SetFont(const QFont &font)
{
    _font = font;
}
void glText::SetPen(const QPen &pen)
{
    _pen = pen;
}

QRect* glText::GetRect()
{
    return &_rect;
}

QFont* glText::GetFont()
{
    return &_font;
}

QPen* glText::GetPen()
{
    return &_pen;
}

void glText::append(const QString &s)
{
    clear();
    QString::append(s);
}
