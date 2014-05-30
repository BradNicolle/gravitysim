#include "spacecraft.h"
#include "trajectory.h"
#include "manoeuvre.h"
#include <cmath>
#include <iostream>

Spacecraft::Spacecraft(Trajectory* a_traj)
{
    trajectory = a_traj;
    x = trajectory->xPos;
    y = trajectory->yPos;
    x_v = trajectory->xVel;
    y_v = trajectory->yVel;

    time = 0;

    halted = false;
}

double Spacecraft::getX() {
    return x;
}

double Spacecraft::getY() {
    return y;
}

void Spacecraft::setX(double setx) {
    x = setx;
}

void Spacecraft::setY(double sety) {
    y = sety;
}

double Spacecraft::getXVel() {
    return x_v;
}

double Spacecraft::getYVel() {
    return y_v;
}

void Spacecraft::applyImpulse(double x_acc, double y_acc, int a_time) {
    time += a_time;
    if (!halted) {
        x_v += x_acc * a_time;
        y_v += y_acc * a_time;
        x += x_v * a_time;
        y += y_v * a_time;
        if (trajectory->getPoints()->contains(time)) {
            std::cout << "Entry found: " << time << "s" << std::endl;
            Manoeuvre* man = trajectory->getPoints()->find(time).value();
            x_v += (man->deltaV) * cos((180/PI)*(man->heading));
            y_v += (man->deltaV) * sin((180/PI)*(man->heading));
        }
    }
}

void Spacecraft::halt() {
    halted = true;
    x_v = 0;
    y_v = 0;
}
