#ifndef SWPHYSCREATEMSG_H
#define SWPHYSCREATEMSG_H

#include "swMessage.h"
#include "swPhysical.h"

class swPhysCreateMsg : public swMessage {
public:
    swPhysCreateMsg();
    virtual ~swPhysCreateMsg();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void cliHandle(swClient* client);
    virtual void servHandle(swServer* server, QTcpSocket* sock);

    swPhysical* object;
};

#endif // SWPHYSCREATEMSG_H
