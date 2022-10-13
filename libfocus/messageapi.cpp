#include "messageapi.h"

MessageAPI::MessageAPI()
{
    this->message="{}";
    this->level=Level_Alert;
}

MessageAPI::MessageAPI(int level, QString message)
{
    this->message=message;
    this->level=level;
    if (isCorrect(level)) return;

}

QByteArray MessageAPI::getBytes()
{
    return (QString::number(level)+"\t"+message).toUtf8();
}

bool MessageAPI::isCorrect(int level)
{
    switch (level) {
    case Level_Alert:
    case Level_Device:
    case Level_Empty:
    case Level_Model:
    case Level_Report:
    case Level_Widget:
        return true;
    }
    return false;
}
