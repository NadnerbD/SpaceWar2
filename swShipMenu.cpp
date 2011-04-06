#include "swShipMenu.h"

swShipMenu::swShipMenu(swGame* g) : game(g) {
}

swShipMenu::~swShipMenu() {}

void swShipMenu::draw() {
    glPushMatrix();
    transform();
    glPopMatrix();
}

void swShipMenu::keyHandle(QKeyEvent* event) {
}

void swShipMenu::mouseHandle(QMouseEvent* event) {
}
