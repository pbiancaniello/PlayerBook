import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import Custom 1.0
import QtQuick.Window 2.0

Rectangle{
    id: spellViewer
    property Spell spell
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
        source: "img/spellBar1.png"
        anchors.top: spellViewer.top
    }
    RowLayout{
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        width: 340
        ScrollView{
            id: spellContent
            //anchors.top: topBar.bottom

            anchors.leftMargin: 5
            anchors.rightMargin: 5
            visible: true
            anchors.fill: parent
            style: ScrollViewStyle{
                transientScrollBars: true
            }
            ColumnLayout{
                id: spellColumn
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.top: parent.top
                anchors.topMargin: 8
                width: 338
                Text{
                    id: s_name
                    text: (spell!=null?spell.name.toUpperCase():"")
                    font.family: "Beleren"
                    font.pointSize: 18
                    color: "#001b2a"
                }
                Text{
                    id: s_category
                    anchors.top: s_name.bottom
                    text:{
                        if(spell!=null){
                            if(spell.level=="0"){
                                spell.school+" cantrip"
                            } else if (spell.level=="1"){
                                   "1st-level "+spell.school
                            } else if (spell.level=="2"){
                                    "2nd-level "+spell.school
                            } else if (spell.level=="3"){
                                    "3rd-level "+spell.school
                            } else{
                                    spell.level+"th-level "+spell.school
                            }
                        } else{
                            ""
                        }
                    }
                    font.italic: true
                    font.pointSize: 9
                    color: "#001b2a"
                }
                Image{
                    id: bar1
                    anchors.top: s_category.bottom
                    anchors.topMargin: 6
                    source: "img/spellDivider1.png"
                    visible: s_name.text!=""
                }
                Text{
                    id: s_castTime
                    text: (spell!=null?"<b>Casting Time </b>"+spell.castTime:"")
                    color: "#001b2a"
                    anchors.top: bar1.bottom
                    anchors.topMargin: 4
                }
                Text{
                    id: s_range
                    text: (spell!=null?"<b>Range </b>"+spell.range:"")
                    color: "#001b2a"
                    anchors.top: s_castTime.bottom
                    anchors.topMargin: 2
                }
                Text{
                    id: s_dur
                    text: (spell!=null?"<b>Duration </b>"+spell.duration:"")
                    color: "#001b2a"
                    anchors.top: s_range.bottom
                    anchors.topMargin: 2
                }
                Image{
                    id: bar2
                    anchors.top: s_dur.bottom
                    anchors.topMargin: 6
                    source: "img/spellDivider1.png"
                    visible: s_name.text!=""
                }
                Column{
                    id: s_comps
                    anchors.top: bar2.bottom
                    anchors.topMargin: 2
                    Text {
                        text: (spell!=null?"<b>Components </b>"+spell.comps:"")
                        width: 320
                        wrapMode: Text.WordWrap
                        color: "#001b2a"
                    }
                }
                Image{
                    id: bar3
                    anchors.top: s_comps.bottom
                    anchors.topMargin: 6
                    source: "img/spellDivider1.png"
                    visible: s_name.text!=""
                }
                Column{
                    id: descCol
                    anchors.top: bar3.bottom
                    anchors.topMargin: 10
                    spacing: 4
                    ListModel{id: blank}
                    Repeater{
                        id: descList
                        model: (spell!=null?spell.desc.split("<br>"):blank)
                        Text{
                            text: modelData
                            width: 320
                            wrapMode: Text.WordWrap
                            textFormat: Text.RichText
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
        source: "img/spellBar2.png"
    }
    Text{
        id: scrollReminder
        text: "(Scroll to see the rest of the entry)"
        font.italic: true
        anchors.right: spellViewer.right
        anchors.bottom: spellViewer.bottom
        visible: descCol.height+215 > spellViewer.height
    }
}
