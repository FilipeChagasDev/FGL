#ifndef QTFGLDISPLAY_HPP
#define QTFGLDISPLAY_HPP

#include <displays/display.hpp>
#include <QGraphicsScene>

class QtFGLDisplay : public Display
{
protected:
    size_t w, h;
    float dpmmx, dpmmy;

public:
    QGraphicsScene scene;
    QtFGLDisplay(size_t w, size_t h, float dpix, float dpiy);

    //Name
    const char *getName();

    //Properties
    uint32_t getWidth();
    uint32_t getHeight();
    float getDPMMX();
    float getDPMMY();

    //Brightness
    void setBrightness(float v);
    float getBrightness();

    //Orientation
    void setOrientation(Orientation orientation);
    Orientation getOrientation();

    //Actions
    void init();
    void reset();
    void select();
    void unselect();
    bool drawPixel(int x, int y, float r, float g, float b);
    bool drawArea(int x1, int y1, int x2, int y2, float r, float g, float b);

    //Destructor
    virtual ~QtFGLDisplay();
};

#endif // QTFGLDISPLAY_HPP
