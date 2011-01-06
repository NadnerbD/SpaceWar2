#include "swBitmask.h"

swBitmask::swBitmask() : value(0) {}

swBitmask::~swBitmask() {}

void swBitmask::read(swStream* stream) {
    stream->readInt(value);
}

void swBitmask::write(swStream* stream) {
    stream->writeInt(value);
}

void swBitmask::setBit(int bit, bool value) {
    if(value)
	value |= 1 << bit;
    else
	value &= ~(1 << bit);
}

bool swBitmask::getBit(int bit) {
    return bit & 1 << bit;
}
