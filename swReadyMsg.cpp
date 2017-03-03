#include "swReadyMsg.h"

#include "swPhysCreateMsg.h"
#include "swFactory.h"
#include "swShip.h"
#include "swStar.h"

#include <math.h>

swReadyMsg::swReadyMsg() {
    type = SW_READY_MSG;
}

swReadyMsg::~swReadyMsg() {

}

void swReadyMsg::read(swStream* stream) {
	clientId = stream->readInt();
}

void swReadyMsg::write(swStream* stream) {
	stream->writeInt(clientId);
}

void swReadyMsg::servHandle(swServer* server, QTcpSocket* sock) {
    // the ready message is sent by the lobby menu
    // when the game ends, the lobby menu should be recreated
    // the server handles this message by relaying it to all clients so they can update their ready status

    clientId = server->socks.indexOf(sock);
    server->clientList[clientId].ready = true;
    foreach(QTcpSocket* sendSock, server->socks) {
        swFactory::writeObject(this, sendSock);
    }
}

void swReadyMsg::cliHandle(swClient* client) {
    // the client handles this (forwarded) message by updating the ready status of players, which will be shown by the lobby menu
    client->players[clientId].ready = true;

    // when all players are ready, the host client begins the game by creating their ships and the star
    bool allReady = true;
    foreach(swPlayer player, client->players) {
        if(player.ready == false) {
            allReady = false;
            break;
        }
    }

    if(allReady && client->clientId == 0) {
        // only the host client should perform game init tasks
        swPhysCreateMsg physMsg;
        int count = client->players.length();
        for(int i = 0; i < count; i++) {
            double angle = M_PI * 2 / count * i;
            // create ship, initial velocity of 0.24 and initial pos radius of 0.5
            swShip newShip = swShip();
            newShip.ownerId = i;
            newShip.pos = swVector(0.5 * cos(angle), 0.5 * sin(angle));
            newShip.vel = swVector(0.24 * sin(angle), 0.24 * cos(angle));
            newShip.rot = angle;
            physMsg.object = &newShip;
            swFactory::writeObject(&physMsg, client->sock);
	}

        // create the star
        swStar newStar = swStar();
        physMsg.object = &newStar;
        swFactory::writeObject(&physMsg, client->sock);
    }

    if(allReady) {
        // all clients need to enable game controls when the game starts
        client->game->connect(client->game, SIGNAL(keyEvent(QKeyEvent*)), SLOT(keyHandle(QKeyEvent*)));
    }
}
