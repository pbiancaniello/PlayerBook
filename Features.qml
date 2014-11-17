import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2
import Custom 1.0

Item {
    id: features
    anchors.fill: parent
    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10
        ColumnLayout {
            id: leftCol
            //Layout.minimumWidth: 250
            //Layout.maximumWidth: 250
            Layout.maximumHeight: parent.height
            RowLayout {
                Label {
                    text: "Features"
                    font.family: "Beleren"
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 12
                }
            }

            RowLayout {
                TableView {
                    id: playerFeatureTable
                    model: character.features.list
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    anchors.fill: parent
                    TableViewColumn {
                        role: "name"
                        title: "Name"
                        //width: 80
                        //resizable: false
                        //movable: false
                    }
                    TableViewColumn {
                        role: "source"
                        title: "Source"
                        //width: 80
                        //resizable: false
                        //movable: false
                    }
                    on__CurrentRowItemChanged: {
                        if(currentRow>=0&&rowCount>0){
                            //removeSpellButton.enabled = true
                            //spellView.spell = playerSpells.get(currentRow)
                            featureView.feature = character.features.get(currentRow)
                        }
                    }
                    onRowCountChanged:
                        if(rowCount<1){
                            //removeSpellButton.enabled = false
                            //addSpellButton.visible = true
                        }
                }
            }
            RowLayout {
                id: buttonRow
                Button {
                    text: "Find spell"
                    Layout.fillWidth: true
                    //onClicked: addSpellWindow.visible = true
                    //onClicked: playerFeatures.addContent(database.monsters.get(0))
                }
                Button {
                    id: removeSpellButton
                    text: "Remove spell"
                    enabled: false
                    Layout.fillWidth: true
                    /*onClicked: {
                        if(playerSpellTable.currentRow>=0){
                            playerSpells.remove(playerSpellTable.currentRow)
                            //enabled = false
                        }
                    }*/
                }
            }
        }
        ColumnLayout {
            id: rightCol
            Layout.maximumHeight: parent.height
            Layout.minimumWidth: 350
            Layout.maximumWidth: 350
            anchors {
                top: parent.top
                bottom: parent.bottom
            }
            FeatureViewer{
                id: featureView
                anchors.fill: parent
            }
            Window{
                id: featureSpells
                visible: false
                minimumWidth: 360
                minimumHeight: 400
                maximumWidth: minimumWidth
                maximumHeight: minimumHeight
                SpellViewer{
                    //spell: modelData
                }
            }
        }
    }
}
