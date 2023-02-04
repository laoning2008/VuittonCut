#include "base/imageutil.h"

namespace  util
{
namespace image
{
    QPixmap pixmapFromSvg(QString svg_path, QString color, QSize size) {
        QIcon img(svg_path);
        auto pixmap = img.pixmap(size);

        QPainter qp(&pixmap);
        qp.setCompositionMode(QPainter::CompositionMode_SourceIn);
        qp.setRenderHint(QPainter::HighQualityAntialiasing);
        qp.setRenderHint(QPainter::SmoothPixmapTransform);
        qp.fillRect(0, 0, size.width(), size.height(), QColor(color) );
        qp.end();

        return pixmap;
    }
}
}
