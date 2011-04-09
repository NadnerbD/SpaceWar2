#include "swShipMenu.h"

#include <QDir>

swShipMenu::swShipMenu(swGame* g) : game(g) {
    QDir dataDir("data");
    QStringList fileNames = dataDir.entryList(QStringList("*.shp"), QDir::Files, QDir::Name);
    for(int i = 0; i < fileNames.length(); i++) {
        QString fileName = fileNames[i];
        swMesh* ship = new swMesh("data/" + fileName);
        ship->scale = swVector(0.25, 0.25);
        ship->pos.x = (double)i * 0.5;
        ships.append(ship);
    }
}

swShipMenu::~swShipMenu() {
    foreach(swMesh* ship, ships)
        delete ship;
}

void swShipMenu::draw() {
    glPushMatrix();
    transform();
    foreach(swMesh* ship, ships)
        ship->draw();
    glPopMatrix();
}

void swShipMenu::keyHandle(QKeyEvent* event) {
}

void swShipMenu::mouseHandle(QMouseEvent* event) {
}
