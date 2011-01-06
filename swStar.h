#ifndef SWSTAR_H
#define SWSTAR_H

#include "swPhysical.h"

class swStar : public swPhysical {
public:
    swStar();
    virtual ~swStar();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void draw();
    virtual void tick();

    double gravity;
};

#endif // SWSTAR_H
