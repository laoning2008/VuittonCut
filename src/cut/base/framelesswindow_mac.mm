#include "base/framelesswindow.h"
#include <QApplication>
#import <AppKit/AppKit.h>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QScreen>

FramelessWindow::FramelessWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mergeTitlebar();
}


void FramelessWindow::mergeTitlebar()
{
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);

    NSView* view = (NSView *)winId();
    NSWindow* window = [view window];

    window.titlebarAppearsTransparent = YES;
    window.titleVisibility = NSWindowTitleHidden;
    window.styleMask |= NSWindowStyleMaskFullSizeContentView;

    setStyleSheet("background-color:white;");
}


void FramelessWindow::centerWindow()
{
    int currentScreen = QApplication::desktop()->screenNumber(this);
    QRect rect = QApplication::desktop()->screenGeometry(currentScreen);
//    QRect rect = screen()->geometry();
    move((rect.width() - width()) / 2, (rect.height() - height()) / 2);
}
