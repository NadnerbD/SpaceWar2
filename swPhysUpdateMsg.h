#ifndef SWPHYSUPDATEMSG_H
#define SWPHYSUPDATEMSG_H

#include "swMessage.h"
#include "swPhysical.h"

class swPhysUpdateMsg : public swMessage {
public:
    swPhysUpdateMsg();
    virtual ~swPhysUpdateMsg();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void servHandle(swServer* server, QTcpSocket* sock);
    virtual void cliHande(swClient* client);

    int index;
    swPhysical* object;
};

#endif // SWPHYSUPDATEMSG_H
