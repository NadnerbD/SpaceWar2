#include "swPhysDeleteMsg.h"
#include "swFactory.h"

swPhysDeleteMsg::swPhysDeleteMsg() {
    type = SW_PHYS_DELETE_MSG;
}

swPhysDeleteMsg::~swPhysDeleteMsg() {}

void swPhysDeleteMsg::read(swStream* stream) {
    stream->readInt(index);
}

void swPhysDeleteMsg::write(swStream* stream) {
    stream->writeInt(index);
}

void swPhysDeleteMsg::cliHandle(swClient* client) {
    client->game->simulator.remove(index);
}

void swPhysDeleteMsg::servHandle(swServer* server, QTcpSocket* sock) {
    // check that this is client 0
    if(server->socks.indexOf(sock) == 0) {
	// forward the message to all clients
	foreach(QTcpSocket* sock, server->socks) {
	    swFactory::writeObject(this, sock);
	}
    }
}
