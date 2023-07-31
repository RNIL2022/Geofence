//#ifndef nmea_h
//#define nmea_h

#include<bits/stdc++.h>
#include<QObject>
#include<QDebug>
using namespace std;

class Nmea: public QObject
{
     Q_OBJECT
public:
//       Q_PROPERTY(QString lat READ lat WRITE setLat NOTIFY latChanged)
//       Q_PROPERTY(QString lon READ lon WRITE setLon NOTIFY lonChanged)
  QString m_lat,m_lon,latt,lonn;
     explicit Nmea(QObject *parent = nullptr):QObject(parent){
         qDebug()<<"in nmea class";
     }
//     QString lat(){
//         return m_lat;
//     }
//     QString lon(){
//         return m_lon;
//     }
//     QString lat;
//     QString lon;
     QString latitudee(QString latitudeValue){
         qDebug()<<"intital value"<<latitudeValue;
//         QString latitudeValue = "2825.9567000";

         double latitude = latitudeValue.toDouble();

         int degrees = static_cast<int>(latitude / 100);
         double minutesSeconds = latitude - (degrees * 100);

         int minutes = static_cast<int>(minutesSeconds);
         double seconds = (minutesSeconds - minutes) * 60.0;

         double decimalDegrees = degrees + (minutes / 60.0) + (seconds / 3600.0);

         QString latitudeString = QString::number(decimalDegrees, 'f', 7);

         qDebug() << "Latitude function : " << latitudeString;

         return latitudeString;
     }

     QString longitudee(QString longitudeValue){
         qDebug()<<"intital value"<< longitudeValue;

         double longitude = longitudeValue.toDouble();

         int degrees = static_cast<int>(longitude / 100);
         double minutesSeconds = longitude - (degrees * 100);

         int minutes = static_cast<int>(minutesSeconds);
         double seconds = (minutesSeconds - minutes) * 60.0;

         double decimalDegrees = degrees + (minutes / 60.0) + (seconds / 3600.0);

         QString longitudeString = QString::number(decimalDegrees, 'f', 7);

         qDebug() << "Longitude function: " << longitudeString; // Output: "Longitude: 77.3069600"

         return longitudeString;
     }

QString dateformat(QString s){
    QString a="/";
    s.insert(2,a);
    s.insert(5,a);
    return s;
}
QString timeformat(QString s){
    QString a=":";
    s.insert(2,a);
    s.insert(5,a);
    return s;
}

void fungll2(std::vector<QString> v){
QString a= v[1];
QString b=v[3];
unordered_map<QString,QString> mapp;
QString s=a.mid(0,2);
{

double d=s.toDouble();
s="";
s=a.mid(2,6);
double m=s.toDouble();
s="";
double latitude = d+(m/60) ;
qDebug()<<"double value"<<latitude;
//m_lat = QString::number(latitude);
m_lat=latitudee(a);

mapp["LATITUDE"]= QString::number(latitude);
}
s="";
{
QString s=b.mid(0,3);
double d= s.toDouble();
s="";
s=b.mid(3,6);
double m=s.toDouble();
s="";
double longitude = d+(m/60) ;
m_lon=longitudee(b);

mapp["LONGITUDE"]= QString::number(longitude);
}
mapp["TIMESTAMP"]=timeformat(v[5]);
mapp["VALIDITY"]=v[6];//A-> ok V-> invalid
mapp["NORTH/SOUTH"]=v[2];
mapp["EAST/WESTT"]=v[4];
//for(auto it : mapp){
//qDebug()<< it.first <<" -> "<< it.second<<"\n";
//    }

qDebug()<<"temprory"<<m_lat<<"kk"<<m_lon;

}

void fungll1(std::vector<QString> v){
QString a= v[1];
QString b=v[3];
unordered_map<QString,QString> mapp;
QString s=a.mid(0,2);
{
double d= s.toDouble();
s="";
s=a.mid(2,6);
double m=s.toDouble();
s="";
double latitude = d+(m/60) ;
qDebug()<<"double value"<<latitude;
//m_lat=QString::number(latitude);
m_lat=latitudee(a);
//emit latChanged();
mapp["LATITUDE"]=QString::number(latitude);
}
s="";
{
QString s=b.mid(0,3);
double d= s.toDouble();
s="";
s=b.mid(3,6);
double m=s.toDouble();
s="";
double longitude = d+(m/60) ;  //+(sec/3600);
m_lon=longitudee(b);
mapp["LONGITUDE"]= QString::number(longitude);
}
mapp["NORTH/SOUTH"]=v[2];
//mapp["EAST/WEST with CHECKSUM"]=v[4];
//for(auto it : mapp){
//        qDebug()<< it.first <<" -> "<< it.second<<"\n";
//    }

    qDebug()<<"temprory"<<m_lat<<"kk"<<m_lon;
}

void fungsv(std::vector<QString> v){
QString a= v[2];
QString b=v[4];
unordered_map<QString,QString> mapp;

mapp["Total number of msg"]=v[1];
mapp["Msg Number"]=v[2];
mapp["Total number of SV's in view"]=v[3];
mapp["SV PRN number"]=v[4];
mapp["Elevation in degrees"]=v[5];
mapp["Azimuth, degrees from true north"]=v[6];
mapp["SNR, 00-99 dB"]=v[7];
mapp["checksum"]=v[v.size()-1].mid(v[v.size()-1].length()-3,3);
//for(auto it : mapp){
//        qDebug()<< it.first <<" -> "<< it.second<<"\n";
//    }
}


void funhdt(std::vector<QString> v){
unordered_map<QString,QString>mapp;
mapp["Heading in degrees"]=v[1];
mapp["Degrees True"]=v[2].mid(0,1);
mapp["Checksum"]=v[2].mid(1,3);
for(auto it:mapp){
    qDebug()<<it.first<<"->"<<it.second<<"\n";
}
}

void funrmc(std::vector<QString> v){
QString a= v[3];
QString b=v[5];
unordered_map<QString,QString> mapp;
QString s=a.mid(0,2);
{
double d= s.toDouble();
s="";
s=a.mid(2,6);
double m=s.toDouble();
s="";
double latitude = d+(m/60) ;
qDebug()<<"double value"<<latitude;
m_lat=latitudee(a);
//emit latChanged();
mapp["LATITUDE"]=QString::number(latitude);
}
s="";
{
QString s=b.mid(0,3);
double d= s.toDouble();
s="";
s=b.mid(3,6);
double m=s.toDouble();
s="";
double longitude = d+(m/60) ;
m_lon=longitudee(b);
mapp["LONGITUDE"]= QString::number(longitude);
}

mapp["TIMESTAMP"]=timeformat(v[1]);
mapp["VALIDITY"]=v[2];//A-> ok V-> invalid
mapp["NORTH/SOUTH"]=v[4];
mapp["EAST/WESTT"]=v[6];
mapp["SPEED IN KNOTS"]=v[7];
mapp["TRUE COURSE"]=v[8];
mapp["DATE STAMP"]=dateformat(v[9]);
mapp["VARIATION"]=v[10];
mapp["CHECKSUM"]=v[11];

//for(auto it : mapp){
//        qDebug()<< it.first <<" -> "<< it.second<<"\n";
//    }
qDebug()<<"temprory"<<m_lat<<"kk"<<m_lon;
}

void fungga(std::vector<QString> v){
QString a= v[2];
QString b=v[4];
unordered_map<QString,QString> mapp;

QString s=a.mid(0,2);
{
double d= s.toDouble();
s="";
s=a.mid(2,6);
double m=s.toDouble();
s="";
double latitude = d+(m/60) ;
qDebug()<<"double value"<<latitude;
m_lat=latitudee(a);

mapp["LATITUDE"]=QString::number(latitude);
}
s="";
{
QString s=b.mid(0,3);
double d= s.toDouble();
s="";
s=b.mid(3,6);
double m=s.toDouble();
s="";
double longitude = d+(m/60) ;
m_lon=longitudee(b);
mapp["LONGITUDE"]= QString::number(longitude);
}
mapp["TIMESTAMP"]=timeformat(v[1]);
mapp["NORTH/SOUTH"]=v[3];
mapp["EAST/WESTT"]=v[5];

mapp["GPS QUALITY INDICATOR"]=v[6];
mapp["NUBER OF SATELLITE IN USE"]=v[7];
mapp["HORIZONTAL DILUTION OF POSITION"]=v[8];
mapp["ANTENNA ALTITUDE"]=v[9];
mapp["METERS in antenna height unit"]=v[10];
mapp["GEOIDAL SEPARATION"]=v[11];
mapp["METER in units of geoidal separation"]=v[12];
mapp["Age in seconds since last update from refrence station"]=v[13];
mapp["Reference Staton id & checksum"]=v[14];
//for(auto it : mapp){
//        qDebug()<< it.first <<" -> "<< it.second<<"\n";
//    }
qDebug()<<"temprory"<<m_lat<<"kk"<<m_lon;
}

void parse(QString s)
{
    qDebug()<<s<<"\n";
    int n=s.length();
    vector<QString>v;
    vector<QString>x;
    QString str;
    int i;
    for(i=0;i<n;i++){
    if(s[i]==','){
    if(str==""){
        str="NULL";
    }
    v.push_back(str);
    str="";
    continue;
    }
    str+=s[i];
    }
    v.push_back(str);
    //

//    if(v[0].mid(0,3)=="$GN")

//    {

    if(v[0].mid(3,3)=="GGA"){
        fungga(v);
        latt=m_lat;
        lonn=m_lon;
    }
//    else if(v[0].mid(3,3)=="GSV"){
//        fungsv(v);
//    }
    else if(v[0].mid(3,3)=="HDT"){
        funhdt(v);
    }
    else if(v[0].mid(3,3)=="RMC"){
        funrmc(v);
        latt=m_lat;
        lonn=m_lon;
    }
    else if(v[0].mid(3,3)=="GLL"){

        for(int i=0;i<v.size();i++){
            if(v[i]=="NULL"){
           continue;
            }
            x.push_back(v[i]);
        }
    if(x.size() <= 6){
    fungll1(x);
    }
    else fungll2(x);
    latt=m_lat;
    lonn=m_lon;
    }
    else{
    m_lat=latt;
    m_lon=lonn;

    }

//    }
//    else{
//    m_lat=latt;
//    m_lon=lonn;
//    qDebug()<<"else condition lat/lon"<<m_lat<<"+"<<m_lon;
//    }
    for(int i=0;i<v.size();i++){
    qDebug()<<v[i]<<" ";
    }
//qDebug()<<"latitude"<<m_lat<<"longitude"<<lon;
}

public slots:
//void setLat(){

//}
//void setLon(){

//}

signals:
// void latChanged();
// void lonChanged();

private:

};
//Nmea nm;
//#endif
