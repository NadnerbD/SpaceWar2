#ifndef SWPLAYER_H
#define SWPLAYER_H

#include <QTcpSocket>

#include "swVector.h"
#include "swMesh.h"
#include "swObject.h"

class swClient;

class swPlayer : public swObject {
public:
    swPlayer();
    virtual ~swPlayer();

    virtual void read(swStream* stream);
    virtual void write(swStream* stream);

    QTcpSocket* sock; // for server use
    swClient* client; // for client use
    QString name;
    int score;
    bool ready;
    int shipId;
    swMesh shipMesh;
    swVector controlAxes;
};

#endif // SWPLAYER_H
