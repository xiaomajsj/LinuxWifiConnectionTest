#ifndef RESIZE_H
#define RESIZE_H

#include <QWidget>

class Resize
{
public:
    Resize();

    void ObjectResize(QWidget *object, double resizeParameterW, double resizeParameterH);
    void IconResize(QWidget *object, double resizeParameterW, double resizeParameterH);
    void IconResize2(QWidget *object, double resizeParameterW, double resizeParameterH);
    void resizeFont(QWidget *object, QString fontfamily, int originsize, double resizeParameterW, double resizeParameterH);
    void ReroundCorners(QWidget *object, int roundprecentX, int roundprecentY);
};

#endif // RESIZE_H
