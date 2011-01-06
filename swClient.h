#ifndef SWCLIENT_H
#define SWCLIENT_H

#include <QTcpSocket>
#include <QObject>

#include "swPlayer.h"
#include "swGame.h"

class swClient : public QObject {
    Q_OBJECT
public:
    swClient(swGame* parent, QString host, int port);

    swGame* game;
    QTcpSocket* sock;
    int clientId;
    QList<swPlayer> players;

public slots:
    void recvMsg();
    void onConnect();
    void error(QAbstractSocket::SocketError);
};

#endif // SWCLIENT_H
