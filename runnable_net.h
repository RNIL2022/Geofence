#ifndef RUNNABLE_NET_H
#define RUNNABLE_NET_H
#include <QObject>
#include <QRunnable>
#include <QThread>
#include<unistd.h>
#include <QTcpSocket>

class Runnable : public QRunnable
{
    QString mNumber = "";
    QObject *mReceiver;
    bool mRunning;
public:
    Runnable(QObject *receiver){
        mReceiver = receiver;
        mRunning = false;
    }



bool check()
{
    QTcpSocket* sock = new QTcpSocket();
    sock->connectToHost("www.google.com", 80);
    bool connected = sock->waitForConnected(30000);

    if (!connected)
    {
        sock->abort();
        qDebug() <<"false";
        return false;
    }
    sock->close();
    return true;
}
    void run(){
        mRunning = true;
        while(mRunning){
            sleep(1);
            if(check()){
                mNumber="Connected";
            }
            else{
                mNumber="Not Connected";
            }
            QMetaObject::invokeMethod(mReceiver, "setNumber",
                                      Qt::QueuedConnection,
                                      Q_ARG(QString, mNumber));
            QThread::msleep(10);
        }
    }
    bool isRunning() const{
        return mRunning;
    }
    void stop(){
        mRunning = false;
    }
};

#endif // RUNNABLE_NET_H
