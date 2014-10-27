import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

Rectangle {
    id: init
    visible: true
    width: 500
    height: 400
    /*modality: Qt.ApplicationModal
    minimumWidth: 500
    minimumHeight: 400
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight*/
    Text{
        id: controlText
        //text: "WEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"
        visible: false
    }
        Text{
            id: displayText
            x: 73
            y: 46
            width: 335
            height: 56
            text: "Welcome to PlayerBook!\nChoose an existing character or create a new one."
            wrapMode: Text.WordWrap
            font.pointSize: 11
        }
        Button{
            x: 51
            y: 195
            text: "Create new character."
            onClicked: {
                //controlText.visible=true
                //init.visible = false
                theCharacter.setName("The Character")
                displayText.text = theCharacter.getName();
            }
        }
        Button{
            x: 176
            y: 195
            text: "Load existing character..."
            onClicked: {
                controlText.visible=true
                init.visible = false
            }
        }
        Button{
            x: 316
            y: 195
            text: "Exit."
            onClicked: Qt.quit()
        }
    /*onVisibilityChanged: {
        if (visible==false&&controlText.visible==false){
            Qt.quit()
        }
    }*/

}
