#include "qt_fgl_display.hpp"

QtFGLDisplay::QtFGLDisplay(size_t w, size_t h, float dpix, float dpiy)
{
    this->w = w;
    this->h = h;
    this->dpmmx = dpix * 25*4;
    this->dpmmy = dpiy * 25*4;
}

const char *QtFGLDisplay::getName()
{
    return "Qt-FGL-Display";
}

uint32_t QtFGLDisplay::getWidth()
{
    return this->w;
}

uint32_t QtFGLDisplay::getHeight()
{
    return this->h;
}

float QtFGLDisplay::getDPMMX()
{
    return this->dpmmx;
}

float QtFGLDisplay::getDPMMY()
{
    return this->dpmmy;
}

void QtFGLDisplay::setBrightness(float v)
{
    //TODO
}

float QtFGLDisplay::getBrightness()
{
    //TODO
    return 1;
}

void QtFGLDisplay::setOrientation(Orientation orientation)
{
    //TODO
}

Orientation QtFGLDisplay::getOrientation()
{
    //TODO
    return Orientation::V;
}

void QtFGLDisplay::init()
{
    this->drawPixel(0,0,1,1,1);
}

void QtFGLDisplay::reset()
{
    this->scene.clear();
}

void QtFGLDisplay::select()
{
    //TODO
}

void QtFGLDisplay::unselect()
{
    //TODO
}

bool QtFGLDisplay::drawPixel(int x, int y, float r, float g, float b)
{
    if(x < this->getWidth() and y < this->getHeight())
    {
        this->scene.addLine(x, y, x, y, QPen(QColor(r*255,g*255,b*255)));
        return true;
    }
    else return false;
}

bool QtFGLDisplay::drawArea(int x1, int y1, int x2, int y2, float r, float g, float b)
{
    if(x1 < this->getWidth() and y1 < this->getHeight() and x2 > x1 and y2 > y1)
    {
        this->scene.addRect(x1, y1, x2-x1, y2-y1, QPen(QColor(r,g,b)), QBrush(QColor(r,g,b)));
        return true;
    }
    else return false;
}

QtFGLDisplay::~QtFGLDisplay()
{
    //TODO
}


