#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include "planet.h"
#include "spacecraft.h"
#include "trajectory.h"

class Spacecraft {
public:
    Spacecraft(Trajectory* a_traj);
    double getX();
    double getY();
    void setX(double);
    void setY(double);
    double getXVel();
    double getYVel();
    void applyImpulse(double x_acc, double y_acc, int time);
    void halt();

private:
    Trajectory* trajectory;
    int time;
    double x;
    double y;
    double x_v;
    double y_v;
    static const double PI = 3.14159265;
    bool halted;
};

#endif // SPACECRAFT_H
