import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0

import Custom 1.0

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
            Layout.maximumHeight: parent.height
            RowLayout {
                Label {
                    text: "Available Pets/Companions/Transformations"
                    font.family: "Beleren"
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 12
                }
            }

            RowLayout {
                ContentList {id: playerMonsters}
                TableView {
                    id: playerMonsterTable
                    model: playerMonsters.list
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    anchors.fill: parent
                    TableViewColumn {
                        role: "name"
                        title: "Name"
                        width: 80
                    }
                    TableViewColumn {
                        role: "size"
                        title: "Size"
                        width: 50
                        //resizable: false
                        //movable: false
                    }
                    TableViewColumn {
                        role: "type"
                        title: "Type"
                        width: 80
                    }
                    TableViewColumn {
                        role: "alignment"
                        title: "Alignment"
                        width: 100
                    }
                    onCurrentRowChanged: {
                        if(currentRow>=0&&rowCount>0){
                            monsterView.monster = playerMonsters.get(currentRow)
                            /*var ms = monsterView.monster.spells
                            if(ms.length>0){
                                for(var i=0; i<ms.length; i++){
                                    var index = database.spells.containsSpell(ms[i])
                                    if(index>=0){
                                        monsterSpells.addContent(database.spells.get(index))
                                    }
                                }
                            } else{
                                //monsterSpells.clear()
                                //if(monsterSpellsWindow.visible == true){
                                    //monsterSpellsWindow.visible = false
                                //}
                            }*/
                        }
                    }
                    onRowCountChanged: removeMonsterButton.enabled = (rowCount>0)
                }
            }
            Window {
                id: addMonsterWindow
                title: "Monster database"
                minimumWidth: 200
                minimumHeight: 300
                maximumWidth: minimumWidth
                maximumHeight: minimumHeight
                ColumnLayout{
                    Text{
                        text: "Monsters available in database:"
                    }
                    TableView{
                        id: monsterTable
                        model: database.monsters.list
                        TableViewColumn {
                            role: "name"
                            title: "Name"
                        }
                        on__CurrentRowItemChanged: {
                            if(currentRow>=0){
                                addMonsterButton.enabled = true
                                if(playerMonsters.contains(database.monsters.get(currentRow))){
                                    addMonsterButton.enabled = false
                                }
                            } else if(currentRow<0){
                                addMonsterButton.enabled = false
                            }
                        }
                    }
                    RowLayout{
                        Button{
                            id: addMonsterButton
                            text: "Add monster"
                            enabled: false
                            onClicked: {
                                playerMonsters.addContent(database.monsters.get((monsterTable.currentRow)))
                                enabled = false
                            }
                        }
                        Button{
                            text: "Exit"
                            enabled: true
                            onClicked: addMonsterWindow.close()
                        }
                    }
                }
            }
            RowLayout {
                id: buttonRow
                Button {                    
                    text: "Find monster"
                    Layout.fillWidth: true
                    onClicked: addMonsterWindow.visible = true
                }
                Button {
                    id: removeMonsterButton
                    text: "Remove monster"
                    enabled: false
                    Layout.fillWidth: true
                    onClicked: {
                        if(playerMonsterTable.currentRow>=0){
                            playerMonsters.remove(playerMonsterTable.currentRow)
                            if(playerMonsterTable.rowCount<1){
                                enabled = false
                                monsterView.monster = null
                            }
                        }
                    }
                }
                Button {
                    text: "View Monster Spells"
                    //visible: monsterView.monster!=null&&monsterView.monster.spells.length>0
                    visible: false
                    Layout.fillWidth: true
                    onClicked: monsterSpellsWindow.visible = true
                }
                Button {
                    text: "Create new monster"
                    Layout.fillWidth: true
                    onClicked: buildMonsterWindow.visible = true
                }
            }
        }
        Window{
            id: monsterSpellsWindow
            visible: false
            minimumWidth: 360
            minimumHeight: 400
            maximumWidth: minimumWidth
            maximumHeight: minimumHeight
            Rectangle{
                id: viewRec
                width: 350
                height: 300
                anchors.horizontalCenter: parent.horizontalCenter
                SpellViewer{
                    id: monsterSpellView
                }
            }
            Rectangle{
                width: 350
                height: 100
                anchors.top: viewRec.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                ContentList {id: monsterSpells}
                TableView{
                    id: temp
                    //anchors.bottom:
                    model: monsterSpells.list
                    width: parent.width
                    height: parent.height
                    TableViewColumn {
                        role: "name"
                        title: "Spell Name"
                    }
                    onCurrentRowChanged: {
                        if(currentRow>=0&&rowCount>0){
                            monsterSpellView.spell = monsterSpells.get(currentRow)
                        }
                    }
                }
            }
        }

        Window{
            id: buildMonsterWindow
            visible: false
            minimumWidth: 750
            minimumHeight: 440
            maximumWidth: minimumWidth
            maximumHeight: minimumHeight
            MonsterBuilder{
                id: mb
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
            MonsterViewer{
                id: monsterView
                anchors.fill: parent
            }
        }
    }
}
