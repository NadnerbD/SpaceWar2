#include <cmath>
#include <QGLWidget>
#include "swDrawable.h"

swDrawable::swDrawable(double px, double py, double r, double sx, double sy) : scale(sx, sy), pos(px, py), rot(r) {
    type = SW_DRAWABLE;
}

swDrawable::~swDrawable() {}

void swDrawable::draw() {
    glPushMatrix();
    transform();
    // draw... nothing
    glPopMatrix();
}

void swDrawable::transform() {
    glTranslated(pos.x, pos.y, 0);
    glRotated(rot * 180.0 / M_PI, 0, 0, 1);
    glScaled(scale.x, scale.y, 1);
}

void swDrawable::read(swStream* stream) {
    scale.read(stream);
    pos.read(stream);
    stream->readDouble(rot);
}

void swDrawable::write(swStream* stream) {
    scale.write(stream);
    pos.write(stream);
    stream->writeDouble(rot);
}
