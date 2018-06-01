#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionbat,
            SIGNAL(triggered(bool)),
            this,
            SLOT(backColor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::backColor()
{
    QColor color;
    QColorDialog cd;
    cd.exec();
    color=cd.getColor();
    ui->tela->setBackColor(color);
}
