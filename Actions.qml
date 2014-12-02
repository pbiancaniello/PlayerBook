import QtQuick 2.3
import Qt.labs.folderlistmodel 2.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item{
    ListView {
        width: 200; height: 400

        FolderListModel {
            id: folderModel
            //nameFilters: ["*.xml"]
            folder: "libraries"
        }

        Component {
            id: fileDelegate
            Text { text: fileName }
        }

        model: folderModel
        delegate: fileDelegate
    }
    SpinBox{
        id: test
        x: 229
        y: 39
        width: 40
        height: 20
        minimumValue: 0
        decimals: 0
        maximumValue: 99
        SpinBoxStyle{
            id:test2
            //incrementControl:
        }

    }

    TextField {
        id: textField1
        x: 270
        y: 131
        width: 14
        height: 14
        font.pointSize: 12
        placeholderText: qsTr("Text Field")
        validator: IntValidator {bottom: 0; top: 3;}
    }

    Text {
        id: text1
        x: 290
        y: 131
        text: qsTr("/3")
        font.pixelSize: 12
    }
}


