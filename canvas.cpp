#include "canvas.h"
#include <QPainter>
#include <QTimer>
#include <vector>
#include "math.h"
#include <QRect>
#include <QImage>
#include <QKeyEvent>

Canvas::Canvas(QWidget* parent) : QWidget(parent) {
    QPalette Pal(palette());
    // set black background
    Pal.setColor(QPalette::Background, Qt::
                 black);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->setFocusPolicy(Qt::StrongFocus);
    zoomAmount = 0.00001;
    firstRender = true;
    timer = new QTimer(this);
}

void Canvas::reset() {
    path.clear();
    removeSpacecraft();
    zoomAmount = 0.00001;
    x = width()/2;
    y = height()/2;
    repaint();
}

void Canvas::addPlanet(Planet* planet) {
    planets.push_back(planet);
}

void Canvas::addSpacecraft(Spacecraft* spacecraft) {
    spacecrafts.push_back(spacecraft);
    repaint();
}

void Canvas::removeSpacecraft() {
    for (unsigned int i = 0; i < spacecrafts.size(); i++) {
        delete spacecrafts[i];
    }
    spacecrafts.clear();
}

void Canvas::simulate(int time) {
    path.clear();
    for (int t = 0; t < time; t++) {
        for (unsigned int i = 0; i < spacecrafts.size(); i++) {
            double acc_vec[2] = {0,0};
            for (unsigned int j = 0; j < planets.size(); j++) {
                double r_abs = sqrt(pow(planets[j]->getX()-spacecrafts[i]->getX(), 2) + pow(planets[j]->getY()-spacecrafts[i]->getY(), 2));
                double rx_unit = (planets[j]->getX() - spacecrafts[i]->getX())/r_abs;
                double ry_unit = (planets[j]->getY() - spacecrafts[i]->getY())/r_abs;
                double force_abs = (planets[j]->getMass()*G)/pow(r_abs, 2);
                acc_vec[0] += rx_unit*force_abs;
                acc_vec[1] += ry_unit*force_abs;
            }
            spacecrafts[i]->applyImpulse(acc_vec[0], acc_vec[1], 1);
            if (t % 120 == 0) {
                path << QPointF(spacecrafts[i]->getX()/100000, spacecrafts[i]->getY()/100000);
            }
        }
    }
    repaint();
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush(Qt::white);
    QPen pen;
    pen.setWidth(0);
    pen.setBrush(Qt::white);
    painter.setBrush(brush);
    painter.setPen(pen);

    if (firstRender) {
        x = width()/2;
        y = height()/2;
        firstRender = false;
    }
    painter.translate(x, y);
    painter.scale(zoomAmount,zoomAmount);
    painter.drawPolyline(path);
    for (unsigned int i = 0; i < planets.size(); i++) {
        double radius = planets[i]->getRadius();
        painter.drawImage(QRectF(planets[i]->getX()-radius,planets[i]->getY()-radius,radius*2,radius*2),*(planets[i]->getImage()));
        painter.drawText(QPointF(planets[i]->getX()+radius, planets[i]->getY()+radius),planets[i]->getName());
    }

}

//comments please

void Canvas::wheelEvent(QWheelEvent *event) {
    double amount = event->angleDelta().y();
    if (amount > 0 && zoomAmount < 0.0001) {
        zoomAmount *= 2;
    }
    else if (amount < 0) {
        zoomAmount *= 0.5;
    }
    event->accept();
    repaint();
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    pressX = event->pos().x();
    pressY = event->pos().y();
    prevX = x;
    prevY = y;
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    x = prevX+ event->pos().x() - pressX;
    y = prevY + event->pos().y() - pressY;
    repaint();
}
