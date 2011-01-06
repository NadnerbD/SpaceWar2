#include "swClientInitMsg.h"

swClientInitMsg::swClientInitMsg() {
    type = SW_CLIENT_INIT_MSG;
}

swClientInitMsg::~swClientInitMsg() {

}

void swClientInitMsg::read(swStream* stream) {
    settings.read(stream);
    int playerCount = stream->readInt();
    for(int i = 0; i < playerCount; i++) {
	swPlayer player;
	player.read(stream);
	players.append(player);
    }
}

void swClientInitMsg::write(swStream* stream) {
    settings.write(stream);
    stream->writeInt(players.count());
    foreach(swPlayer player, players) {
	player.write(stream);
    }
}

void swClientInitMsg::servHandle(swServer* server, QTcpSocket* sock) {
    // this message is sent by the server
}

void swClientInitMsg::cliHandle(swClient* client) {
    // on receive, the client's lists are updated
    client->players = players;
    client->game->settings = settings;
}
