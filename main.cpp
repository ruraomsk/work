#include <QCoreApplication>
#include "libfocus/libfocus.h"
#include "tester/tester.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    LogHelper::setDebugMessageHandler("",1);
    TestMessages t;
    return 0;
}
