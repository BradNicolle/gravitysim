#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include "spacecraft.h"
#include "planet.h"
#include "xmlparser.h"
#include <QSpinBox>
#include "trajectory.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("GravitySim");
    setWindowIcon(QIcon(":/earth.png"));
    setMinimumSize(800,600);
    canvas = new Canvas(ui->centralWidget);

    ui->verticalLayout->insertWidget(0, canvas);
    connect(ui->simButton, SIGNAL(clicked()), this, SLOT(startSim()));
    connect(ui->resetButton, SIGNAL(clicked()), canvas, SLOT(reset()));
    connect(ui->loadSolar, SIGNAL(clicked()), this, SLOT(addSolar()));
    connect(ui->loadMission, SIGNAL(clicked()), this, SLOT(addMission()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startSim() {
    canvas->simulate(ui->simTime->value());
}

void MainWindow::addSolar() {
    canvas->reset();
    XMLParser solarsystem(this);
    solarsystem.load();
    QVector<Planet*> planets = solarsystem.parsePlanets();
    for (int i = 0; i < planets.size(); i++) {
        canvas->addPlanet(planets[i]);
    }
}

void MainWindow::addMission() {
    canvas->reset();
    XMLParser mission(this);
    mission.load();
    canvas->addSpacecraft(mission.parseSpacecraft());
}
