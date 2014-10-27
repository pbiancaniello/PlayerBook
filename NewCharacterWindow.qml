import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Item {
    id: newCharacterWindow
    Rectangle {
        id: raceSelection
        width: 500
        height: 400
        color: "#ab3bd6"
        //anchors.fill: parent
        Text{
            x: 74
            y: 35
            text: "Please choose a race"
        }
        Button{
            id: back
            text: "Back"
            enabled: true
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: newCharacterWindow.visible=false
        }
        Button{
            id: next1
            text: "Next"
            enabled: false
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked: classSelection.visible=true
        }
        ListModel {
            id: races
            ListElement { text: "Dark Elf"; }
            ListElement { text: "Dragonborn"; }
            ListElement { text: "Forest Gnome"; }
            ListElement { text: "Half-Elf"; }
            ListElement { text: "Half-Orc"; }
            ListElement { text: "High Elf"; }
            ListElement { text: "Hill Dwarf"; }
            ListElement { text: "Human"; }
            ListElement { text: "Lightfoot Halfling"; }
            ListElement { text: "Mountain Dwarf"; }
            ListElement { text: "Rock Gnome"; }
            ListElement { text: "Stout Halfling"; }
            ListElement { text: "Tiefling"; }
            ListElement { text: "Unicorn"; }
            ListElement { text: "Wood Elf"; }
        }
        ComboBox {
            id: raceChoice
            x: 190
            y: 35
            visible: false
            model: races
            //model: testData.getMonsters()
            //onCurrentIndexChanged: next1.enabled = true
        }
        TableView {
            x: 74
            y: 54
            model: races
            width: 110
            height: 300
            TableViewColumn {
                role: "text"
                title: "Race Name"
                resizable: false
                movable: false
            }
            on__CurrentRowItemChanged: {
                if (currentRow>=0){
                    next1.enabled = true
                }
                //next1.text = testData.getMonsterName(0)
            }
        }
    }
    Rectangle {
        id: classSelection
        visible: false
        width: 500
        height: 400
        color: "#19a19a"
        //anchors.fill: parent
        Text{
            text: "Please choose a class"
        }
        Button{
            text: "Next"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked: scoreSelection.visible=true
        }
        Button{
            text: "Back"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: classSelection.visible=false
        }
    }
    Rectangle {
        id: scoreSelection
        visible: false
        width: 500
        height: 400
        color: "#3d52de"
        //anchors.fill: parent
        Text{
            text: "Please enter your ability scores"
        }
        Text {
            x: 119
            y: 119
            text: "STR"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_str
            x: 112
            y: 144
            minimumValue: 0
            value: 0
        }
        Text {
            x: 159
            y: 119
            text: "DEX"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_dex
            x: 152
            y: 144
            minimumValue: 0
            value: 0
        }
        Text {
            x: 199
            y: 119
            text: "CON"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_con
            x: 193
            y: 144
            minimumValue: 0
            value: 0
        }
        Text {
            x: 241
            y: 119
            text: "INT"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_int
            x: 234
            y: 144
            minimumValue: 0
            value: 0
        }
        Text {
            x: 282
            y: 119
            text: "WIS"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_wis
            x: 275
            y: 144
            minimumValue: 0
            value: 0
        }
        Text {
            x: 323
            y: 119
            text: "CHA"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_cha
            x: 316
            y: 144
            minimumValue: 0
            value: 0
        }
        Button{
            text: "Next"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            //onClicked: characterDetails.visible=true
        }
        Button{
            text: "Back"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: scoreSelection.visible=false
        }
    }
    Rectangle {
        id: characterDetails
        visible: false
        width: 500
        height: 400
        color: "#19a19a"
        //anchors.fill: parent
        Text{
            text: "Please choose a class"
        }
        Button{
            text: "Next"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            //onClicked: scoreSelection.visible=true
        }
        Button{
            text: "Back"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: characterDetails.visible=false
        }
    }
}
