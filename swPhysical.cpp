#include "swSimulator.h"
#include "swPhysical.h"

swPhysical::swPhysical(swSimulator* prnt) : parent(prnt), owner(NULL), ownerId(-1), omega(0), radius(1), colType(0) {
    type = SW_PHYSICAL;
    scale = swVector(0.1, 0.1);
}

swPhysical::~swPhysical() {

}

void swPhysical::read(swStream* stream) {
    swDrawable::read(stream);
    // the ownerId is used by the createMsg to assign the owner pointer
    stream->readInt(ownerId);
    vel.read(stream);
    stream->readDouble(omega);
    stream->readDouble(radius);
    stream->readInt(colType);
}

void swPhysical::write(swStream* stream) {
    swDrawable::write(stream);
    stream->writeInt(ownerId);
    vel.write(stream);
    stream->writeDouble(omega);
    stream->writeDouble(radius);
    stream->writeInt(colType);
}

void swPhysical::tick() {
    pos += vel * swSimulator::tickScale;
    rot += omega * swSimulator::tickScale;
    // perform the edge-of-window check
    if(pos.x > 1.5)
	pos.x -= 3;
    if(pos.x < -1.5)
	pos.x += 3;
    if(pos.y > 1.5)
	pos.y -= 3;
    if(pos.y < -1.5)
	pos.y += 3;
    // we start at our index to avoid duplicate checks
    // this depends on the accuracy of the index
    for(int i = parent->objects.indexOf(this); i < parent->objects.count(); i++) {
	// if we're not in the list, don't do anything
	if(i == -1)
	    break;
	swPhysical* other = parent->objects[i];
	if(other && collide(other)) {
	    handleCollision(other);
	    other->handleCollision(this);
	}
    }
}

bool swPhysical::collide(swPhysical* other) {
    if(other == this)
	return false;
    swVector diff = other->pos - pos;
    // we're going to approximate scale by using only one axis
    // there is a better way to do this, but I'm too lazy to work it out at the moment
    double dist = other->radius * other->scale.x + radius * scale.x;
    if(diff * diff < dist * dist) {
	// "colType" is a measure of complexity
	// plain radius check = 0
	// mesh or other types > 0
	if(other->colType > colType)
	    return other->collide(this);
	return true;
    }
    return false;
}

void swPhysical::handleCollision(swPhysical* other) {
    // base implementation.. doesn't do anything
}
