#ifndef GLTEXT_H
#define GLTEXT_H
#include <QString>
#include <QRect>
#include <QFont>
#include <QPen>

class glText:public QString
{
public:
    glText();
    glText(const QRect& rect);
    glText(const QString& text, const QRect &rect);
    glText(const QString &text, const QRect &rect, const int& font_size);
    glText(const QString &text, const QRect &rect, const int &font_size, const QPen& font_color);
    glText(const QString &text, const QRect &rect, const int &font_size, const QPen &font_color, const QString& font_family);

    void   SetRect(const QRect& rect);
    void   SetFont(const QFont& font);
    void   SetPen(const QPen& pen);
    QRect* GetRect();
    QFont* GetFont();
    QPen*  GetPen();
    virtual void append(const QString &s);
private:
    QRect   _rect;
    QFont   _font;
    QPen    _pen;
};

#endif // GLTEXT_H
