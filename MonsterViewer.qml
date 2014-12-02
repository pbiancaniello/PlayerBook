import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import Custom 1.0
import QtQuick.Window 2.0

Rectangle{
    id: monsterViewer
    property Monster monster
    width: 350
    height: parent.height
    anchors.horizontalCenter: parent.horizontalCenter
    Image {
        id: background
        sourceSize.width: 720
        anchors.top: topBar.top
        anchors.bottom: bottomBar.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: 340
        fillMode: Image.PreserveAspectCrop
        source: "img/parchment.jpg"
    }
    Image{
        id: topBar
        source: "img/monsterBar1.png"
        anchors.top: monsterViewer.top
    }
    RowLayout{
        anchors.top: topBar.bottom
        anchors.bottom: bottomBar.top
        width: 340
        ScrollView{
            id: monsterContent
            anchors.topMargin: 6
            anchors.fill: parent
            style: ScrollViewStyle{
                transientScrollBars: true
            }
            ColumnLayout{
                id: monsterColumn
                anchors.left: parent.left
                anchors.leftMargin: 8
                width: 338
                Text{
                    id: m_name
                    text: (monster!=null?monster.name.toUpperCase():"")
                    font.family: "Beleren"
                    font.pointSize: 18
                    color: "#2a0700"
                }
                Text{
                    id: sizetypealignment
                    anchors.top: m_name.bottom
                    text: (monster!=null?monster.size+" ":"")+(monster!=null?monster.type+", ":"")+(monster!=null?monster.alignment:"")
                    font.italic: true
                    font.pointSize: 9
                    color: "#2a0700"
                }
                Image{
                    id: bar1
                    anchors.top: sizetypealignment.bottom
                    anchors.topMargin: 6
                    source: "img/monsterDivider1.png"
                    visible: monster!=null
                }
                Text {
                    id: m_ac
                    anchors.top: bar1.bottom
                    anchors.topMargin: 4
                    text: (monster!=null?"<b>Armor Class </b>"+monster.AC:"")
                    color: "#2a0700"
                }
                Text {
                    id: m_hp
                    anchors.top: m_ac.bottom
                    anchors.topMargin: 2
                    text: (monster!=null?"<b>Hit Points </b>"+monster.HP:"")
                    color: "#2a0700"
                }
                Text {
                    id: m_speed
                    anchors.top: m_hp.bottom
                    anchors.topMargin: 2
                    text: (monster!=null?"<b>Speed </b>"+monster.speed:"")
                    color: "#2a0700"
                }
                Image{
                    id: bar2
                    anchors.top: m_speed.bottom
                    anchors.topMargin: 6
                    source: "img/monsterDivider1.png"
                    visible: monster!=null
                }
                RowLayout{
                    anchors.top: bar2.bottom
                    anchors.topMargin: 6
                    id: abilityScores
                    spacing: 17
                    anchors.horizontalCenter: parent.horizontalCenter
                    Item{
                        id: helper
                        function getMod(s){
                            var parsed = parseInt(s)
                            if(parsed>11){
                                parsed-=10
                                return " (+"+Math.floor(parsed/2)+")"
                            } else if(parsed<10){
                                parsed=10-parsed
                                return " (-"+Math.ceil(parsed/2)+")"
                            } else {
                                return " (+0)"
                            }
                        }
                    }
                    Text{
                        id: m_str
                        horizontalAlignment: Text.AlignHCenter
                        text: (monster!=null?"<b>STR</b><br>"+monster.scores[0]+helper.getMod(monster.scores[0]):"")
                        color: "#2a0700"
                    }
                    Text{
                        id: m_dex
                        horizontalAlignment: Text.AlignHCenter
                        text: (monster!=null?"<b>DEX</b><br>"+monster.scores[1]+helper.getMod(monster.scores[1]):"")
                        color: "#2a0700"
                    }
                    Text{
                        id: m_con
                        horizontalAlignment: Text.AlignHCenter
                        text: (monster!=null?"<b>CON</b><br>"+monster.scores[2]+helper.getMod(monster.scores[2]):"")
                        color: "#2a0700"
                    }
                    Text{
                        id: m_int
                        horizontalAlignment: Text.AlignHCenter
                        text: (monster!=null?"<b>INT</b><br>"+monster.scores[3]+helper.getMod(monster.scores[3]):"")
                        color: "#2a0700"
                    }
                    Text{
                        id: m_wis
                        horizontalAlignment: Text.AlignHCenter
                        text: (monster!=null?"<b>WIS</b><br>"+monster.scores[4]+helper.getMod(monster.scores[4]):"")
                        color: "#2a0700"
                    }
                    Text{
                        id: m_cha
                        horizontalAlignment: Text.AlignHCenter
                        text: (monster!=null?"<b>CHA</b><br>"+monster.scores[5]+helper.getMod(monster.scores[5]):"")
                        color: "#2a0700"
                    }
                }
                Image{
                    id: bar3
                    //anchors.top: abilityScores.bottom
                    anchors.topMargin: 6
                    source: "img/monsterDivider1.png"
                    visible: monster!=null
                }
                Column{
                    id: dynamicCol
                    spacing: 4
                    Text{
                        id: m_sthrows
                        visible: (monster!=null?monster.sThrows!="":false)
                        width: rightCol.width-21
                        text: (monster!=null?"<b>Saving Throws</b> "+monster.sThrows:"")
                        color: "#2a0700"
                        wrapMode: Text.WordWrap
                    }
                    Text{
                        id: m_skills
                        visible: (monster!=null?monster.skills!="":false)
                        width: rightCol.width-21
                        text: (monster!=null?"<b>Skills</b> "+monster.skills:"")
                        color: "#2a0700"
                        wrapMode: Text.WordWrap
                    }
                    Text{
                        id: m_damvulns
                        visible: (monster!=null?monster.damvulns!="":false)
                        width: rightCol.width-21
                        text: (monster!=null?"<b>Damage Vulnerabilities</b> "+monster.damvulns:"")
                        color: "#2a0700"
                        wrapMode: Text.WordWrap
                    }
                    Text{
                        id: m_damres
                        visible: (monster!=null?monster.damres!="":false)
                        width: rightCol.width-21
                        text: (monster!=null?"<b>Damage Resistances</b> "+monster.damres:"")
                        color: "#2a0700"
                        wrapMode: Text.WordWrap
                    }
                    Text{
                        id: m_damimms
                        visible: (monster!=null?monster.damimms!="":false)
                        width: rightCol.width-21
                        text: (monster!=null?"<b>Damage Immunities</b> "+monster.damimms:"")
                        color: "#2a0700"
                        wrapMode: Text.WordWrap
                    }
                    Text{
                        id: m_conimms
                        visible: (monster!=null?monster.conimms!="":false)
                        width: rightCol.width-21
                        text: (monster!=null?"<b>Condition Immunities</b> "+monster.conimms:"")
                        color: "#2a0700"
                        wrapMode: Text.WordWrap
                    }
                    Text{
                        id: m_senses
                        width: rightCol.width-21
                        text: (monster!=null?"<b>Senses</b> "+monster.senses:"")
                        color: "#2a0700"
                        wrapMode: Text.WordWrap
                    }
                    Text{
                        id: m_langs
                        width: rightCol.width-21
                        text: (monster!=null?"<b>Languages</b> "+monster.langs:"")
                        color: "#2a0700"
                        wrapMode: Text.WordWrap
                    }
                    Text{
                        id: m_challenge
                        text: (monster!=null?"<b>Challenge</b> "+monster.challenge:"")
                        color: "#2a0700"
                    }
                }
                Image{
                    id: bar4
                    anchors.top: dynamicCol.bottom
                    anchors.topMargin: 8
                    source: "img/monsterDivider1.png"
                    visible: monster!=null
                }
                ListModel{id: blank}
                ColumnLayout{
                    id: variableCol
                    anchors.top: bar4.bottom
                    anchors.topMargin: 10
                    Column{
                        id: traitCol
                        spacing: 10
                        Repeater{
                            id: traitList
                            model: (monster!=null?monster.traits:blank)
                            Text{
                                text: modelData
                                width: rightCol.width-21
                                wrapMode: Text.WordWrap
                            }
                        }
                    }
                    RowLayout{
                        id: actionText
                        visible: false
                        anchors.top: traitCol.bottom
                        anchors.topMargin: 8
                        Text{
                            id: atextA
                            color: "#2a0700"
                            text: "A"
                            font.family: "Beleren"
                            font.pointSize: 16
                        }
                        Text{
                            color: "#2a0700"
                            text: "CTIONS"
                            font.family: "Beleren"
                            font.pointSize: 11
                            anchors.left: atextA.right
                            anchors.leftMargin: -2
                            anchors.bottom: atextA.bottom
                            anchors.bottomMargin: 2
                        }
                    }
                    Image{
                        id: bar5
                        visible: false
                        anchors.top: actionText.bottom
                        anchors.topMargin: -4
                        source: "img/monsterDivider2.png"
                    }
                    Column{
                        id: actionCol
                        anchors.top: bar5.bottom
                        anchors.topMargin: 4
                        spacing: 10
                        Repeater{
                            id: actionList
                            model: (monster!=null?monster.actions:blank)
                            Text{
                                text: modelData
                                width: rightCol.width-21
                                wrapMode: Text.WordWrap
                            }
                            onModelChanged: {
                                if(count<1){
                                    actionText.visible = false
                                    bar5.visible = false
                                } else{
                                    actionText.visible = true
                                    bar5.visible = true
                                }
                            }
                        }
                    }
                    RowLayout{
                        id: reactionText
                        visible: false
                        anchors.top: actionCol.bottom
                        anchors.topMargin: 8
                        Text{
                            id: rTextR
                            color: "#2a0700"
                            text: "R"
                            font.family: "Beleren"
                            font.pointSize: 16
                        }
                        Text{
                            color: "#2a0700"
                            text: "EACTIONS"
                            font.family: "Beleren"
                            font.pointSize: 11
                            anchors.left: rTextR.right
                            anchors.leftMargin: -2
                            anchors.bottom: rTextR.bottom
                            anchors.bottomMargin: 2
                        }
                    }
                    Image{
                        id: bar6
                        visible: false
                        anchors.top: reactionText.bottom
                        anchors.topMargin: -4
                        source: "img/monsterDivider2.png"
                    }
                    Column{
                        id: reactionCol
                        anchors.top: bar6.bottom
                        anchors.topMargin: 4
                        spacing: 10
                        Repeater{
                            id: reactionList
                            model: (monster!=null?monster.reactions:blank)
                            Text{
                                text: modelData
                                width: rightCol.width-21
                                wrapMode: Text.WordWrap
                            }
                            onModelChanged: {
                                if(count<1){
                                    reactionText.visible = false
                                    bar6.visible = false
                                } else{
                                    reactionText.visible = true
                                    bar6.visible = true
                                }
                            }
                        }
                    }
                    RowLayout{
                        id: lActionText
                        visible: false
                        Text{
                            id: ltext1
                            color: "#2a0700"
                            text: "L"
                            font.family: "Beleren"
                            font.pointSize: 16
                        }
                        Text{
                            id: ltext2
                            color: "#2a0700"
                            text: "EGENDARY"
                            font.family: "Beleren"
                            font.pointSize: 11
                            anchors.left: ltext1.right
                            anchors.leftMargin: -2
                            anchors.bottom: ltext1.bottom
                            anchors.bottomMargin: 2
                        }
                        Text{
                            id: ltext3
                            color: "#2a0700"
                            text: "A"
                            font.family: "Beleren"
                            font.pointSize: 16
                            anchors.left: ltext2.right
                            anchors.leftMargin: 4
                            anchors.bottom: ltext2.bottom
                            anchors.bottomMargin: -2
                        }
                        Text{
                            color: "#2a0700"
                            text: "CTIONS"
                            font.family: "Beleren"
                            font.pointSize: 11
                            anchors.left: ltext3.right
                            anchors.leftMargin: -2
                            anchors.bottom: ltext3.bottom
                            anchors.bottomMargin: 2
                        }
                    }
                    Image{
                        id: bar7
                        visible: false
                        anchors.top: lActionText.bottom
                        anchors.topMargin: -4
                        source: "img/monsterDivider2.png"
                    }
                    Column{
                        id: lActionCol
                        anchors.top: bar7.bottom
                        anchors.topMargin: 2
                        spacing: 4
                        Repeater{
                            id: lActionList
                            model: (monster!=null?monster.lActions:blank)
                            Text{
                                text: modelData
                                width: rightCol.width-21
                                wrapMode: Text.WordWrap
                            }
                            onModelChanged: {
                                if(count<1){
                                    lActionText.visible = false
                                    bar7.visible = false
                                    lActionCol.visible = false
                                } else{
                                    lActionText.visible = true
                                    bar7.visible = true
                                    lActionCol.visible = true
                                }
                            }
                        }
                    }
                }
                Rectangle{
                    width: parent.fillWidth
                    height: 30
                }
            }
        }
    }
    Image{
        id: bottomBar
        anchors.bottom: scrollReminder.top
        source: "img/monsterBar2.png"
    }
    Text{
        id: scrollReminder
        text: "(Scroll to see the rest of the entry)"
        font.italic: true
        anchors.right: monsterViewer.right
        anchors.bottom: monsterViewer.bottom
        visible: variableCol.height+320 > monsterViewer.height
        //visible: true
    }
}
