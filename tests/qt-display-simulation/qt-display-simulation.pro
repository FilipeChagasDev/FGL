QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fgl/base/array_search.cpp \
    fgl/base/ccw_sort.cpp \
    fgl/base/list.cpp \
    fgl/buffered_pencil.cpp \
    fgl/color.cpp \
    fgl/displays/display.cpp \
    fgl/fonts/font.cpp \
    fgl/framebuffer.cpp \
    fgl/image.cpp \
    fgl/pencil.cpp \
    images/logo.cpp \
    images/space1.cpp \
    images/space10.cpp \
    images/space2.cpp \
    images/space3.cpp \
    images/space4.cpp \
    images/space5.cpp \
    images/space6.cpp \
    images/space7.cpp \
    images/space8.cpp \
    images/space9.cpp \
    qt_fgl_display.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    fgl/base/array_search.hpp \
    fgl/base/ccw_sort.hpp \
    fgl/base/list.hpp \
    fgl/buffered_pencil.hpp \
    fgl/color.hpp \
    fgl/displays/display.hpp \
    fgl/fonts/font.hpp \
    fgl/framebuffer.hpp \
    fgl/image.hpp \
    fgl/pencil.hpp \
    images/logo.hpp \
    images/space1.hpp \
    images/space10.hpp \
    images/space2.hpp \
    images/space3.hpp \
    images/space4.hpp \
    images/space5.hpp \
    images/space6.hpp \
    images/space7.hpp \
    images/space8.hpp \
    images/space9.hpp \
    mainwindow.h \
    qt_fgl_display.hpp

INCLUDEPATH += fgl

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
