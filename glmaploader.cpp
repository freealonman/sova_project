#include "glmaploader.h"


glMapLoader::glMapLoader()
{

}

glMapLoader::glMapLoader(QString mFileName)
{
    MapFileName = mFileName;
    QSettings set1(mFileName ,QSettings::IniFormat);
    set1.beginGroup("MAP_FILE_INFO");
    MapWidth   = set1.value("mapWidth").toInt();
    MapHeight  = set1.value("mapHeight").toInt();
    TileWidth  = set1.value("tileWidth").toInt();
    TileHeight = set1.value("tileHeight").toInt();
    TileFileName = set1.value("tilePath").toString();
}

std::vector<QImage> glMapLoader::LoadMap(glViewRect & ViewRect)
{
    std::vector<QImage> qim;
    int x1, x2, y1, y2 = 0;
    //ViewRect.GetImageRect().getCoords(&x1, &y1, &x2, &y2);
    xStartTileNumber = x1 / TileWidth;
    xEndTileNumber   = x2 / TileWidth;
    yStartTileNumber = y1 / TileHeight;
    yEndTileNumber   = y2 / TileHeight;

    for (int i = xStartTileNumber; i <= xEndTileNumber; i++)
         for (int j = yStartTileNumber; j <= yEndTileNumber; j++)
         {
             QPixmap pix = QPixmap(TileFileName + "[" + QString::number(i) + "]" + "[" + QString::number(j) + "].png");
             qim.push_back(pix.toImage());
         }

    return qim;

}

void glMapLoader::GetMapInfo(int *mWidth, int *mHeight, int *tWidth, int* tHeight)
{
    *mWidth  = MapWidth;
    *mHeight = MapHeight;
    *tWidth  = TileWidth;
    *tHeight = TileHeight;
}
