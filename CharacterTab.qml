import QtQuick 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1

import Custom 1.0


ScrollView{
RowLayout {
    id: firstRow
    anchors.margins: 10
    spacing: 10
    anchors.top: parent.top
    anchors.topMargin: 10
    anchors.left: parent.left
    anchors.leftMargin: 10
    Rectangle {
        id: portraitField
        width: 250
        height: 275
        color: "#ffffff"
        Image{
            id: charPortrait
            anchors.horizontalCenter: parent.horizontalCenter
            y: 1
            width: 248
            height: 248
            source: "img/jace.png"
            //sourceSize: 4
        }
        Image{
            source: "img/portrait.png"
        }

        FileDialog {
            id: imageDialog
            title: "Please choose an image file"
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
            y: 250
            width: 250
            height: 25
            text: "Select portrait"
            onClicked: imageDialog.open()
        }
    }
    ColumnLayout{
        id: firstCol
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.left: portraitField.right
        anchors.leftMargin: 50
        Text{
            id: c_name
            //text: character.name
            text: character.name
            font.bold: true
            font.pixelSize: 20
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
            }
            Text {
                id: c_race
                text: (character.subrace!=""?character.subrace:character.race)
                font.pointSize: 12
            }
            Text{
                text: character.className
                font.pointSize: 12
            }
        }
        RowLayout{
            Text{
                id: c_alignment
                text: character.alignment
                font.pointSize: 12
            }
            Text{
                id: c_background
                text: character.background
                font.pointSize: 12
            }
            Button{
                text: "TEST"
                onClicked:{
                    character.alignment = "Neutral"
                    character.background = "Scholar"
                    //character.level = 20
                    character.level = character.scores[0]
                    console.log(character.getLeveledEffects(3)[0])
                }
            }
        }
    }
}
}
