#ifndef SWPHYSICAL_H
#define SWPHYSICAL_H

#include "swDrawable.h"

class swSimulator;
class swPlayer;

class swPhysical : public swDrawable {
public:
    swPhysical(swSimulator* prnt = NULL);
    virtual ~swPhysical();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void tick();
    virtual bool collide(swPhysical* other);
    virtual void handleCollision(swPhysical* other);

    swSimulator* parent;
    swPlayer* owner;
    int ownerId;
    swVector vel;
    double omega;
    double radius;
    int colType;
};

#endif // SWPHYSICAL_H
