import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1

Item {
    id: beastiary
    anchors.fill: parent

    RowLayout {
        id: contentRow
        anchors.fill:parent
        anchors.margins: 10
        spacing: 10
        ColumnLayout {
            id: leftCol
            Layout.minimumWidth: 250
            Layout.maximumWidth: 250
            RowLayout {
                Label {
                    id: charInv
                    text: qsTr("Character Inventory")
                    font.family: "Beleren"
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 12
                }
            }
            RowLayout {
                id: list
                ListModel {
                    id: dummyModel
                    Component.onCompleted: {
                        for (var i = 0 ; i < 10 ; ++i) {
                            append({"name": i, "type": "Other", "value" :"0 gp"})
                        }
                    }
                }
                TableView {
                    model: dummyModel
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    anchors.fill: parent

                    TableViewColumn {
                        role: "name"
                        title: "Name"
                        width: 80
                        resizable: false
                        movable: false
                    }
                    TableViewColumn {
                        role: "type"
                        title: "Type"
                        width: 60
                    }
                    TableViewColumn {
                        role: "value"
                        title: "Value"
                        width: 40
                    }
                }
            }
            RowLayout {
                id: buttonRow
                Button {
                    id: addItemButton
                    text: "Add Item"
                    //tooltip:"This is an interesting tool tip"
                    Layout.fillWidth: true
                }
            }
        }
        ColumnLayout {
            id: rightCol
            Layout.fillWidth: true
            anchors {
                top: parent.top
                bottom: parent.bottom
            }

            TextArea {
                id: description
                text: "Item Description"
                font.family: "Beleren"
                textFormat: Qt.RichText
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
