#ifndef SWSTARFIELD_H
#define SWSTARFIELD_H

#include "swDrawable.h"

class swStarfield : public swDrawable {
public:
    swStarfield();
    swStarfield(QString file);
    swStarfield(swStream* stream);
    virtual ~swStarfield();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void draw();

    int pointCount;
    double* points;
};

#endif // SWSTARFIELD_H
