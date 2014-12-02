import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import Custom 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 500
    minimumWidth: 800
    minimumHeight: 500
    //color: "#ffffff"
    title: "PlayerBook"

    property Character character: base

    Window {
        id: errors
        title: "Parsing Errors"
        visible: true
        modality: Qt.ApplicationModal
        minimumWidth: 500
        minimumHeight: 200
        maximumWidth: minimumWidth
        maximumHeight: minimumHeight
        color: "#ece9d8"
        Component.onCompleted: {
            if(database.errorLog.length<1){
                visible = false;
            }
        }
        Rectangle{
            width:500
            height:65
            color:"#ffffff"
        }
        Image{
            id: warningIcon
            source: "qrc:/img/warningIcon.png"
            fillMode: Image.PreserveAspectFit
            height: 60
            width: 60
            x: 10
            y: 1
        }
        Text{
            id: warningText
            text: "The following errors were detected during parsing:"
            font.pointSize: 9
            font.bold: true
            anchors.left: warningIcon.right
            anchors.leftMargin: 10
            anchors.verticalCenter: warningIcon.verticalCenter
        }
        Rectangle{
            color: "#ffffff"
            anchors.top: warningIcon.bottom
            anchors.topMargin: 20
            anchors.left: warningIcon.left
            width: errors.width-100
            height: 102
        }
        ScrollView{
            id: errorView
            anchors.top: warningIcon.bottom
            anchors.topMargin: 22
            anchors.left: warningIcon.left
            anchors.leftMargin: 2
            height: 100
            width: errors.width-100
            Column{
                spacing: 10
                Repeater{
                    model: database.errorLog
                    Text{
                        text: modelData
                        width: errors.width-120
                        wrapMode: Text.WordWrap
                    }
                }
            }
        }
        Button{
            anchors.left: errorView.right
            anchors.leftMargin: 5
            y: 122
            text: "Ok"
            onClicked:{
                errors.close()
            }
        }
    }

    Window {
        id: init
        property bool control: false
        visible: true
        modality: Qt.ApplicationModal
        minimumWidth: 500
        minimumHeight: 400
        maximumWidth: minimumWidth
        maximumHeight: minimumHeight
        ColumnLayout{
            Text{
                id: displayText
                text: "Welcome to PlayerBook! Choose an existing character or create a new one."
            }
            Button{
                text: "Create new character."
                onClicked: newCharWindow.visible = true
            }
            Button{
                text: "Load existing character...(closes window for now)"
                onClicked: {
                    init.control = true
                    init.close()
                }
            }
            Button{
                text: "Quit."
                onClicked: Qt.quit()
            }
        }
        NewCharacterWindow{
            id: newCharWindow
            visible: false
            anchors.fill: parent
            onVisibleChanged: {
                if(visible==false&&complete==true){
                    init.control = true
                    init.close()
                }
            }
        }
        onVisibilityChanged: {
            if (visible==false&&init.control==false){
                Qt.quit()
            }
        }

    }

    Character{
        id: test
        name: "TEST"
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: {
                    console.log("Open action triggered");
                    //console.log(serialize(test))
                    //charTab.chara = test
                    //charTab.children[0].chara = test
                    character = test
                    character.saveCharacter()
                }
            }
            MenuItem {
                text: "Save"
                onTriggered: {
                    character.saveCharacter()
                }
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    TabView {
        anchors.fill: parent
        Tab {
            title: "Character"
            CharacterTab {
                anchors.fill:parent
            }
        }
        Tab {
            title: "Features"
            Features { anchors.fill: parent }
        }
        Tab {
            title: "Spellcasting"
            //enabled: character.isCaster()
            Spellcasting { anchors.fill: parent }
        }
        Tab {
            title: "Inventory"
            Inventory { anchors.fill:parent }
        }
        Tab {
            title: "Beastiary"
            Beastiary { anchors.fill:parent }
        }
        Tab {
            title: "Actions"
            //enabled: false
            Actions { anchors.fill:parent }
        }
    }
}
