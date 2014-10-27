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
                ContentList {
                    id: playerFeatures
                    onContentAdded:{
                        console.log(playerFeatures.list.length)
                        console.log(playerFeatures.get(playerFeatures.list.length-1).name)
                    }
                    //playerFeatures.o
                }
                TableView {
                    id: playerFeatureTable
                    model: playerFeatures.list
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
                            //removeSpellButton.enabled = true
                            //spellView.spell = playerSpells.get(currentRow)
                        }
                    }
                    onRowCountChanged:
                        if(rowCount<1){
                            //removeSpellButton.enabled = false
                            //addSpellButton.visible = true
                        }
                }
            }
            /*Window {
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
                                if(playerSpells.contains(database.spells.get(currentRow))){
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
                                playerSpells.addContent(database.spells.get((spellTable.currentRow)))
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
            }*/
            RowLayout {
                id: buttonRow
                Button {
                    text: "Find spell"
                    Layout.fillWidth: true
                    //onClicked: addSpellWindow.visible = true
                    onClicked: playerFeatures.addContent(database.monsters.get(0))
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
            //Layout.minimumWidth: 350
            //Layout.maximumWidth: 350
            Layout.maximumHeight: parent.height
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            Feature{
                id: feature
            }
            Text {
                //text: "FEATURE NAME"
                text: feature.name
                font.family: "Beleren"
                font.pointSize: 18
                font.bold: true
            }
            Text {
                text: "DESCRIPTION"
                font.family: "Beleren"
                font.pointSize: 18
                font.bold: true
            }
            ListModel {
                id: choices
                ListElement { text: "<Choose a spell>" }
                ListElement { text: "Mage Hand" }
                ListElement { text: "Prestidigitation" }
            }
            ComboBox {
                id: cb1
                property string prev: ""
                model: choices
                onCurrentIndexChanged: {
                    if(currentIndex>0){

                    }

                    /*if(prev!=""){
                        var i1 = character.spells.containsSpell(prev)
                        if(i1>=0){
                            console.log("1")
                            character.spells.remove(i1)
                        }
                    }
                    if(currentIndex>0){
                        var i2 = database.spells.containsSpell(currentText)
                        if(i2>=0){
                            console.log("2")
                            character.spells.addContent(database.spells.get(i2))
                        }
                    }
                    prev = currentText*/
                }
            }
            /*Button{
                id: viewSpell
            }*/
            Repeater{
                //model: feature

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
