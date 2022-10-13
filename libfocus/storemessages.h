#ifndef STOREMESSAGES_H
#define STOREMESSAGES_H
#include <QObject>
#include <QMap>
#include <QQueue>
#include <QMutex>
#include <QDebug>
#include <QList>
#include "messageapi.h"

class StoreMessages:public QObject
{
    Q_OBJECT
public:
    StoreMessages();
public slots:
    void addMessage(MessageAPI message);
    void quietMessage(MessageAPI message);
    MessageAPI getMessage(int level);
    QList<MessageAPI> getAllMessages();
    QList<MessageAPI> getAllLevel(int level);
signals:
    void isAlert();
    void isDevice();
    void isModel();
    void isReport();
    void isWidget();
    void upMessage();

private:
    QMutex mutex;
    QMap<int,QQueue<MessageAPI>> map;
    void appendMessage(MessageAPI message);

};

#endif // STOREMESSAGES_H
