#pragma once

#include <QPainter>
#include <QIcon>
#include <QPixmap>

namespace  util {
namespace image {
    QPixmap pixmapFromSvg(QString svg_path, QString color, QSize size);
    bool GeneratePixmapFromText(QString &text, QPixmap &pixmap, int width, int height);
}
}
