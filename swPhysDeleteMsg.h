#ifndef SWPHYSDELETEMSG_H
#define SWPHYSDELETEMSG_H

#include "swMessage.h"

class swPhysDeleteMsg : public swMessage {
public:
    swPhysDeleteMsg();
    virtual ~swPhysDeleteMsg();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void cliHandle(swClient* client);
    virtual void servHandle(swServer* server, QTcpSocket* sock);

    int index;
};

#endif // SWPHYSDELETEMSG_H
