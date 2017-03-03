#ifndef SWREADYMSG_H
#define SWREADYMSG_H

#include "swMessage.h"

class swReadyMsg : public swMessage {
public:
    swReadyMsg();
    virtual ~swReadyMsg();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void servHandle(swServer* server, QTcpSocket* sock);
    virtual void cliHandle(swClient* client);

    int clientId;
};

#endif // SWREADYMSG_H
