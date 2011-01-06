#include "swMissile.h"
#include "swFactory.h"
#include "swPhysDeleteMsg.h"

#include <QGLWidget>

swMissile::swMissile() {
    type = SW_MISSILE;
    radius = 0.1;
}

swMissile::~swMissile() {}

void swMissile::draw() {
    glPushMatrix();
    transform();
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();
}

void swMissile::handleCollision(swPhysical* other) {
    swPhysDeleteMsg delMsg;
    delMsg.index = parent->objects.indexOf(this);
    swFactory::writeObject(&delMsg, owner->client->sock);
}
