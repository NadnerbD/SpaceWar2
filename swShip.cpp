#include <QGLWidget>

#include "swPhysCreateMsg.h"
#include "swPlayerKillMsg.h"
#include "swSimulator.h"
#include "swMissile.h"
#include "swFactory.h"
#include "swStream.h"
#include "swPlayer.h"
#include "swDebris.h"
#include "swShip.h"

swShip::swShip() : fuel(1000), ammo(100), killed(false) {
    type = SW_SHIP;
    radius = 0.5; // this should be 1
    colType = 1;
}

swShip::~swShip() {}

bool swShip::collide(swPhysical* other) {
    // TODO: line set collision
    return swPhysical::collide(other);
}

void swShip::handleCollision(swPhysical* other) {
    if(!killed && other->type != SW_DEBRIS) {
	// send kill message (kill message will destroy ship and create debris)
	swPlayerKillMsg killMsg;
	killMsg.index = ownerId;
	killMsg.killerId = other->ownerId;
	swFactory::writeObject(&killMsg, owner->client->sock);
	killed = 1;
    }
}

void swShip::draw() {
    if(owner) {
	glPushMatrix();
	transform();
	owner->shipMesh.draw();
	glPopMatrix();
    }else{
	qWarning("Attempt to draw ship without owner");
    }
}

void swShip::tick() {
    swPhysical::tick();
    if(owner) {
	double H = owner->controlAxes.x * -4.0 * swSimulator::tickScale;
	double V = owner->controlAxes.y * 0.5 * swSimulator::tickScale;
	if(parent->simulateOmega)
	    omega += H;
	else
	    rot += H;
	if(fuel > 0) {
	    vel += swVector(0, 1).rotate(rot) * V;
	    if(V != 0)
		fuel--;
	}
    }
}

void swShip::fire() {
    if(ammo > 0) {
	swPhysCreateMsg fireMsg;
	swMissile missile;
	missile.ownerId = ownerId;
	swVector disp = swVector(0, 1).rotate(rot).scale(scale);
	missile.pos = pos + disp;
	missile.vel = vel + disp * fireVel;
	fireMsg.object = &missile;
	swFactory::writeObject(&fireMsg, owner->client->sock);
	ammo--;
    }
}

void swShip::createDebris() {
    swMesh* mesh = &owner->shipMesh;
    for(int i = 0; i < mesh->edgeCount; i++) {
	swVector p1 = swVector(mesh->verts[mesh->edges[i * 2] * 3], mesh->verts[mesh->edges[i * 2] * 3 + 1]);
	swVector p2 = swVector(mesh->verts[mesh->edges[i * 2 + 1] * 3], mesh->verts[mesh->edges[i * 2 + 1] * 3 + 1]);
	swDebris* debris = new swDebris();
	swVector localPos = ((p1 + p2) / 2).rotate(rot).scale(scale);
	double length = (p1 - p2).scale(scale).length() / 2;
	debris->pos = localPos + pos;
	debris->vel = localPos + vel + swVector(-localPos.y, localPos.x) * omega;
	debris->rot = (p1 - p2).angle() + rot;
	debris->scale = swVector(length, length);
	debris->omega = omega;
	owner->client->game->simulator.insert(debris);
    }
}

void swShip::die() {
    createDebris();
    parent->remove(owner->shipId);
    owner->shipId = -1;
}

void swShip::read(swStream* stream) {
    swPhysical::read(stream);
    stream->readInt(fuel);
    stream->readInt(ammo);
}

void swShip::write(swStream* stream) {
    swPhysical::write(stream);
    stream->writeInt(fuel);
    stream->writeInt(ammo);
}
