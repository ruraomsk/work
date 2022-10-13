#include "loghelper.h"

QString LogHelper::m_logFileName;

QString LogHelper::m_logPath;
FILE* LogHelper::File;
bool   LogHelper::isFile;
QMutex LogHelper::mutex;
int LogHelper::savedays;

void LogHelper::printToLogFile(const QString &text)
{
    if (!isFile) return;
    // Быстрый вывод текста в файл лога
    mutex.lock();
    newDay();
    fprintf(File,"%s",qPrintable(text));
    fflush(File);
    mutex.unlock();
}

void LogHelper::smartPrintDebugMessage(QString msg)
{
    // Подготовка текста для вывода

    QTime currTime = QTime::currentTime();
    QString timeText = currTime.toString("hh:mm:ss.zzz");
    msg=timeText+"\t"+msg;
    // Быстрый вывод в консоль
    fprintf(stderr, "%s", qPrintable(msg));
    // Вывод в файл лога
    printToLogFile(msg);
}

// Обработчик (хендлер) вызовов qDebug()

// Внутри этого обработчика нельзя использовать вызовы qDebug(), т. к. получится рекурсия

void LogHelper::myMessageOutput(QtMsgType type,
                                const QMessageLogContext &context,
                                const QString &msgText)
{
    QString position="";
    if (context.file!=nullptr) {
        position+=QString::fromUtf8(context.file)+":"+QString::number(context.line)+"\t";
    }
    switch (type) {
    case QtDebugMsg:
        // Отладочный вывод возможен только при компиляции в режиме отладки
#ifdef QT_DEBUG
        smartPrintDebugMessage("DEBUG\t"+position+msgText+"\n");
#endif
        break;
    case QtWarningMsg:
        smartPrintDebugMessage("WARNING\t"+position+msgText+"\n");
        break;
    case QtCriticalMsg:
        smartPrintDebugMessage("ERROR\t"+position+msgText+"\n");
        break;
    case QtFatalMsg:
        smartPrintDebugMessage("FATAL\t"+position+msgText+"\n");
        abort();
    case QtInfoMsg:
        smartPrintDebugMessage("INFO\t"+msgText+"\n");
        break;
    }
}


void LogHelper::setDebugMessageHandler(QString logPath,int days)
{
    m_logPath=logPath;
    savedays=days;
    // Задается статическое значение имени файла лога
    m_logFileName=getName();
    File=fopen(qPrintable(m_logPath+m_logFileName),"a+");
    isFile=true;
    if (File==nullptr){
        fprintf(stderr,"%s",qPrintable(m_logFileName));
        isFile=false;
    }
    // Старые лог-файл удаляются
    clearLogFiles();
    // Устанавливается Qt-обработчик консольного вывода
    qInstallMessageHandler(myMessageOutput);

}

void LogHelper::clearLogFiles()
{
    if (savedays<=0) return;
    // Удаляем все старые файлы в логах системы пролежавшие больше положенного
    QDate currDate = QDate::currentDate();
    QDir dir(m_logPath);
    dir.setNameFilters(QStringList("*.log"));
    QFileInfoList files=dir.entryInfoList(QDir::Files,QDir::NoSort);
    foreach (auto file, files) {
        QDate date=QDate::fromString(file.baseName(),"yyyy-MM-dd");
        if (date.daysTo(currDate)>savedays) {
            QFile::remove(file.absoluteFilePath());
        }
    }
}

void LogHelper::newDay()
{
    QString newName=getName();
    if (newName!=m_logFileName){
        fclose(File);
        m_logFileName=newName;
        m_logFileName=getName();
        File=fopen(qPrintable(m_logPath+m_logFileName),"a+");
        isFile=true;
        if (File==nullptr){
            fprintf(stderr,"%s",qPrintable(m_logFileName));
            isFile=false;
        }
    }
}

QString LogHelper::getName()
{
    QDate currDate = QDate::currentDate();
    return currDate.toString("yyyy-MM-dd")+".log";

}
