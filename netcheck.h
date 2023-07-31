#ifndef NETCHECK_H
#define NETCHECK_H

#include "runnable_net.h"

#include <QObject>
#include <QThreadPool>

class Net : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY numberChanged)
public:
    explicit Net(QObject *parent   = nullptr):QObject(parent){
        m_number = "";
       runnable = new Runnable(this);
               if(!runnable->isRunning())
                   QThreadPool::globalInstance()->start(runnable);
    }
    ~Net(){
        runnable->stop();
    }
    QString number() const{
        return m_number;
    }
public slots:
    void setNumber(QString number){
        if(number == m_number)
            return;
        m_number = number;
        emit numberChanged(m_number);
    }
signals:
    void numberChanged(QString);
private:
    QString m_number;
    Runnable *runnable;
};

#endif // NETCHECK_H
