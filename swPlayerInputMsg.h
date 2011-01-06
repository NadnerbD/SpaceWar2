#ifndef SWPLAYERINPUTMSG_H
#define SWPLAYERINPUTMSG_H

#include "swMessage.h"

class swPlayerInputMsg : public swMessage {
public:
    swPlayerInputMsg();
    virtual ~swPlayerInputMsg();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);
    virtual void servHandle(swServer* server, QTcpSocket* sock);
    virtual void cliHandle(swClient* client);

    int index;
    swVector controlAxes;
};

#endif // SWPLAYERINPUTMSG_H
