#ifndef GLMAPLOADER_H
#define GLMAPLOADER_H

#include <QSettings>
#include <vector>
#include <QPixmap>
#include <QImage>
#include "glviewrect.h"

class glMapLoader
{
public:
    glMapLoader();
    glMapLoader(QString mFileName);
    std::vector<QImage> LoadMap(glViewRect &ViewRect);
    void GetMapInfo(int* mWidth, int* mHeight, int* tWidth, int *tHeight);
private:
    int MapWidth;
    int MapHeight;
    int TileWidth;
    int TileHeight;
    int TileLineCount;
    int TileRowCount;
    QString TileFileName;

    int xStartTileNumber;
    int xEndTileNumber;
    int yStartTileNumber;
    int yEndTileNumber;
    QString MapFileName;
};

#endif // GLIMAGELOADER_H
