#include <QGLWidget>

#include "swStar.h"
#include "swSimulator.h"

swStar::swStar() : gravity(0.04) {
    type = SW_STAR;
    radius = 0.2;
}

swStar::~swStar() {}

void swStar::read(swStream* stream) {
    swPhysical::read(stream);
    stream->readDouble(gravity);
}

void swStar::write(swStream* stream) {
    swPhysical::write(stream);
    stream->writeDouble(gravity);
}

void swStar::draw() {
    glPushMatrix();
    transform();
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();
}

void swStar::tick() {
    swPhysical::tick();
    foreach(swPhysical* object, parent->objects) {
	if(object && object != this) {
	    swVector diff = pos - object->pos;
	    double accel = gravity * swSimulator::tickScale / (diff * diff); // G / dist^2
	    object->vel += diff.normalize() * accel;
	}
    }
}
