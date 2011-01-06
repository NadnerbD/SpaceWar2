#ifndef SWDRAWABLE_H
#define SWDRAWABLE_H

#include "swObject.h"
#include "swVector.h"

class swDrawable : public swObject {
public:
    swDrawable(double px = 0, double py = 0, double r = 0, double sx = 1, double sy = 1);
    virtual ~swDrawable();

    virtual void draw();
    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    void transform();

    swVector scale;
    swVector pos;
    double rot;
};

#endif // SWDRAWABLE_H
