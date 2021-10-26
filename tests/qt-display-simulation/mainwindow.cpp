#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>
#include <QColor>
#include <image.hpp>
#include "images/space1.hpp"
#include "images/space2.hpp"
#include "images/space3.hpp"
#include "images/space4.hpp"
#include "images/space5.hpp"
#include "images/space6.hpp"
#include "images/space7.hpp"
#include "images/space8.hpp"
#include "images/space9.hpp"
#include "images/space10.hpp"
#include "images/logo.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->display = new QtFGLDisplay(this->ui->graphicsView->width(),this->ui->graphicsView->height(), 50, 50);
    ui->graphicsView->setScene(&this->display->scene);

    this->display->init();

    //Pencil canvas(*display);
    this->canvas = new BufferedPencil(*display, Color(0,0,0), true, true);
    this->canvas->fillRectangle(0,0,this->display->getWidth(), this->display->getHeight(), Color(0,0,0));

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

    //float px[4] = {10, 200, 50, 100};
    //float py[4] = {10, 10, 200, 250};
    //canvas.drawPolygon(px, py, 4, Color(1,0,0));

    //ImageARGB8888 pic(100, 100);
    //ImageARGB1555 pic(100, 100);
    //ImageRGB565 pic(100, 100);

    /*
    ImageK8 pic(100, 100);
    int k = 0;
    for(int a = 0; a < 4; a++)
    {
        for(int r = 0; r < 4; r++)
        {
            for(int g = 0; g < 4; g++)
            {
                for(int b = 0; b < 4; b++)
                {
                    pic.color_map[k++] = new Color((float)a/3, (float)r/3, (float)g/3, (float)b/3);
                }
            }
        }
    }

    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            //pic.setPixel(i, j, Color((float)(i*j)/10000.0, (float)i/100.0, 0, (float)j/100.0));
            pic.setPixel(i, j, Color((float)i/100.0, 0, (float)j/100.0));
        }
    }

    canvas.drawImage(100, 100, pic);
    */

}

void MainWindow::draw()
{
    Image *img = get_logo_image();
    //canvas->fillRoundedRectangle(100,100,100,100,20,Color(0,0,0));
    this->canvas->drawImage(10, 10, *img);
    this->canvas->drawRoundedRectangle(5,5, img->getWidth()+10, img->getHeight()+10, 5, Color(1,1,1));
}

MainWindow::~MainWindow()
{
    delete ui;
}

