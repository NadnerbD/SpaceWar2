#ifndef SWPLAYERKILLMSG_H
#define SWPLAYERKILLMSG_H

#include "swMessage.h"

class swPlayerKillMsg : public swMessage {
public:
    swPlayerKillMsg();
    virtual ~swPlayerKillMsg();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void cliHandle(swClient* client);
    virtual void servHandle(swServer* server, QTcpSocket* sock);

    int index;
    int killerId;
};

#endif // SWPLAYERKILLMSG_H
