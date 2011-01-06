#ifndef SWBITMASK_H
#define SWBITMASK_H

#include "swObject.h"

class swBitmask : public swObject
{
public:
    swBitmask();
    virtual ~swBitmask();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    void setBit(int bit, bool value);
    bool getBit(int bit);

    int value;
};

#endif // SWBITMASK_H
