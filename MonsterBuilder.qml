import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import Custom 1.0

Item {
    id: monsterBuilder
    width: 750
    height: 440
    Monster{
        id: custom
        name: "Custom Monster"
        source: "Custom"
        size: "Size"
        type: "Type"
        alignment: "alignment"
        speed: "# ft."
        scores: ["10","10","10","10","10","10"]
        sThrows: "Ability score +#, Ability score +#, etc."
        skills: "Skill +#, Skill +#, etc."
        damres: "damage type, damage type, etc."
        damimms: "damage type, damage type, etc."
        conimms: "condition, condition, etc."
        senses: "sense, sense, etc., passive Perception #"
        langs: "Language, Language, etc."
        challenge: "# (# XP)"
        Component.onCompleted: {
            AC = "# (armor)"
            HP = "# (hit dice + modifier)"
            addTrait("<b><i>Trait. </i></b>This is a trait.")
            addAction("<b><i>Action. </i></b>This is an action.")
            addReaction("<b><i>Reaction. </i></b>This is a legendary action.")
            addLAction("This monster may take # legendary actions.")
            addLAction("<b><i>Legendary Action. </i></b>This is a legendary action.")

        }
    }
    RowLayout{
        anchors.fill: parent
        anchors.margins: 6
        spacing: 6
        ColumnLayout{
            id: leftCol
            width: 350
            height: parent.height
            Rectangle{
                anchors.fill: parent
                color: "black"
            }
            Button{
                text: "Press me"
                height: 20
                width: 100
                onClicked:{
                    custom.HP = "Test"
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
            MonsterViewer{
                id: monsterView
                anchors.fill: parent
                monster: custom
            }
        }
    }
}
