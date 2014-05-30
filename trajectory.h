#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <QMap>
#include "manoeuvre.h"

class Trajectory {
public:
    Trajectory();
    Trajectory(double x, double y, double vx, double vy);
    void addPoint(long time, double deltaV, double heading);
    QMap<long, Manoeuvre*>* getPoints();
    void setX(double x);
    void setY(double y);
    void setXVel(double vx);
    void setYVel(double vy);

    double xPos;
    double yPos;
    double xVel;
    double yVel;

private:
    QMap<long, Manoeuvre*> points;
};

#endif // TRAJECTORY_H
