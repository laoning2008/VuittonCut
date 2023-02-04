#include "base/iconbutton.h"

QString circleStyleSheetTemplate = "QToolButton{border-radius:%1; border-style:outset;} QToolButton:hover {background-color:%2;}";
QString normalStyleSheetTemplate = "QToolButton:hover {background-color:%1;}";


IconButton::IconButton(QWidget *parent):QToolButton(parent)
{
    setCursor(QCursor(Qt::PointingHandCursor));
    this->connect(this, SIGNAL(toggled(bool)), this, SLOT(handleToggled(bool)));
}


void IconButton::setIcons(QPixmap defaultMap, QPixmap checkedMap, QPixmap hoverMap)
{
    this->defaultPix = defaultMap;
    this->checkedMap = checkedMap;
    this->hoverPix = hoverMap;
    if (isChecked()) {
        setIcon(QIcon(checkedMap));
    } else {
        setIcon(QIcon(defaultPix));
    }
}

void IconButton::setHoverBackground(QString backgroundColor, bool circle) {
    QString styleSheet;
    if (circle) {
        styleSheet = circleStyleSheetTemplate.arg(width()/2).arg(backgroundColor);
    } else {
        styleSheet = normalStyleSheetTemplate.arg(backgroundColor);
    }

    setStyleSheet(styleSheet);
}

void IconButton::enterEvent(QEvent *e)
{
    if (!isChecked()) {
        setIcon(QIcon(hoverPix));
    } else {
        setIcon(QIcon(checkedMap));
    }

    QToolButton::enterEvent(e);
}

void IconButton::leaveEvent(QEvent *e)
{
    if (!isChecked()) {
        setIcon(QIcon(defaultPix));
    } else {
        setIcon(QIcon(checkedMap));
    }

    QToolButton::leaveEvent(e);
}


void IconButton::handleToggled(bool checked) {
    if (checked) {
        setIcon(QIcon(checkedMap));
    } else {
        setIcon(QIcon(defaultPix));
    }
}
