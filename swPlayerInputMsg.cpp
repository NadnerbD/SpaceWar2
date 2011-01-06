#include "swPlayerInputMsg.h"
#include "swFactory.h"

swPlayerInputMsg::swPlayerInputMsg() : index(0) {
    type = SW_PLAYER_INPUT_MSG;
}

swPlayerInputMsg::~swPlayerInputMsg() {}

void swPlayerInputMsg::read(swStream* stream) {
    stream->readInt(index);
    controlAxes.read(stream);
}

void swPlayerInputMsg::write(swStream* stream) {
    stream->writeInt(index);
    controlAxes.write(stream);
}

void swPlayerInputMsg::cliHandle(swClient* client) {
    client->players[index].controlAxes = controlAxes;
}

void swPlayerInputMsg::servHandle(swServer* server, QTcpSocket* sock) {
    server->clientList[index].controlAxes = controlAxes;
    foreach(QTcpSocket* sendSock, server->socks) {
	if(sendSock != sock)
	    swFactory::writeObject(this, sendSock);
    }
}
