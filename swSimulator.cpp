#include "swPhysical.h"
#include "swSimulator.h"

swSimulator::swSimulator() : lastUpdate(0), netObjects(0), simulateOmega(0) {
    qtime.start();
    lastUpdate = qtime.elapsed();
}

swSimulator::~swSimulator() {
    // this can be used as a general cleanup function
    foreach(swPhysical* object, objects) {
	if(object)
	    delete object;
    }
    foreach(swPhysical *object, deadObjects) {
	delete object;
    }
    objects.clear();
    deadObjects.clear();
    netObjects = 0;
}

void swSimulator::draw() {
    foreach(swPhysical* object, objects) {
	if(object)
	    object->draw();
    }
}

void swSimulator::insert(swPhysical* object, bool net) {
    // connect the object to the simulator
    object->parent = this;
    // this keeps the synched objects in the low address range
    if(net) {
	objects.insert(netObjects, object);
	netObjects++;
    }else{
	objects.append(object);
    }
}

void swSimulator::update(int index, swPhysical* object) {
    if(!object) {
	qWarning("Attempt to update dead object at: %d", index);
	return;
    }
    swPhysical* target = objects[index];
    target->pos = object->pos;
    target->rot = object->rot;
    target->vel = object->vel;
    target->omega = object->omega;
}

void swSimulator::remove(int index) {
    deadObjects.append(objects[index]);
    objects[index] = NULL;
}

void swSimulator::simulate() {
    while(lastUpdate < qtime.elapsed()) {
	foreach(swPhysical* object, objects) {
	    if(object)
		object->tick();
	}
	lastUpdate += tickLen;
    }
}
