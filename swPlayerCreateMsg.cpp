#include "swPlayerCreateMsg.h"
#include "swFactory.h"

swPlayerCreateMsg::swPlayerCreateMsg() : isLocalPlayer(false) {
    type = SW_PLAYER_CREATE_MSG;
}

swPlayerCreateMsg::~swPlayerCreateMsg() {}

void swPlayerCreateMsg::read(swStream* stream) {
    isLocalPlayer = stream->readChar();
    player.read(stream);
}

void swPlayerCreateMsg::write(swStream* stream) {
    stream->writeChar(isLocalPlayer);
    player.write(stream);
}

void swPlayerCreateMsg::cliHandle(swClient* client) {
    // the client sends and receives this message
    if(isLocalPlayer)
	client->clientId = client->players.count();
    player.client = client;
    client->players.append(player);
}

void swPlayerCreateMsg::servHandle(swServer* server, QTcpSocket* sock) {
    // the server adds the client to it's list and relays the message
    player.sock = sock;
    server->clientList.append(player);
    foreach(QTcpSocket* sendSock, server->socks) {
	isLocalPlayer = sock == sendSock;
	swFactory::writeObject(this, sendSock);
    }
}
