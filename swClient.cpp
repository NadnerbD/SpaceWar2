#include "swClient.h"
#include "swFactory.h"
#include "swMessage.h"

#include "swPlayerCreateMsg.h"
#include "swPhysCreateMsg.h"
#include "swShip.h"
#include "swStar.h"

swClient::swClient(swGame* parent, QString host, int port) : QObject(parent), game(parent), clientId(-1) {
    sock = new QTcpSocket(this);
    connect(sock, SIGNAL(readyRead()), this, SLOT(recvMsg()));
    connect(sock, SIGNAL(connected()), this, SLOT(onConnect()));
    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    sock->connectToHost(host, port, QIODevice::ReadWrite);
}

void swClient::recvMsg() {
    while(sock->bytesAvailable()) {
	swMessage* msg = swFactory::readMessage(sock);
	msg->cliHandle(this);
	delete msg;
    }
}

void swClient::onConnect() {
    // the server sends us our init message as soon as the socket is connected

    // send our player to the server
    swPlayerCreateMsg playerMsg;
    playerMsg.player = game->playerConstruct;
    swFactory::writeObject(&playerMsg, sock);

    // TEMP: create ship, initial velocity of 0.24 and initial pos radius of 0.5
    swPhysCreateMsg physMsg;
    swShip newShip = swShip();
    newShip.ownerId = 0; // we know this is us, since we're the only player, later this will have to use our clientId
    newShip.pos = swVector(0.5, 0.0);
    newShip.vel = swVector(0.0, 0.24);
    physMsg.object = &newShip;
    swFactory::writeObject(&physMsg, sock);

    // TEMP: create the star
    swStar newStar = swStar();
    physMsg.object = &newStar;
    swFactory::writeObject(&physMsg, sock);
}

void swClient::error(QAbstractSocket::SocketError) {

}
