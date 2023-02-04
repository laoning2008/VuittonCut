#include "view/mainwindow.h"
#include "ui_mainwindow.h"
#include <engine.hpp>

MainWindow::MainWindow(QWidget *parent)
    : FramelessWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

