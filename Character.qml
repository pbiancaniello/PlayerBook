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
                text: qsTr("Select portrait")
                onClicked: imageDialog.open()
            }
        }
        ColumnLayout{
            id: secondCol
            anchors.top: parent.top
            //anchors.right: parent.right
            //anchors.topMargin: 10
            Text {
                id: name
                text: qsTr("Name")
                font.bold: true
                font.pixelSize: 16
            }
            Rectangle {
                id: nameField
                width: 280
                height: 28
                //color: "#227ec6"
                color: "#ffffff"
                TextField {
                    id: charName
                    font.pointSize: 16
                    anchors.fill: parent
                    placeholderText: qsTr("Character Name")
                    //font.family: "Beleren"
                }
                Text {
                    id: charNameFinal
                    font.pointSize: 16
                    font.bold: false
                    text: qsTr("Character Name")
                    visible: false
                    font.family: "Matura MT Script Capitals"
                }
            }
            RowLayout{
                id: levelRaceClassRow
                Text {
                    id: level
                    text: qsTr("Level")
                    font.pointSize: 12
                }
                Text {
                    id: levelText
                    width: 20
                    text: qsTr("0")
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 12
                    anchors.left: level.right
                    anchors.leftMargin: 2
                }
                ComboBox {
                    id: raceChoice
                    height: 30
                    width: 80
                    anchors.left: levelText.right
                    anchors.leftMargin: 2
                    model: ListModel {
                        id: races
                        ListElement { text: "<Choose a race>"; }
                        /*ListElement { text: "Dark Elf"; }
                        ListElement { text: "Dragonborn"; }
                        ListElement { text: "Forest Gnome"; }
                        ListElement { text: "Half-Elf"; }
                        ListElement { text: "Half-Orc"; }
                        ListElement { text: "High Elf"; }
                        ListElement { text: "Hill Dwarf"; }*/
                        ListElement { text: "Human"; }
                        /*ListElement { text: "Lightfoot Halfling"; }
                        ListElement { text: "Mountain Dwarf"; }
                        ListElement { text: "Rock Gnome"; }
                        ListElement { text: "Stout Halfling"; }
                        ListElement { text: "Tiefling"; }
                        ListElement { text: "Wood Elf"; }*/
                    }
                    onPressedChanged: {
                        if (races.get(0).text==="<Choose a race>"){
                            //races.remove(0)
                        }
                    }
                    /*onCurrentTextChanged: {
                        className.x = 120 + (raceChoice.currentText.length*2)
                    }*/
                    style: ComboBoxStyle {
                        background: Rectangle{}
                        label: Rectangle{
                            Text {
                                x: -5
                                y: -10
                                text: control.editText
                                font.pointSize: 12
                                //font.bold: false
                            }
                        }
                    }
                }
                Text{
                    id: className
                    text: "Class Name"
                    font.pointSize: 12
                    anchors.left: raceChoice.right
                    anchors.leftMargin: 2
                }
            }
            Button {
                id: button1
                text: "Test"
                onClicked: {
                    //charName.readOnly=!charName.readOnly
                    charName.visible=!charName.visible
                    charNameFinal.text = charName.text;
                    charNameFinal.visible=!charNameFinal.visible
                    levelText.text = levelText.text == "10" ? "0" : "10"
                }
            }
            Button {
                id: button2
                text: "Load"
                onClicked: {
                    //testChar.readCharacter();
                    charName.text = character.name
                }
            }
        }
    }

    RowLayout {
        id: row2
        //width: 100
        //height: 100

        Text {
            id: text1
            text: "<p>paragraph1</p><br>&emsp;&emsp;<b>paragraph2</b>"
            font.pixelSize: 16
        }
    }
}
}
