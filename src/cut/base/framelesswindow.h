#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QMainWindow>

class FramelessWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FramelessWindow(QWidget *parent = nullptr);

protected:
    void mergeTitlebar();
    void centerWindow();
};

#endif
