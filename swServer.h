#ifndef SWSERVER_H
#define SWSERVER_H

#include "swPlayer.h"
#include "swGame.h"

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class swServer : public QObject {
    Q_OBJECT
public:
    swServer(swGame* parent, int port);

    QString address();
    swPlayer* findPlayer(QTcpSocket* sock);

    swGame* game;
    QTcpServer* qserver;
    QList<QTcpSocket*> socks;
    QList<swPlayer> clientList;
    int gamePhase;

public slots:
    void recvMsg();
    void addConnection();
    void sockError(QAbstractSocket::SocketError);
};

#endif // SWSERVER_H
