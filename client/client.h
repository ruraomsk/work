#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include "../libfocus/storemessages.h"

#include "clientsender.h"
#include "clientreceiver.h"

class Client : public QObject,QThread
{
    Q_OBJECT
public:

    Client(QString host,int sendport,int listenport);
    void  writeMessage(MessageAPI message);
public slots:
    void readMessage(MessageAPI message);
signals:
    void isMessage();
    void isReady();
    void isNotWork();
private:
    QString host;
    int port;
    StoreMessages sendstore;
    StoreMessages receivstore;
    ClientSender *sender;
    ClientReceiver *reciiver;

    // QThread interface
protected:
    void run() override;
};

#endif // CLIENT_H
