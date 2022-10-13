#ifndef MESSAGEAPI_H
#define MESSAGEAPI_H

#include <QString>
#include <QByteArray>

enum  {
    Level_Empty=-1,
    Level_Alert=0,
    Level_Device=1,
    Level_Model=2,
    Level_Report=3,
    Level_Widget=4
};

class MessageAPI
{
public:
    MessageAPI();
    MessageAPI(int level,QString message);
    QByteArray getBytes();

    QString message;
    int level;              //Сообщения уровня -1 игнорируются
private:
    bool isCorrect(int level);
};

#endif // MESSAGEAPI_H
