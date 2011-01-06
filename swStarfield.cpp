#include <cmath>
#include <QFile>
#include <QGLWidget>
#include "swStarfield.h"

swStarfield::swStarfield() : swDrawable(0, 0, 0, 2, 2) {
    type = SW_STARFIELD;
}

swStarfield::swStarfield(QString file) : swDrawable(0, 0, 0, 2, 2) {
    swObject::read(file);
}

swStarfield::swStarfield(swStream* stream) : swDrawable(0, 0, 0, 2, 2) {
    type = SW_STARFIELD;
    read(stream);
}

swStarfield::~swStarfield() {}

void swStarfield::read(swStream *stream) {
    stream->readInt(pointCount);
    points = new double[pointCount * 3];
    stream->read((char*)points, pointCount * sizeof(double) * 3);
}

void swStarfield::write(swStream *stream) {
    stream->writeInt(pointCount);
    stream->write((char*)points, pointCount * sizeof(double) * 3);
}

void swStarfield::draw() {
    glPushMatrix();
    transform();

    glPointSize(2);
    glColor3f(1, 1, 1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, points);
    glDrawArrays(GL_POINTS, 0, pointCount);
    glDisableClientState(GL_VERTEX_ARRAY);
    // step the rotation forward
    rot += 0.01 * M_PI / 180;

    glPopMatrix();
}
