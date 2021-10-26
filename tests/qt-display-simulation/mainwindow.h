#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qt_fgl_display.hpp"
#include <buffered_pencil.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void draw();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    BufferedPencil *canvas;
    QtFGLDisplay *display;
};
#endif // MAINWINDOW_H
