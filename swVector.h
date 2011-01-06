#ifndef SWVECTOR_H
#define SWVECTOR_H

#include "swObject.h"

class swVector : public swObject {
public:
    swVector(double a = 0.0, double b = 0.0);
    swVector(const swVector &src);

    swVector normalize();
    swVector rotate(double angle);
    swVector scale(swVector a);
    double length();
    double angle();

    swVector operator+(swVector a);
    swVector operator-(swVector a);
    swVector operator*(double a);
    swVector operator/(double a);
    double operator*(swVector a);
    swVector& operator+=(swVector a);
    swVector& operator-=(swVector a);
    bool operator==(swVector a);
    bool operator!=(swVector a);

    void read(swStream* stream);
    void write(swStream* stream);

    double x;
    double y;
};

#endif // SWVECTOR_H
