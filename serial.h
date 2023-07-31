#ifndef SERIAL_H
#define SERIAL_H
#include<QObject>
#include <QSerialPort>
#include <QTimer>
#include <QDebug>
class SerialManager : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString lat READ lat WRITE setLat NOTIFY latChanged)
    Q_PROPERTY(QString lon READ lon WRITE setLon NOTIFY lonChanged)
    Q_PROPERTY(int ans READ ans WRITE setAns NOTIFY ansChanged)
    explicit SerialManager(QObject *parent = nullptr);
    ~SerialManager();
    QString lat();
    QString lon();
    int ans(){
        qDebug()<<"answer constructor "<<mans;
        return mans;
    }

    struct GeoPoint {
        double lat;
        double lon;

    };
    std::vector<GeoPoint> fencePoints = {};
    Q_INVOKABLE void add_geopoint(double latitude, double longitude){
        GeoPoint x;
        x.lat=latitude;
        x.lon=longitude;
        fencePoints.push_back(x);
        //        qDebug()<<fencePoints[0];
    }
    Q_INVOKABLE void clear_geopoint(){
        fencePoints.clear();
    }
    bool isInsideGeofence(double lat, double lon) {
        bool inside = false;
        for (int i = 0, j = fencePoints.size() - 1; i < fencePoints.size(); j = i++) {
            if (((fencePoints[i].lat > lat) != (fencePoints[j].lat > lat)) &&
                (lon < (fencePoints[j].lon - fencePoints[i].lon) * (lat - fencePoints[i].lat) / (fencePoints[j].lat - fencePoints[i].lat) + fencePoints[i].lon)) {
                inside = !inside;
            }
        }
        return inside;
    }
    void handleCoordinates(double latitude, double longitude)
    {
        // Do something with the latitude and longitude values
        //        QGeoCoordinate coordinate(latitude, longitude);

        if(fencePoints.size()<1){
            qDebug()<<"zero array";
            mans=0;
            emit ansChanged();
        }
        else{
            for (int i = 0, j = fencePoints.size() - 1; i < fencePoints.size(); j = i++) {
                qDebug()<<fencePoints[i].lat<<" "<<fencePoints[i].lon<<Qt::endl;
            }
            if (isInsideGeofence(latitude, longitude)) {
                mans=1;
                qDebug() << "User is inside the geofence"<<mans;

                emit ansChanged();
            } else {
                mans=2;
                qDebug() << "User is outside the geofence"<<mans;

                emit ansChanged();
            }
        }
        //        return ans;
    }

    Q_INVOKABLE void startReading();

signals:
    void latChanged();
    void lonChanged();
    void ansChanged();

public slots:
    void handleSerialError(QSerialPort::SerialPortError error);
    void readData();
    void setLat();
    void setLon();
    void setAns(){

    }

private:
    QString mlat,mlon;
    int mans;
    QSerialPort *serialPort;
    QTimer *reconnectTimer;
     QString portName; // Replace with the name of your serial port (e.g., "COM3" or "/dev/ttyACM0")
    const int baudRate; // Replace with the baud rate of your serial communication (e.g., 9600)
};


#endif // SERIAL_H
