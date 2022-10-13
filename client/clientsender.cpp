#include "clientsender.h"


ClientSender::ClientSender(QString host, int port, StoreMessages *store)
{
    this->host=host;
    this->port=port;
    this->store=store;
    que.clear();
    que.append(MessageAPI());
    this->run();
}

ClientSender::~ClientSender()
{
    socket->close();
}

void ClientSender::disconnected()
{
    //Связь оборвалась конец работы
    qCritical() << socket->errorString();
    socket->close();
    this->exit();
}

void ClientSender::readyRead()
{
    auto buf=QString::fromUtf8(socket->readAll());
    if (buf!="ok\n\n") {
        qCritical()<<"Read responce from server"<<buf;
        socket->close();
        this->exit();
    }
    busy=false;
    mutex.lock();
    MessageAPI msg();
    if (que.length()!=0) {
        msg=que.dequeue();
    }
    mutex.unlock();
    if (msg.level!=Level_Empty) {
        send(msg);
    }

}

void ClientSender::upMessage()
{
    auto list=store->getAllMessages();
    mutex.lock();
    foreach (auto var, list) {
        que.append(v);
    }
    if (que.length()==0 || busy) {
        mutex.unlock();
        return;
    }
    auto msg=que.dequeue();
    mutex.unlock();
    send(msg);
}

void ClientSender::send(MessageAPI message)
{
    busy=true;
    socket->write(message.getBytes());
    socket->flush();
}

void ClientSender::run()
{
    busy=true;
    connect(store,SIGNAL(upMessage()),this,SLOT(upMessage()));
    socket=new QTcpSocket();
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesSender()));
    qInfo() << "Connecting to server"<<host<<port;
    do {
        socket->connectToHost(host, port);
        if(!socket->waitForDisconnected())
        {
            qCritical() << socket->errorString();
            QThread::sleep(10);
        } else {
            qInfo() << "Connected to server"<<host<<port;
        }
    } while (!socket->isOpen());
    busy=false;
    upMessage();
    while (this->isRunning()&&socket->isOpen()){
        QThread::sleep(1);
    }
    this->exit();
}
