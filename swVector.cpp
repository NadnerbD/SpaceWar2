#include <cmath>
#include "swVector.h"

swVector::swVector(double a, double b) : x(a), y(b) {
    type = SW_VECTOR;
}

swVector::swVector(const swVector &src) : x(src.x), y(src.y) {
    type = SW_VECTOR;
}

swVector swVector::normalize() {
    double len = length();
    return *this / len;
}

swVector swVector::rotate(double angle) {
    return swVector(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
}

double swVector::length() {
    return sqrt(x * x + y * y);
}

double swVector::angle() {
    return atan2(y, x);
}

swVector swVector::scale(swVector a) {
    return swVector(x * a.x, y * a.y);
}

swVector swVector::operator+(swVector a) {
    return swVector(x + a.x, y + a.y);
}

swVector swVector::operator-(swVector a) {
    return swVector(x - a.x, y - a.y);
}

double swVector::operator*(swVector a) {
    return x * a.x + y * a.y;
}

swVector swVector::operator*(double a) {
    return swVector(x * a, y * a);
}

swVector swVector::operator/(double a) {
    return swVector(x / a, y / a);
}

swVector& swVector::operator+=(swVector a) {
    x += a.x;
    y += a.y;
    return *this;
}

swVector& swVector::operator-=(swVector a) {
    x -= a.x;
    y -= a.y;
    return *this;
}

bool swVector::operator==(swVector a) {
    return (x == a.x && y == a.y);
}

bool swVector::operator!=(swVector a) {
    return (x != a.x || y != a.y);
}

void swVector::read(swStream* stream) {
    stream->readDouble(x);
    stream->readDouble(y);
}

void swVector::write(swStream* stream) {
    stream->writeDouble(x);
    stream->writeDouble(y);
}
