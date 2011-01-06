#include "swPlayerKillMsg.h"
#include "swFactory.h"
#include "swDebris.h"
#include "swShip.h"
#include "swMesh.h"
#include <cmath>

swPlayerKillMsg::swPlayerKillMsg() : killerId(-1) {
    type = SW_PLAYER_KILL_MSG;
}

swPlayerKillMsg::~swPlayerKillMsg() {}

void swPlayerKillMsg::read(swStream* stream) {
    stream->readInt(index);
    stream->readInt(killerId);
}

void swPlayerKillMsg::write(swStream* stream) {
    stream->writeInt(index);
    stream->writeInt(killerId);
}

void swPlayerKillMsg::cliHandle(swClient* client) {
    // if the player hasn't already been killed
    if(client->players[index].shipId != -1) {
	// destroy the player ship (adds debris)
	swShip* ship = (swShip*)client->game->simulator.objects[client->players[index].shipId];
	ship->die();
	// increment killer's score
	if(killerId != -1)
	    client->players[killerId].score++;
    }
}

void swPlayerKillMsg::servHandle(swServer* server, QTcpSocket* sock) {
    // check that this is client 0
    if(server->socks.indexOf(sock) == 0) {
	// forward the message to all clients
	if(killerId != -1)
	    server->clientList[killerId].score++;
	foreach(QTcpSocket* sock, server->socks) {
	    swFactory::writeObject(this, sock);
	}
    }
}
