#ifndef SERVERAPI_H
#define SERVERAPI_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

#include "../libfocus/libfocus.h"

class ServerAPI : public QThread
{
    Q_OBJECT
public:
    ServerAPI(int port);

signals:


    // QThread interface
protected:
    void run() override;
private:
    int listenport;
};

#endif // SERVERAPI_H
