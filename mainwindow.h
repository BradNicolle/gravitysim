#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include "canvas.h"


//comments please
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startSim();
    void addSolar();
    void addMission();
    
private:
    Ui::MainWindow *ui;
    Canvas* canvas;
};

#endif // MAINWINDOW_H
