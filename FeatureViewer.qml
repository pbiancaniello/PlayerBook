import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import Custom 1.0
import QtQuick.Window 2.0

Rectangle{
    id: featureViewer
    property Feature feature
    width: 350
    height: parent.height
    anchors.horizontalCenter: parent.horizontalCenter
    Image {
        id: background
        sourceSize.width: 720
        anchors.top: topBar.top
        anchors.bottom: bottomBar.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: 340
        fillMode: Image.PreserveAspectCrop
        source: "img/parchment.jpg"
    }
    Image{
        id: topBar
        source: "img/featureBar1.png"
        anchors.top: featureViewer.top
    }
    RowLayout{
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        width: 340
        ScrollView{
            id: featureContent
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            visible: true
            anchors.fill: parent
            style: ScrollViewStyle{
                transientScrollBars: true
            }
            ColumnLayout{
                id: featureColumn
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.top: parent.top
                anchors.topMargin: 8
                width: 338
                Text{
                    id: f_name
                    text: (feature!=null?feature.name:"")
                    font.family: "Beleren"
                    font.pointSize: 18
                    color: "#210d06"
                }
                ListModel{id: blank}
                Column{
                    id: descCol
                    anchors.top: f_name.bottom
                    anchors.topMargin: 8
                    spacing: 4
                    Repeater{
                        id: descList
                        model: (feature!=null?feature.desc:blank)
                        Text{
                            text: modelData
                            width: 320
                            wrapMode: Text.WordWrap
                        }
                    }
                }
                Column{
                    id: choiceCol
                    anchors.top: descCol.bottom
                    anchors.topMargin: 6
                    Repeater{
                        model: (feature!=null?feature.choices.list.length:0)
                        Column{
                            property Choice c: feature.choices.list[index]
                            //visible: character.getClassLevel(feature.source)>=c.lvl
                            visible:{
                                if(database.containsClass(feature.source)){
                                    character.getClassLevel(feature.source)>=c.lvl
                                } else{
                                    true
                                }
                            }

                            spacing: 4
                            Text{
                                text: c.desc
                            }
                            ComboBox{
                                model: c.options
                                width: 140
                                currentIndex: c.sel
                                onCurrentIndexChanged:{
                                    character.removeEffect(c.effects[c.sel])
                                    c.sel = currentIndex
                                    character.addEffect(c.effects[c.sel])
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    width: parent.fillWidth
                    height: 30
                }
            }
        }
    }
    Image{
        id: bottomBar
        anchors.bottom: scrollReminder.top
        source: "img/featureBar2.png"
    }
    Text{
        id: scrollReminder
        text: "(Scroll to see the rest of the entry)"
        font.italic: true
        anchors.right: featureViewer.right
        anchors.bottom: featureViewer.bottom
        //visible: descCol.height+215 > featureViewer.height
    }
}
