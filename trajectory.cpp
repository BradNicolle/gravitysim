#include "trajectory.h"

Trajectory::Trajectory() {
    xPos = 0;
    yPos = 0;
    xVel = 0;
    yVel = 0;
}

Trajectory::Trajectory(double x, double y, double vx, double vy) {
    xPos = x;
    yPos = y;
    xVel = vx;
    yVel = vy;
}

void Trajectory::addPoint(long time, double deltaV, double heading) {
    Manoeuvre* man = new Manoeuvre();
    man->deltaV = deltaV;
    man->heading = heading;
    points.insert(time, man);
}

QMap<long, Manoeuvre*>* Trajectory::getPoints() {
    return &points;
}

void Trajectory::setX(double x) {
    xPos = x;
}

void Trajectory::setY(double y) {
    yPos = y;
}

void Trajectory::setXVel(double vx) {
    xVel = vx;
}

void Trajectory::setYVel(double vy) {
    yVel = vy;
}
