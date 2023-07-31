#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "serial.h"
#include "netcheck.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
//    SerialManager s;
//    s.startReading();
    qmlRegisterType<SerialManager>("kunal",1,0,"Serial");
    qmlRegisterType<Net>("kunal",2,0,"Net");
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Serial_delete/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
