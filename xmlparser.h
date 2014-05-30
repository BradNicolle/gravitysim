#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "planet.h"
#include "spacecraft.h"
#include <QFile>
#include <QXmlStreamReader>

class XMLParser
{
public:
    XMLParser(QWidget* parent);
    bool load();
    QVector<Planet*> parsePlanets();
    Spacecraft* parseSpacecraft();

private:
    Planet* singlePlanet(QXmlStreamReader& xml);
    Spacecraft* singleSpacecraft(QXmlStreamReader& xml);
    QFile* file;
    QWidget* parent;

};

#endif // XMLPARSER_H
