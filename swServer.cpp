#include "swServer.h"
#include "swFactory.h"
#include "swClientInitMsg.h"

swServer::swServer(swGame* parent, int port) : QObject(parent), game(parent) {
    qserver = new QTcpServer(this);
    connect(qserver, SIGNAL(newConnection()), this, SLOT(addConnection()));
    qserver->listen(QHostAddress::Any, port);
}

void swServer::recvMsg() {
    foreach(QTcpSocket* sock, socks) {
	while(sock->bytesAvailable()) {
	    swMessage* msg = swFactory::readMessage(sock);
	    msg->servHandle(this, sock);
	    delete msg; // why does this cause problems!?
	}
    }
}

void swServer::addConnection() {
    QTcpSocket* sock = qserver->nextPendingConnection();
    connect(sock, SIGNAL(readyRead()), this, SLOT(recvMsg()));
    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(sockError(QAbstractSocket::SocketError)));
    socks.append(sock);
    // send the client init message
    swClientInitMsg msg;
    msg.players = clientList;
    msg.settings = game->settings;
    swFactory::writeObject(&msg, sock);
}

swPlayer* swServer::findPlayer(QTcpSocket* sock) {
    for(int i = 0; i < clientList.count(); i++) {
	swPlayer* player = &clientList[i];
	if(player->sock == sock)
	    return player;
    }
    return NULL;
}

QString swServer::address() {
    return qserver->serverAddress().toString();
}

void swServer::sockError(QAbstractSocket::SocketError) {

}
