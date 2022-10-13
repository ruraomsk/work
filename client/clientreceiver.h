#ifndef CLIENTRECEIVER_H
#define CLIENTRECEIVER_H

#include <QObject>

class ClientReceiver : public QObject,QThread
{
    Q_OBJECT
public:
    explicit ClientReceiver(QObject *parent = nullptr);

signals:

};

#endif // CLIENTRECEIVER_H
