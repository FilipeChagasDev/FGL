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
    BufferedPencil canvas(*display, Color(1,1,1), true, true);

    //canvas.drawLine(50,50,300,200,Color(0,0,0));
    //canvas.drawRoundedRectangle(100,100,100,100,20,Color(0,0,0));
    //canvas.drawCircle(150,150,100,Color(1,0,0));
    //canvas.drawEllipse(150,150,100,200,Color(0.5,0,1,0));
    //canvas.fillRectangle(10,10,100,100,Color(0.1,1,1,0));
    //canvas.fillCircle(200,200,50,Color(1,0,1,1));
    //canvas.fillEllipse(150,300,50,100,Color(1,0,1));
    //float px[4] = {10, 200, 50, 100};
    //float py[4] = {10, 10, 200, 250};
    //canvas.fillPolygon(px, py, 4, Color(1,0,0));

    /*
    float alpha = 0;
    for(int x = 50; x < this->display->getWidth(); x += 50)
    {
        for(int y = 50; y < this->display->getHeight(); y += 50)
        {
            canvas.fillArc(x, y, 0, alpha, 20, Color(1,0,0));
            alpha += 0.15;
        }
    }
    */

    /*
    float alpha = 0;
    for(int x = 50; x < this->display->getWidth(); x += 50)
    {
        for(int y = 50; y < this->display->getHeight(); y += 50)
        {
            canvas.fillSector(x, y, 0, alpha, 20, Color(1,0,0));
            alpha -= 0.15;
        }
    }
    */


    //canvas.fillArc(50, 50, 0, 0.75, 20, Color(1,0,0));

    //canvas.fillArc(150,150,0,3.14+3.14/2,50,Color(1,0,0));
    //canvas.fillArc(150,150,0,-3.14/2,50,Color(1,0,0));

    //canvas.fillRoundedRectangle(100,100,100,100,20,Color(0,0,0));

    float px[4] = {10, 200, 50, 100};
    float py[4] = {10, 10, 200, 250};
    canvas.drawPolygon(px, py, 4, Color(1,0,0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

