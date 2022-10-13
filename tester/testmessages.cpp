#include "testmessages.h"

TestMessages::TestMessages()
{
    MessageAPI m1(Level_Alert,"{ALERT}");
    MessageAPI m2(Level_Device,"Device");

    qInfo()<<"Start test StoreMessage";
    oneStore.addMessage(m1);
    oneStore.addMessage(m2);
    auto sl=oneStore.getAllMessages();
    foreach (auto v, sl) {
        qDebug()<<v.message;
    }
    qDebug()<<"========================";
    oneStore.addMessage(m1);
    oneStore.addMessage(m1);
    oneStore.addMessage(m1);
    oneStore.addMessage(m1);
    {
        auto sl=oneStore.getAllLevel(Level_Alert);
        foreach (auto v, sl) {
            qDebug()<<v.message;
        }
    }

}
