#include "swDebris.h"
#include "swSimulator.h"
#include <QGLWidget>

swDebris::swDebris() {
    type = SW_DEBRIS;
    colType = 1;
}

swDebris::~swDebris() {}

void swDebris::handleCollision(swPhysical* other) {
    // these immediately remove themselves
    if(other->type != SW_DEBRIS)
	parent->remove(parent->objects.indexOf(this));
}

bool swDebris::collide(swPhysical* other) {
    // TODO: single line collision
    return swPhysical::collide(other);
}

void swDebris::draw() {
    glPushMatrix();
    transform();
    glBegin(GL_LINES);
    glVertex2d(1, 0);
    glVertex2d(-1, 0);
    glEnd();
    glPopMatrix();
}
