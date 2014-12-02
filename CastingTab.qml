import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.Controls.Styles 1.2
import Custom 1.0

Item {
    id: castingtab
    anchors.fill: parent
    property CastingPage page
    RowLayout {
        anchors.fill:parent
        anchors.margins: 10
        spacing: 10
        ColumnLayout {
            id: leftCol
            //Layout.minimumWidth: 250
            //Layout.maximumWidth: 250
            Layout.maximumHeight: parent.height
            Text{
                text: {
                    var v
                    if(page.c_subclass!=""){
                        v = page.c_subclass+" "+page.c_class
                    } else{
                        v = page.c_class+" "
                    }
                    v += " "+character.getClassLevel(page.c_class)
                }
                font.family: "Beleren"
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 14
                font.bold: true
            }
            RowLayout{
                spacing: 1
                Text{
                    text: "Spells Known"
                    font.family: "Beleren"
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 9
                }
                Text{
                    text: " ("+page.stat+" is your spellcasting ability for these spells)"
                    font.pointSize: 9
                    font.italic: true
                }
            }
            RowLayout {
                TableView {
                    id: knownTable
                    model: page.known.list
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    anchors.fill: parent
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
                    onClicked: {
                        if(currentRow>=0&&rowCount>0){
                            removeSpellButton.enabled = true
                            spellView.spell = page.known.get(currentRow)
                        }
                    }
                    onActivated: {
                        if(currentRow>=0&&rowCount>0){
                            removeSpellButton.enabled = true
                            spellView.spell = page.known.get(currentRow)
                        }
                    }
                    onRowCountChanged: {
                        if(rowCount<1&&preparedTable.rowCount<1){
                            removeSpellButton.enabled = false
                            addSpellButton.visible = true
                            spellView.spell = null
                        }
                    }
                }
            }
            RowLayout{
                Text{
                    text: "Spells Prepared"
                    visible: page.formula!=""
                    font.family: "Beleren"
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 9
                }
                Text{
                    text:{
                        var v = page.numPrep(page.formula,character.getClassLevel(page.c_class),character.getMods())
                        "(You may prepare "+(v>0?v:1)+")"
                    }
                    visible: page.formula!=""
                    font.pointSize: 9
                    font.italic: true
                }
            }
            RowLayout {
                TableView {
                    id: preparedTable
                    model: page.prepared.list
                    visible: page.formula!=""
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    anchors.fill: parent
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
                    onClicked:{
                        if(currentRow>=0&&rowCount>0){
                            spellView.spell = page.prepared.get(currentRow)
                        }
                    }
                    onActivated:{
                        if(currentRow>=0&&rowCount>0){
                            spellView.spell = page.prepared.get(currentRow)
                        }
                    }
                    onRowCountChanged:{
                        if(rowCount<1&&knownTable.rowCount<1){
                            spellView.spell = null
                        }
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
                                if(page.known.contains(database.spells.get(currentRow))){
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
                                page.known.addContent(database.spells.get((spellTable.currentRow)))
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
                    text: "Add new spell"
                    Layout.fillWidth: true
                    onClicked: addSpellWindow.visible = true
                }
                Button {
                    id: removeSpellButton
                    text: "Remove known spell"
                    enabled: false
                    Layout.fillWidth: true
                    onClicked: {
                        if(knownTable.currentRow>=0){
                            page.known.remove(knownTable.currentRow)
                            spellView.spell = null
                        }
                    }
                }
                Button{
                    visible: page.formula!=""
                    text: "Prepare"
                    enabled: knownTable.rowCount>0
                    onClicked: {
                        if(knownTable.currentRow>=0&&knownTable.rowCount>0){
                            page.prepared.addContent(page.known.get(knownTable.currentRow))
                            page.known.remove(knownTable.currentRow)
                        }
                    }
                }
                Button{
                    visible: page.formula!=""
                    text: "Unprepare"
                    enabled: preparedTable.rowCount>0
                    onClicked: {
                        if(preparedTable.currentRow>=0&&preparedTable.rowCount>0){
                            page.known.addContent(page.prepared.get(preparedTable.currentRow))
                            page.prepared.remove(preparedTable.currentRow)
                        }
                    }
                }
                /*Button{//eventually
                    text:"View class"
                    //onClicked
                }*/
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
