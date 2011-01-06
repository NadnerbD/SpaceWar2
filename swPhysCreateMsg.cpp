#include "swPhysCreateMsg.h"
#include "swFactory.h"
#include "swShip.h"

swPhysCreateMsg::swPhysCreateMsg() : object(NULL) {
    type = SW_PHYS_CREATE_MSG;
}

swPhysCreateMsg::~swPhysCreateMsg() {}

void swPhysCreateMsg::write(swStream* stream) {
    swFactory::writeObject(object, stream);
}

void swPhysCreateMsg::read(swStream* stream) {
    object = swFactory::readPhysical(stream);
}

void swPhysCreateMsg::cliHandle(swClient* client) {
    // add the received object to the simulator
    client->game->simulator.insert(object, true);
    // assign the object's owner, if it has one
    if(object->ownerId != -1) {
	object->owner = &client->players[object->ownerId];
	// players need to receive their shipId when their ship is created
	if(object->type == swObject::SW_SHIP)
	    object->owner->shipId = client->game->simulator.objects.indexOf(object);
    }
    // since it was added to this list, we don't need to delete it
}

void swPhysCreateMsg::servHandle(swServer* server, QTcpSocket* sock) {
    // forward the message to all clients
    foreach(QTcpSocket* sock, server->socks) {
	swFactory::writeObject(this, sock);
    }
    // only the server needs to delete the object after sending
    delete object;
}
