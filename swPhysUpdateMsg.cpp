#include "swPhysUpdateMsg.h"
#include "swFactory.h"

swPhysUpdateMsg::swPhysUpdateMsg() {
    type = SW_PHYS_UPDATE_MSG;
}

swPhysUpdateMsg::~swPhysUpdateMsg() {}

void swPhysUpdateMsg::read(swStream* stream) {
    stream->readInt(index);
    object = swFactory::readPhysical(stream);
}

void swPhysUpdateMsg::write(swStream* stream) {
    stream->writeInt(index);
    swFactory::writeObject(object, stream);
}

void swPhysUpdateMsg::cliHande(swClient* client) {
    client->game->simulator.update(index, object);
    delete object;
}

void swPhysUpdateMsg::servHandle(swServer* server, QTcpSocket* sock) {
    // forward the message to all other clients
    foreach(QTcpSocket* sendSock, server->socks) {
	if(sock != sendSock)
	    swFactory::writeObject(this, sendSock);
    }
    delete object;
}
