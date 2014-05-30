#include "planet.h"
#include "math.h"

Planet::Planet(QString aname, QString aimage, double amass, double aradius, double ax, double ay) {
    name = aname;
    image.load(aimage);
    mass = amass;
    radius = aradius;
    x = ax;
    y = ay;
}

QString Planet::getName() {
    return name;
}

double Planet::getX() {
    return x;
}

double Planet::getY() {
    return y;
}

double Planet::getRadius() {
    return radius;
}

double Planet::getMass() {
    return mass;
}

QImage* Planet::getImage() {
    return &image;
}

void orbitStep() {

}
