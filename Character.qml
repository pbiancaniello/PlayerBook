import QtQuick 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1

ScrollView{
ColumnLayout {
    id: firstCol
    anchors.margins: 10
    spacing: 10

    RowLayout {
        id: firstRow
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        //anchors.right: parent.right
        //anchors.rightMargin: 10
        spacing: 10
        Rectangle {
            id: portraitField
            width: 200
            height: 225
            color: "#ffffff"
            Image{
                id: charPortrait
                width: 200
                height: 200
                source: "img/jace.png"
            }
            FileDialog {
                id: imageDialog
                title: "Please choose an image file"
                //visible: true
                nameFilters: ["Image File (*.png *.jpg *.bmp)"]
                onAccepted: {
                    console.log("You chose: " + imageDialog.fileUrl)
                    charPortrait.source = imageDialog.fileUrl
                }
                onRejected: {
                    console.log("Canceled")
                }
            }
            Button {
                id: portraitButton
                x: 0
                y: 200
                width: 200
                height: 25
                text: "Select portrait"
                onClicked: imageDialog.open()
            }
        }
        ColumnLayout{
            id: secondCol
            anchors.top: parent.top
            //anchors.right: parent.right
            //anchors.topMargin: 10
            Text{
                id: c_name
                text: character.name
                font.bold: true
                font.pixelSize: 16
            }

            RowLayout{
                id: levelRaceClassRow
                Text {
                    id: level
                    text: "Level"
                    font.pointSize: 12
                }
                Text {
                    id: c_level
                    text: character.level
                    font.pointSize: 12
                    anchors.left: level.right
                    anchors.leftMargin: 4
                }
                Text {
                    id: c_race
                    text: (character.subrace!=""?character.subrace:character.race)
                    font.pointSize: 12
                    anchors.left: c_level.right
                    anchors.leftMargin: 4
                }
                Text{
                    text: character.charClass
                    font.pointSize: 12
                    anchors.left: c_race.right
                    anchors.leftMargin: 4
                }
            }
        }
    }
}
}
