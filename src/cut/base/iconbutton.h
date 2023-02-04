#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QToolButton>
#include <QtCore>
#include <QtGui>
#include <QIcon>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QFont>
#include <QFontMetrics>
#include <cmath>

#define MODE_DEFAUT 0
#define MODE_PRESSED 1
#define MODE_HOVER 2

#define TYPE_PUSHBUTTON 0
#define TYPE_ICONBUTTON 1

class IconButton : public QToolButton
{
    Q_OBJECT
public:
    IconButton(QWidget *parent = nullptr);

    void setIcons(QPixmap defaultMap, QPixmap checkedMap, QPixmap hoverMap);
    void setHoverBackground(QString backgroundColor, bool circle);
protected:
    void enterEvent(QEvent *e)override;
    void leaveEvent(QEvent *e)override;
private slots:
    void handleToggled(bool checked);
private:
    QPixmap defaultPix;
    QPixmap checkedMap;
    QPixmap hoverPix;
};

#endif // ICONBUTTON_H
