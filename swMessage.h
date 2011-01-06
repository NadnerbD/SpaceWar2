#ifndef SWMESSAGE_H
#define SWMESSAGE_H

#include "swObject.h"
#include "swClient.h"
#include "swServer.h"

#include <QTcpSocket>

class swMessage : public swObject {
public:
    swMessage();
    virtual ~swMessage();

    virtual void servHandle(swServer* server, QTcpSocket* sock);
    virtual void cliHandle(swClient* client);
};

#endif // SWMESSAGE_H
