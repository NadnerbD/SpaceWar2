#ifndef SWCLIENTINITMSG_H
#define SWCLIENTINITMSG_H

#include "swMessage.h"
#include "swBitmask.h"
#include "swPlayer.h"

class swClientInitMsg : public swMessage {
public:
    swClientInitMsg();
    virtual ~swClientInitMsg();

    virtual void servHandle(swServer* server, QTcpSocket* sock);
    virtual void cliHandle(swClient* client);
    virtual void read(swStream* stream);
    virtual void write(swStream* stream);

    swBitmask settings;
    QList<swPlayer> players;
};

#endif // SWCLIENTINITMSG_H
