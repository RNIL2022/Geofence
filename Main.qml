import QtQuick
import QtLocation 5.15
import QtPositioning
import QtWebEngine
import QtWebChannel 1.0
import QtLocation 6.5
import kunal 1.0
import kunal 2.0
import QtQuick.Controls
import QtQuick.Dialogs

//import kunal 3.0

Window {
    id:window
    width: 800
    height:480
    visible:true
    title:qsTr('Geo Fencing')

    Rectangle{
    color: "white"
    anchors.fill: parent
    z: 4
    Text{
        text: "LOADING . . . "
        font.pixelSize: 25
        y: 200
        x: 350
    }
    opacity: if(myclass.number== "Connected"){
                 serial.startReading()
             return 0
             } else return 1

    }


    property var clickedPoint;
    property string geoVal: "Geofence active" ;

    //plot button object
    QtObject {
        id: plotObject
        property var vis: [];
        property var pt: [serial.lat, serial.lon];
        property var check: 0;


        WebChannel.id: "plotPoly"
        signal someSignal();
        signal someSignal4()
        onSomeSignal: pt = [serial.lat, serial.lon];
        onVisChanged: addGeopoint()
    }

    //redo button object
    QtObject {
        id: redoObject

        WebChannel.id: "redoPoly"

        signal someSignal2();

    }

    QtObject {
            id: loadObject
            property var live: [serial.lat, serial.lon];

            WebChannel.id: "loadObj"

            signal someSignal3();
            onSomeSignal3: {live= [serial.lat, serial.lon]
            console.log(loadObject.live)
            }

        }

    Button{
        z: 3
        y: 350
        id: reload_btn
        x: 740
        height: 50
        width: 50
        Image {
            z: 4
            x: 5
            y: 5
            id: img
            height: 40
            width: 40
            source: "qrc:/reload.png"
        }
        onClicked: {
            web.reload()
            redoObject.someSignal2()
            polygonPlot_btn.opacity = 1
            serial.clear_geopoint()
            window.clickedPoint = " "
            geo_txt.opacity = 0
            dir_txt.opacity=1
            timer.running=true
            liveloc.restart()
        }

    }

    Net{
        id: myclass
    }

    Serial{
        id:serial

    }



//    Nmea{
//        id:nmea
//    }


    function addGeopoint(){
        var coords = plotObject.vis
        var string = ""
        for(var i=0; i<=coords.length; i++){
            serial.add_geopoint(coords[i][0], coords[i][1])
            console.log('point added and latlng:', coords[i][0], coords[i][1])
            var split = coords[i][0] + "  " + coords[i][1] + "\n"
            string = string + split
            window.clickedPoint = string
        }
    }

    function checkGeopoint(){


//            check=serial.handleCoordinates(serial.cord1, serial.cord2);
        var check = serial.ans
        console.log("check serial"+serial.ans)
        console.log(serial.ans+"from qml")
            if(check===1){
                window.geoVal = "You are inside the geofence."
                bulb.color = "green"
                console.log("inside js true")
            }
            else if(check===2){
                window.geoVal = "You are outside the geofence!"
                bulb.color = "red"
                console.log("inside js false", plotObject.pt)
            }
            else{
                window.geoVal = "GeoFence is active"
                bulb.color = "lightgrey"
            }

            console.log('header works')
        }

    Timer {
            id: timer2
            interval: 500;
            running: true;
            repeat: true

            onTriggered: {
                checkGeopoint()
            }
        }
    Timer {
            id: timer3
            interval: 100;
            running: false;
            repeat: true

            onTriggered: {
                plotObject.pt = [serial.lat, serial.lon]
                plotObject.someSignal4()
            }
        }



    RoundButton {
        z: 3
        y: 20
        x: 50
        height: 50
        width: 200
        radius: 10
        id: polygonPlot_btn
        text: "Plot Polygon"
        font.pixelSize: 18
        onPressed: {
            plotObject.someSignal()
            polygonPlot_btn.opacity = 0
            plotObject.pt = " "
            geo_txt.opacity=1
            dir_txt.opacity=0
            timer.running=false
            timer3.running=true
            checkGeopoint()

        }

    }

    RoundButton {
        z: 3
        y: 150
        id: redo_btn
        x: 50
        height: 50
        width: 200
        radius: 10
        text: "Redo Polygon"
        font.pixelSize: 18
        onClicked: {
            redoObject.someSignal2()
            polygonPlot_btn.opacity = 1
            serial.clear_geopoint()
            window.clickedPoint = " "
            geo_txt.opacity = 0
            dir_txt.opacity=1
            timer.running=true
            tmer3.running=false

        }
    }
    RoundButton {
        z: 3
        y: 250
     id: point_btn
        x: 50
        height: 50
        width: 200
        radius: 10
        text: serial.lat
        font.pixelSize: 18
        onClicked: {
            console.log('click event detected' + serial.lat)
            point_btn.text = serial.lat + 'working'
        }
    }

    Rectangle{
        z: 3
        id: bulb_cover
        x: 455
        y: 5
        radius: 40
        height: 40
        width: 40
        opacity: 1
        color: "#555555"

        Rectangle{
            id: bulb
            x: 5
            y: 5
            radius: 30
            height: 30
            width: 30
            opacity: 1
            color: "lightgrey"
        }
    }

    Rectangle{
        z: 2
        color: "#1c1c1c"
        x: 0
        y: 0
        height: 600
        width: 300
        opacity: 0.9

                Text{
                    opacity: 0
                    id: coord_display2
                    color: "white"
                    x: 10
                    y: 510
                    font.pointSize: 10
                    text: "Point Clicked: \n" + plotObject.pt
                }
    }

    Timer {
        id: timer
        interval: 500;
        running: true;
        repeat: true

        property int count: 0
        onTriggered: {
            count++
            if(count%2 == 0)
            bulb.color= "red"

            else if(count%3 == 0)
            bulb.color = "green"

            else
            bulb.color= "lightgrey"
        }
    }

    Rectangle{
        id: geo_txt_cover
        z: 2
        color: "#1c1c1c"
        radius: 5
        x: 450
        y: -5
        height: 55
        width: 400
        opacity: 0.8
        Text{
            id: geo_txt
            color: "white"
            font.pointSize: 13
            x: 50
            y: 15
            text: window.geoVal
            opacity: 0
        }
        Text{
            id: dir_txt
            color: "white"
            font.pointSize: 13
            x: 50
            y: 15
            text: "Mark the plot to activate geofence."
            opacity: 1
        }
    }

    WebChannel {
        id: channel
        registeredObjects: [plotObject, redoObject, loadObject]

    }

    WebEngineProfile {
        id:profile
        httpAcceptLanguage: "en-US,en;q=0.9,es;q=0.8,de;q=0.7";
        httpCacheType: WebEngineProfile.DiskHttpCache
    }

    WebEngineView{
        z: 1
        id:web
        anchors.fill : parent
        profile: profile
        url:"qrc:/mapbuild.html"
        webChannel: channel

        onJavaScriptConsoleMessage: (level,message,ln,sid)=>{
                                        console.log(message);
                                    }

        onFeaturePermissionRequested: {
            console.log("Honcho");
        }


    }

    Timer{
        id: liveloc
    interval: 3000
    running: true
    onTriggered: {loadObject.someSignal3()
}

    }



}


