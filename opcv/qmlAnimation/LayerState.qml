
import QtQuick 2.0

Item {
    Rectangle{
        id: root
        property int duration:3000
        property string layerName: "3"
        property string carName: "68"
        width: 250
        height: 120
        color:"#1ce31d"
        Rectangle{
            id:road
            width: 250
            height: 13
            x:0
            y:root.height-13
            color:"#51413e"
            gradient: Gradient{
                GradientStop{position: 0.0 ;color :"#d3d0cf"}
                GradientStop{position: 1.0 ;color :"#51413e"}
            }
        }
        Rectangle{
            id:roller1
            width: 8
            height: 16
            //anchors.right: root.left
            x:root.width - 8
            y:root.height/4
            color:"#d3d0cf"
        }
        Rectangle{
            id:roller2
            width: 8
            height: 16
            //anchors.right: root.left
            x:root.width - 8
            y:root.height/2
            color:"#d3d0cf"
        }
        Rectangle{
            id:roller3
            width: 8
            height: 16
            //anchors.right: root.left
            x:0
            y:root.height/4
            color:"#d3d0cf"
        }
        Text {
            x:5
            y:5
            font.family: "Helvetica"
            font.pointSize: 14
            color: "grey"
            id: layerText
            text: qsTr("Layer: "+root.layerName)
        }
        Text {
            x:170
            y:5
            font.family: "Helvetica"
            font.pointSize: 14
            color: "grey"
            id: carText
            text: qsTr("CarId:"+root.carName)
        }
        Connections{
            target: MainWindow
            onLayerStateSignal:{carReadyIn(carNumber,state)}
        }
        Connections{
            target:animOut
            onFinished:{
                car.visible = false;
                root.carName = "";
            }
        }

    }
    Image {
        id: car //width 50 height 50
        x:200
        y:70
        source: "qrc:/image/car.png"

        MouseArea{
            anchors.fill: car
            onClicked: {
                car.x = 200;y=70;
                animIn.restart()
                root.color = "#f36d58"
                //animOut.restart()
            }
        }

    }
    ParallelAnimation{
        id:animIn
        SequentialAnimation{

            NumberAnimation {
                target: car
                properties: "x"
                to: root.width/2-30
                duration: root.duration*0.6
                easing.type: Easing.OutCirc
            }
        }
    }

    ParallelAnimation{
        id:animOut
        SequentialAnimation{
            NumberAnimation {
                alwaysRunToEnd: false
                target: car
                properties: "y"
                to: 0
                duration: root.duration*0.8
                easing.type: Easing.OutCirc
            }
        }
    }
    function carReadyIn(carNumber,state){
        if(state === 1) //care ready in layer
        {
            root.color =  "#f36d58"
            root.carName = carNumber;
        }
        else if(state === 2) //car inLayer
        {
            car.visible = true;
            car.x = 200;car.y=70;
            animIn.restart()
        }
        else if(state === 3)//car out
        {
            root.color = "#1ce31d"
            animOut.restart();

        }
    }
}
