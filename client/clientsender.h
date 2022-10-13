#ifndef CLIENTSENDER_H
#define CLIENTSENDER_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QQueue>
#include <QMutex>
#include "../libfocus/storemessages.h"

class ClientSender : public QObject,QThread
{
    Q_OBJECT
public:
    ClientSender(QString host,int port,StoreMessages* store);
    ~ClientSender();
    bool isConnected();
public slots:
    void disconnected();
    void bytesSender();
    void readyRead();
    void upMessage();
private:
    void send(MessageAPI message);
    QTcpSocket *socket;
    StoreMessages* store;
    QQueue<MessageAPI> que;
    QMutex mutex;

    bool busy;
    // QThread interface
protected:
    void run() override;
};

#endif // CLIENTSENDER_H
