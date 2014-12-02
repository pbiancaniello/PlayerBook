import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.2

import Custom 1.0

Item {
    id: newCharacterWindow
    property Race race
    property Race subrace
    property bool complete: false
    Rectangle {
        id: raceSelection
        width: 500
        height: 400
        color: "white"
        MouseArea{ //An easy fix to prevent clicking "through" the current rectangle
            anchors.fill:parent
        }
        Text{
            id: racetext
            text: "Please choose a race"
            anchors.left: parent.left
            anchors.leftMargin: 55
            anchors.top: parent.top
            anchors.topMargin: 35
        }
        Button{
            id: back
            text: "Back"
            enabled: true
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: newCharacterWindow.visible=false
        }
        Button{
            id: next1
            text: "Next"
            enabled: false
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked:{
                if(race.choices.list.length>0){
                    racialChoices.visible=true
                } else if(race.subraces.list.length>0){
                    subraceSelection.visible=true
                } else{
                    classSelection.visible=true
                }
            }
        }
        TableView {
            id: raceTable
            model: database.races
            anchors.top: racetext.bottom
            anchors.topMargin: 6
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: 145
            height: 300
            currentRow: 0
            TableViewColumn {
                role: "name"
                title: "Race"
                resizable: false
                movable: false
            }
            on__CurrentRowItemChanged: {
                if (currentRow>=0){
                    next1.enabled = true
                    race = database.getRace(raceTable.currentRow)
                }
            }
        }
        ScrollView{
            anchors.top: racetext.bottom
            anchors.topMargin: 6
            anchors.left: raceTable.right
            anchors.leftMargin: 14
            anchors.bottom: raceTable.bottom
            width: 300
            Column{
                id: descCol
                spacing: 0
                Text{
                    id: racename
                    text: race.name
                    font.bold: true
                    font.pointSize: 20
                    font.family: "Beleren"
                }
                Text{
                    text: "(Source: "+race.source+")<br>"
                    font.italic: true
                }
                ListModel{id: blank}
                Repeater{
                    id: descList
                    model: race.desc
                    Text{
                        text: modelData+"<br>"
                        width: 280
                        wrapMode: Text.WordWrap
                    }
                }
            }
        }
    }
    Rectangle{
        id: racialChoices
        visible: false
        width: 500
        height: 400
        color: "white"
        onVisibleChanged: {
            if(!visible){
                for(var i=0; i<choices.count; i++){
                    choices.itemAt(i).children[1].currentIndex = 0
                }
            }
        }
        MouseArea{ //An easy fix to prevent clicking "through" the current rectangle
            anchors.fill:parent
        }
        Button{
            id: choiceBack
            text: "Back"
            enabled: true
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: racialChoices.visible = false
        }
        Button{
            text: "Next"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked:{
                if(race.subraces.list.length>0){
                    subraceSelection.visible = true
                } else{
                    classSelection.visible = true
                }
            }
        }
        Text{
            id: choiceText
            text: "Please make the following choices for your race:"
            anchors.left: parent.left
            anchors.leftMargin: 55
            anchors.top: parent.top
            anchors.topMargin: 35
        }
        Column{
            id: choiceCol
            anchors.top: choiceText.bottom
            anchors.topMargin: 8
            anchors.left: choiceText.left
            Repeater{
                id: choices
                model: race.choices.list
                Column{
                    property Choice c: race.choices.list[index]
                    spacing: 4
                    Text{
                        text: c.desc
                    }
                    ComboBox{
                        model: c.options
                        width: 140
                        currentIndex: c.sel
                        onCurrentIndexChanged:{
                            character.removeEffect(c.effects[c.sel])
                            c.sel = currentIndex
                            character.addEffect(c.effects[c.sel])
                        }
                    }
                }
            }
        }
    }
    Rectangle {
        id: subraceSelection
        width: 500
        height: 400
        color: "white"
        visible: false
        MouseArea{ //An easy fix to prevent clicking "through" the current rectangle
            anchors.fill:parent
        }
        Text{
            id: subracetext
            text: "Please choose a subrace"
            anchors.left: parent.left
            anchors.leftMargin: 55
            anchors.top: parent.top
            anchors.topMargin: 35
        }
        Button{
            text: "Back"
            enabled: true
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: subraceSelection.visible=false
        }
        Button{
            text: "Next"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked: {
                if(subrace.choices.list.length>0){
                    subracialChoices.visible = true
                } else{
                    classSelection.visible = true
                }
            }
        }
        TableView {
            id: subraceTable
            model: race.subraces.list
            anchors.top: subracetext.bottom
            anchors.topMargin: 6
            anchors.left: parent.left
            anchors.leftMargin: 20
            width: 145
            height: 300
            currentRow: 0
            TableViewColumn {
                role: "name"
                title: "Subrace"
                resizable: false
                movable: false
            }
            on__CurrentRowItemChanged: {
                if(currentRow>=0){
                    subrace = race.subraces.list[currentRow]
                }
            }
        }
        ScrollView{
            anchors.top: subracetext.bottom
            anchors.topMargin: 6
            anchors.left: subraceTable.right
            anchors.leftMargin: 14
            anchors.bottom: subraceTable.bottom
            width: 300
            Column{
                spacing: 0
                Text{
                    text: {
                        if(race!=null&&subrace!=null&&race.subraces.list.length>0){
                            subrace.name
                        } else{
                            ""
                        }
                    }
                    font.bold: true
                    font.pointSize: 20
                    font.family: "Beleren"
                }
                Text{
                    text: "(Source: "+subrace.source+")<br>"
                    font.italic: true
                }
                Repeater{
                    model:{
                        if(race!=null&&subrace!=null&&race.subraces.list.length>0){
                            subrace.desc
                        } else{
                            blank
                        }
                    }
                    Text{
                        text: modelData+"<br>"
                        width: 280
                        wrapMode: Text.WordWrap
                    }
                }
            }
        }
    }
    Rectangle{
        id: subracialChoices
        visible: false
        width: 500
        height: 400
        color: "white"
        MouseArea{ //An easy fix to prevent clicking "through" the current rectangle
            anchors.fill:parent
        }
        Button{
            id: subchoiceBack
            text: "Back"
            enabled: true
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked:{
                //console.log(choices.count)
                for(var i=0; i<subchoices.count; i++){
                    subchoices.itemAt(i).children[1].currentIndex = 0
                }
                subracialChoices.visible=false
            }
        }
        Button{
            text: "Next"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked: classSelection.visible = true
        }
        Text{
            id: subchoiceText
            text: "Please make the following choices for your subrace:"
            anchors.left: parent.left
            anchors.leftMargin: 55
            anchors.top: parent.top
            anchors.topMargin: 35
        }
        Column{
            id: subchoiceCol
            anchors.top: subchoiceText.bottom
            anchors.topMargin: 8
            anchors.left: subchoiceText.left
            Repeater{
                id: subchoices
                model:{
                    if(race!=null&&subrace!=null&&race.subraces.list.length>0){
                        subrace.choices.list
                    } else{
                        blank
                    }
                }
                Column{
                    property Choice c: subrace.choices.list[index]
                    spacing: 4
                    Text{
                        text: c.desc
                    }
                    ComboBox{
                        model: c.options
                        width: 140
                        currentIndex: c.sel
                        onCurrentIndexChanged:{
                            character.removeEffect(c.effects[c.sel])
                            c.sel = currentIndex
                            character.addEffect(c.effects[c.sel])
                        }
                    }
                }
            }
        }
    }
    Rectangle {
        id: classSelection
        visible: false
        width: 500
        height: 400
        color: "#19a19a"
        MouseArea{ //An easy fix to prevent clicking "through" the current rectangle
            anchors.fill:parent
        }
        Text{
            text: "Please choose a class"
        }
        Button{
            text: "Next"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            onClicked: scoreSelection.visible=true
        }
        Button{
            text: "Back"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: classSelection.visible=false
        }
    }
    Rectangle {
        id: scoreSelection
        visible: false
        width: 500
        height: 400
        color: "#3d52de"
        MouseArea{ //An easy fix to prevent clicking "through" the current rectangle
            anchors.fill:parent
        }
        Item{
            id: helper
            function getCost(v){
                if (v<=8){
                    return 0
                } else if(v==9){
                    return 1
                } else if (v==10){
                    return 2
                } else if (v==11){
                    return 3
                } else if (v==12){
                    return 4
                } else if (v==13){
                    return 5
                } else if (v==14){
                    return 7
                } else{ //15 or higher
                    return 9
                }
            }

        }
        Text{
            text: "Please enter your ability scores"
        }
        Text{
            x: 225
            y: 79
            text: 27-p_str.cost-p_dex.cost-p_con.cost-p_int.cost-p_wis.cost-p_cha.cost
        }

        Text {
            x: 119
            y: 119
            text: "STR"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_str
            property int cost: 0
            x: 112
            y: 144
            minimumValue: 0
            value: 8
            onValueChanged: cost = helper.getCost(value)
        }
        Text {
            x: 159
            y: 119
            text: "DEX"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_dex
            property int cost: 0
            x: 152
            y: 144
            minimumValue: 0
            value: 8
            onValueChanged: cost = helper.getCost(value)
        }
        Text {
            x: 199
            y: 119
            text: "CON"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_con
            property int cost: 0
            x: 193
            y: 144
            minimumValue: 0
            value: 8
            onValueChanged: cost = helper.getCost(value)
        }
        Text {
            x: 241
            y: 119
            text: "INT"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_int
            property int cost: 0
            x: 234
            y: 144
            minimumValue: 0
            value: 8
            onValueChanged: cost = helper.getCost(value)
        }
        Text {
            x: 282
            y: 119
            text: "WIS"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_wis
            property int cost: 0
            x: 275
            y: 144
            minimumValue: 0
            value: 8
            onValueChanged: cost = helper.getCost(value)
        }
        Text {
            x: 323
            y: 119
            text: "CHA"
            font.pixelSize: 12
        }
        SpinBox {
            id: p_cha
            property int cost: 0
            x: 316
            y: 144
            minimumValue: 0
            value: 8
            onValueChanged: cost = helper.getCost(value)
        }
        Button{
            text: "Next"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            //onClicked: characterDetails.visible=true
        }
        Button{
            text: "Back"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: scoreSelection.visible=false
        }
        Button{
            text: "Finish"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            onClicked: {
                character.setRace(database.getRace(raceTable.currentRow))
                if(database.getRace(raceTable.currentRow).subraces.list.length>0){
                    character.setSubrace(database.getRace(raceTable.currentRow).subraces.list[subraceTable.currentRow])
                }
                character.addToScore(0, p_str.value)
                character.addToScore(1, p_dex.value)
                character.addToScore(2, p_con.value)
                character.addToScore(3, p_int.value)
                character.addToScore(4, p_wis.value)
                character.addToScore(5, p_cha.value)
                complete=true
                newCharacterWindow.visible = false
            }
        }
    }
    Rectangle {
        id: characterDetails
        visible: false
        width: 500
        height: 400
        color: "#19a19a"
        //anchors.fill: parent
        Text{
            text: "Please choose a class"
        }
        Button{
            text: "Next"
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            //onClicked: scoreSelection.visible=true
        }
        Button{
            text: "Back"
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            onClicked: characterDetails.visible=false
        }
    }
}
