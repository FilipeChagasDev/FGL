#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>
#include <QColor>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->display = new QtFGLDisplay(this->ui->graphicsView->width(),this->ui->graphicsView->height(), 50, 50);
    ui->graphicsView->setScene(&this->display->scene);

    this->display->init();

    //Pencil canvas(*display);
    BufferedPencil canvas(*display, Color(1,1,1));
    canvas.drawLine(50,50,300,200,Color(0,0,0));
    canvas.drawRoundedRectangle(100,100,100,100,20,Color(0,0,0));
    canvas.drawCircle(150,150,100,Color(1,0,0));
    canvas.drawEllipse(150,150,100,200,Color(0.5,0,1,0));
}
MainWindow::~MainWindow()
{
    delete ui;
}

