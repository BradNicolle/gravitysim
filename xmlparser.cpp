#include "xmlparser.h"
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>

XMLParser::XMLParser(QWidget* parent) : parent(parent) {

}

bool XMLParser::load() {
    file = new QFile(QFileDialog::getOpenFileName(parent));
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        //QMessageBox::critical(this, "MainWindow::loadInputFile", "Couldn't open file", QMessageBox::Ok);
        return false;
    }
    return true;
}

QVector<Planet*> XMLParser::parsePlanets() {
    QVector<Planet*> ret;
    QXmlStreamReader xml(file);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument) {
            continue;
        }
        if (token == QXmlStreamReader::StartElement) {
            if (xml.name() == "planets") {
                continue;
            }
            if (xml.name() == "planet") {
                ret.push_back(singlePlanet(xml));
            }
        }
    }

    if (xml.hasError()) {
        //QMessageBox::critical(this, "MainWindow::loadInputFile", xml.errorString(), QMessageBox::Ok);
    }
    xml.clear();

    return ret;
}

Spacecraft* XMLParser::parseSpacecraft() {
    QXmlStreamReader xml(file);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument) {
            continue;
        }
        if (token == QXmlStreamReader::StartElement) {
            if (xml.name() == "spacecraft") {
                return singleSpacecraft(xml);
            }
        }
    }
    if (xml.hasError()) {
        //QMessageBox::critical(this, "MainWindow::loadInputFile", xml.errorString(), QMessageBox::Ok);
    }
    xml.clear();

    return NULL;
}

Planet* XMLParser::singlePlanet(QXmlStreamReader& xml) {

    if(xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "planet") {
        return NULL;
    }

    /* Next element... */
    xml.readNext();
    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named person.
     */
    QString name;
    QString image;
    double mass = 0.0;
    double radius = 0.0;
    double x = 0.0;
    double y = 0.0;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "planet")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            if(xml.name() == "name") {
                xml.readNext();
                name = xml.text().toString();
            }

            if(xml.name() == "image") {
                xml.readNext();
                image = xml.text().toString();
            }

            if(xml.name() == "mass") {
                xml.readNext();
                mass = xml.text().toString().toDouble();
            }

            if(xml.name() == "radius") {
                xml.readNext();
                radius = xml.text().toString().toDouble();
            }

            if(xml.name() == "x") {
                xml.readNext();
                x = xml.text().toString().toDouble();
            }

            if(xml.name() == "y") {
                xml.readNext();
                y = xml.text().toString().toDouble();
            }

        }
        /* ...and next... */
        xml.readNext();
    }
    Planet* planet = new Planet(name, image, mass, radius, x, y);
    return planet;
}

Spacecraft* XMLParser::singleSpacecraft(QXmlStreamReader& xml) {

    if(xml.tokenType() != QXmlStreamReader::StartElement &&
            xml.name() == "spacecraft") {
        return NULL;
    }

    /* Next element... */
    xml.readNext();
    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named person.
     */

    Trajectory* traj = new Trajectory();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
            xml.name() == "spacecraft")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            if(xml.name() == "xPos") {
                xml.readNext();
                traj->setX(xml.text().toDouble());
                std::cout << "added xpos" << std::endl;
            }

            if(xml.name() == "yPos") {
                xml.readNext();
                traj->setY(xml.text().toDouble());
                std::cout << "added ypos" << std::endl;
            }

            if(xml.name() == "xVel") {
                xml.readNext();
                traj->setXVel(xml.text().toDouble());
                std::cout << "added xvel" << std::endl;
            }

            if(xml.name() == "yVel") {
                xml.readNext();
                traj->setYVel(xml.text().toDouble());
                std::cout << "added yvel" << std::endl;
            }

            if(xml.name() == "point") {
                xml.readNext();
                long time = 0;
                double deltaV = 0;
                double heading = 0;
                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "point")) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
                        if (xml.name() == "time") {
                            xml.readNext();
                            time = xml.text().toLong();
                            std::cout << "added time " << time << std::endl;
                        }
                        if (xml.name() == "deltav") {
                            xml.readNext();
                            deltaV = xml.text().toDouble();
                            std::cout << "added deltav " << deltaV << std::endl;
                        }
                        if (xml.name() == "heading") {
                            xml.readNext();
                            heading = xml.text().toDouble();
                            std::cout << "added heading " << heading << std::endl;
                        }
                    }
                    xml.readNext();
                }
                traj->addPoint(time, deltaV, heading);
                std::cout << "added point" << std::endl;
            }

        }
        /* ...and next... */
        xml.readNext();
    }

    Spacecraft* spacecraft = new Spacecraft(traj);
    return spacecraft;
}
