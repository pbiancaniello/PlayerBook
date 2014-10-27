import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2
import Custom 1.0

Item {
    id: spellcasting
    anchors.fill: parent
    RowLayout {
        anchors.fill:parent
        anchors.margins: 10
        spacing: 10
        ColumnLayout {
            id: leftCol
            //Layout.minimumWidth: 250
            //Layout.maximumWidth: 250
            Layout.maximumHeight: parent.height
            RowLayout {
                Label {
                    text: "Available Spells"
                    font.family: "Beleren"
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 12
                }
            }

            RowLayout {
                TableView {
                    id: playerSpellTable
                    model: character.spells.list
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    anchors.fill: parent
                    TableViewColumn {
                        role: "name"
                        title: "Name"
                        width: 80
                        //resizable: false
                        //movable: false
                    }
                    on__CurrentRowItemChanged: {
                        if(currentRow>=0&&rowCount>0){
                            removeSpellButton.enabled = true
                            spellView.spell = character.spells.get(currentRow)
                        }
                    }
                    onRowCountChanged:
                        if(rowCount<1){
                            removeSpellButton.enabled = false
                            addSpellButton.visible = true
                            spellView.spell = null
                        }
                }
            }
            Window {
                id: addSpellWindow
                title: "Spell Database"
                minimumWidth: 200
                minimumHeight: 300
                maximumWidth: minimumWidth
                maximumHeight: minimumHeight
                ColumnLayout{
                    Text{
                        text: "Spells available in database:"
                    }
                    TableView{
                        id: spellTable
                        model: database.spells.list
                        TableViewColumn {
                            role: "name"
                            title: "Name"
                        }
                        on__CurrentRowItemChanged: {
                            if(currentRow>=0){
                                addSpellButton.enabled = true
                                if(character.spells.contains(database.spells.get(currentRow))){
                                    addSpellButton.enabled = false
                                }
                            } else if(currentRow<0){
                                addSpellButton.enabled = false
                            }
                        }
                    }
                    RowLayout{
                        Button{
                            id: addSpellButton
                            text: "Add spell"
                            enabled: false
                            onClicked: {
                                character.spells.addContent(database.spells.get((spellTable.currentRow)))
                                enabled = false
                            }
                        }
                        Button{
                            text: "Exit"
                            enabled: true
                            onClicked: addSpellWindow.close()
                        }
                    }
                }
            }
            RowLayout {
                id: buttonRow
                Button {
                    text: "Find spell"
                    Layout.fillWidth: true
                    onClicked: addSpellWindow.visible = true
                }
                Button {
                    id: removeSpellButton
                    text: "Remove spell"
                    enabled: false
                    Layout.fillWidth: true
                    onClicked: {
                        if(playerSpellTable.currentRow>=0){
                            character.spells.remove(playerSpellTable.currentRow)
                            //enabled = false
                        }
                    }
                }
                Window{
                    id: testSpellViewWindow
                    visible: false
                    minimumWidth: 360
                    minimumHeight: 300
                    maximumWidth: minimumWidth
                    maximumHeight: minimumHeight
                    SpellViewer{
                        id: testSpellView
                    }
                }
                Button {
                    text: "Test spell viewer"
                    Layout.fillWidth: true
                    onClicked: {
                        if(playerSpellTable.currentRow>=0){
                            testSpellView.spell = character.spells.get(playerSpellTable.currentRow)
                            testSpellViewWindow.visible = true
                        }
                    }
                }
            }
        }
        ColumnLayout {
            id: rightCol
            Layout.minimumWidth: 350
            Layout.maximumWidth: 350
            Layout.maximumHeight: parent.height
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            SpellViewer{
                id: spellView
                anchors.fill: parent
            }
        }
    }
}
