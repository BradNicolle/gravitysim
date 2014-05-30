#ifndef PLANET_H
#define PLANET_H

#include <QString>
#include <QImage>

class Planet {
public:
    Planet(QString, QString, double, double, double, double);
    QString getName();
    double getX();
    double getY();
    double getRadius();
    double getMass();
    QImage* getImage();
    void orbitStep();

private:
    QString name;
    QImage image;
    double mass;
    double x;
    double y;
    double radius;
};

#endif // PLANET_H
