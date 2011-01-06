#ifndef SWPLAYERCREATEMSG_H
#define SWPLAYERCREATEMSG_H

#include "swMessage.h"
#include "swPlayer.h"

class swPlayerCreateMsg : public swMessage {
public:
    swPlayerCreateMsg();
    virtual ~swPlayerCreateMsg();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void cliHandle(swClient* client);
    virtual void servHandle(swServer* server, QTcpSocket* sock);

    bool isLocalPlayer;
    swPlayer player;
};

#endif // SWPLAYERCREATEMSG_H
