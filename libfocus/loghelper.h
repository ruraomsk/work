#ifndef LOGHELPER_H
#define LOGHELPER_H


#include <QDebug>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QTime>
#include <QDate>
#include <QDir>
#include <QFile>
#include <iostream>
#include <QMutex>
#include <QTextStream>

/*
 *  Система
 *
 */



class LogHelper
{
public:
    static void setDebugMessageHandler(QString logPath,int days);
    static void myMessageOutput(QtMsgType type,
                                const QMessageLogContext &context,
                                const QString &msgText);
protected:
    static void smartPrintDebugMessage(QString msg);
    static void printToLogFile(const QString &text);
    static void clearLogFiles();
    static QString m_logFileName;
    static QString m_logPath;
    static FILE *File;
    static bool isFile;
    static QMutex mutex;
    static int savedays;
    static void newDay();
    static QString getName();
};


#endif // LOGHELPER_H
