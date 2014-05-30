#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include "planet.h"
#include "math.h"
#include "spacecraft.h"

class Canvas : public QWidget {
    Q_OBJECT

public:
    Canvas(QWidget *parent = 0);

    void addPlanet(Planet* planet);
    void addSpacecraft(Spacecraft* spacecraft);
    void removeSpacecraft();

public slots:
    //comments please
    void simulate(int time);
    void reset();

protected:
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    std::vector<Planet*> planets;
    std::vector<Spacecraft*> spacecrafts;
    QPolygonF path;
    QTimer* timer;
    double zoomAmount;
    long x;
    long y;
    long prevX;
    long prevY;
    long pressX;
    long pressY;
    bool firstRender;
    static const double G = 6.67384e-11;
    static const double PI = 3.14159265;
};

#endif // CANVAS_H
