import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2
import Custom 1.0

Item {
    id: spellcasting
    anchors.fill: parent
    TabView{
        anchors.fill: parent
        Tab{
            title: "Main"
            anchors.fill: parent
            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10
                ColumnLayout {
                    id: leftCol
                    Layout.maximumHeight: parent.height
                    Text{
                        text: {
                            var v = "<b>Spell Slots</b><br>As a "
                            if(character.numPages()>1){
                                v+="multiclass spellcaster with caster level "
                                v+character.casterLevel()+" you have the following spell slots:"
                            } else /*if(character.numPages()==1)*/{
                                var c = character.getCastingPage(0).c_class
                                v+="level "+character.getClassLevel(c)+" "+c
                                v+" you have the following spell slots:"
                            }
                        }
                        visible: character.isCaster()
                    }
                    RowLayout{
                        id: spellSlots
                        visible: character.isCaster()
                        property var slots: {
                            //database.getMCSpellSlots(character.casterLevel())
                            database.getMCSpellSlots(20)
                        }
                        spacing: 7
                        Repeater{
                            model:9
                            ColumnLayout{
                                Text{
                                    text:"LVL "+(index+1)
                                    font.bold: true
                                    anchors.horizontalCenter: parent.horizontalCenter
                                }
                                SpinBox{
                                    id: temp
                                    minimumValue: 0
                                    maximumValue: spellSlots.slots[index]
                                    value: maximumValue
                                    implicitWidth: 40
                                    Text{
                                        x: 10
                                        y: 3
                                        text:"/"+parent.maximumValue
                                    }
                                }
                            }
                        }
                    }
                    RowLayout{
                        visible: character.isCaster()
                        Text{
                            text: "Extra Spells"
                            font.family: "Beleren"
                            font.pixelSize: 12
                        }
                        Text{
                            text: "(These are usually spells granted by feats/features)"
                            font.pixelSize: 12
                            font.italic: true
                        }
                    }
                    Text{
                        visible: !character.isCaster()
                        text: "You do not possess any spellcasting ability"
                        font.family: "Beleren"
                        font.pixelSize: 16
                        anchors.top: parent.top
                        anchors.topMargin: 4
                    }
                    TableView {
                        id: playerExtraSpellTable
                        visible: character.isCaster()
                        model: character.extraSpells.list
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        TableViewColumn {
                            role: "name"
                            title: "Name"
                            width: 185
                            //resizable: false
                            movable: false
                        }
                        TableViewColumn {
                            role: "level"
                            title: "Level"
                            width: 35
                            //resizable: false
                            movable: false
                        }
                        TableViewColumn {
                            role: "school"
                            title: "School"
                            width: 120
                            //resizable: false
                            movable: false
                        }
                        onCurrentRowChanged: {
                            if(currentRow>=0&&rowCount>0){
                                spellView.spell = character.extraSpells.get(currentRow)
                            }
                        }

                        onRowCountChanged:{
                            if(rowCount<1){
                                spellView.spell = null
                            }
                        }
                    }
                    Window {
                        id: addSpellWindow
                        title: "Spell Database"
                        minimumWidth: 450
                        minimumHeight: 350
                        maximumWidth: minimumWidth
                        maximumHeight: minimumHeight
                        ColumnLayout{
                            width: addSpellWindow.width
                            anchors.fill: parent
                            Text{
                                id: aswText
                                text: "Spells available in the database:"
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.pointSize: 12
                                font.bold: true
                            }
                            TableView{
                                id: spellTable
                                model: database.spells.list
                                anchors.top: aswText.bottom
                                anchors.left: parent.left
                                anchors.right: parent.right
                                anchors.bottom: aswButtons.top
                                anchors.margins: 4
                                sortIndicatorVisible: true
                                onSortIndicatorColumnChanged: {
                                    database.spells.sortSpells(getColumn(sortIndicatorColumn).role)
                                    //console.log(sortIndicatorColumn)
                                    console.log(getColumn(sortIndicatorColumn).role)
                                    model = database.spells.list
                                    console.log(sortIndicatorOrder)
                                }

                                TableViewColumn {
                                    role: "name"
                                    title: "Name"
                                    width: 185
                                    //resizable: false
                                    movable: false
                                }
                                TableViewColumn {
                                    role: "level"
                                    title: "Level"
                                    width: 35
                                    //resizable: false
                                    movable: false
                                }
                                TableViewColumn {
                                    role: "school"
                                    title: "School"
                                    width: 120
                                    //resizable: false
                                    movable: false
                                }
                                on__CurrentRowItemChanged: {
                                    if(currentRow>=0){
                                        addSpellButton.enabled = true
                                        if(character.extraSpells.contains(database.spells.get(currentRow))){
                                            addSpellButton.enabled = false
                                        }
                                    } else if(currentRow<0){
                                        addSpellButton.enabled = false
                                    }
                                }
                            }
                            RowLayout{
                                id: aswButtons
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 20
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 4
                                Button{
                                    id: addSpellButton
                                    text: "Add spell"
                                    enabled: false
                                    onClicked: {
                                        character.extraSpells.addContent(database.spells.get((spellTable.currentRow)))
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
                        visible: character.isCaster()
                        Button {
                            text: "Add new spell"
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
                                    spellView.spell = null
                                    //enabled = false
                                }
                            }
                        }
                    }
                }
                ColumnLayout {
                    id: rightCol
                    visible: character.isCaster()
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
        CastingPage{
            id: wiz
            c_class: "Wizard"
            c_subclass: "Enchantment"
            weight: 1
            stat: "Intelligence"
            formula: "intmod+classlevel"
        }
        CastingPage{
            id: sorc
            c_class: "Sorceror"
            c_subclass: "Draconic"
            weight: 1
            stat: "Charisma"
        }
        Tab{
            title: wiz.c_class
            anchors.fill: parent
            CastingTab{
                page: wiz
                anchors.fill: parent
            }
        }
        Tab{
            title: sorc.c_class
            anchors.fill: parent
            CastingTab{
                page: sorc
                anchors.fill: parent
            }
        }
    }
}
