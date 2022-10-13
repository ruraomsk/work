#include "storemessages.h"
StoreMessages::StoreMessages()
{
    map.clear();
}

void StoreMessages::addMessage(MessageAPI message)
{
    appendMessage(message);
    switch (message.level) {
    case Level_Alert:
        emit isAlert();
        break;
    case Level_Device:
        emit isDevice();
        break;
    case Level_Model:
        emit isModel();
        break;
    case Level_Report:
        emit isReport();
        break;
    case Level_Widget:
        emit isWidget();
        break;

    default:
        qCritical()<<"bad level "<<message.level;
        break;
    }
}

void StoreMessages::quietMessage(MessageAPI message)
{
    appendMessage(message);
    emit upMessage();
}

MessageAPI StoreMessages::getMessage(int level)
{
    MessageAPI empty(Level_Empty,"{}");
    MessageAPI result;
    mutex.lock();
    if (!map.contains(level)){
        result=empty;
    } else {
        auto que=map[level];
        if (que.length()!=0) {
            result=que.dequeue();
            map[level]=que;
        } else result=empty;
    }
    mutex.unlock();
    return result;
}

QList<MessageAPI> StoreMessages::getAllMessages()
{
    QList<MessageAPI> result;
    mutex.lock();
    foreach (auto que, map) {
        while(que.length()!=0){
            result.append(que.dequeue());
        }
    }
    map.clear();
    mutex.unlock();
    return result;

}

QList<MessageAPI> StoreMessages::getAllLevel(int level)
{
    QList<MessageAPI> result;
    mutex.lock();
    if (map.contains(level)){
        auto que=map[level];
        while(que.length()!=0){
            result.append(que.dequeue());
        }
        map[level]=que;
    }
    mutex.unlock();
    return result;
}

void StoreMessages::appendMessage(MessageAPI message)
{
    mutex.lock();
    if (!map.contains(message.level)){
        //Нет такой записи создаем пустую очередь
        QQueue<MessageAPI> que;
        que.enqueue(message);
        map[message.level]=que;
    } else {
        auto que=map[message.level];
        que.enqueue(message);
        map[message.level]=que;
    }
    mutex.unlock();
}
