#include "contentlist.h"
#include <iostream>

ContentList::ContentList(QObject *parent) :
    QObject(parent){}

QQmlListProperty<QObject> ContentList::getList(){
    return QQmlListProperty<QObject>(this, list);
}

bool ContentList::addContent(QObject* c){
    if(!contains(c)){
        list.append(c);
        emit listChanged();
        emit contentAdded();
        return true;
    }
    return false;
    /*list.append(c);
    emit listChanged();
    return true;*/
}

QObject* ContentList::get(int i){
    return list.at(i);
}

bool ContentList::contains(QObject* o){
    return list.contains(o);
}

int ContentList::containsMonster(QString s){
    for(int i=0; i<list.length(); i++){
        Monster* monster = qobject_cast<Monster*>(list[i]);
        if(monster->getName().toLower()==s.toLower()){
            return i;
        }
    }
    return -1;
}

/*int ContentList::containsRace(QString s){
    for(int i=0; i<list.length(); i++){
        Race* race = qobject_cast<Race*>(list[i]);
        if(race->getName().toLower()==s.toLower()){
            return i;
        }
    }
    return -1;
}*/

int ContentList::containsSpell(QString s){
    for(int i=0; i<list.length(); i++){
        Spell* spell = qobject_cast<Spell*>(list[i]);
        if(spell->getName().toLower()==s.toLower()){
            return i;
        }
    }
    return -1;
}

void ContentList::remove(int i){
    list.removeAt(i);
    emit listChanged();
}

void ContentList::clear(){
    if(list.length()>0){
        list.clear();
        emit listChanged();
    }
}

int ContentList::length(){
    return list.length();
}

void ContentList::sortSpells(QString attribute){
    if(attribute.toLower()=="name"){
        QMap<QString, QObject*> temp;
        foreach(QObject* q, list){
            Spell* s = qobject_cast<Spell*>(q);
            temp.insert(s->getName(),s);
        }
        list = temp.values();
    } else if(attribute.toLower()=="school"){
        QMap< QString, QList<Spell*> > temp;
        foreach(QObject* q, list){
            Spell* s = qobject_cast<Spell*>(q);
            temp[s->getSchool()].append(s);
        }
        QList<QObject*> sorted;
        foreach(QString qs, temp.keys()){
            QMap<QString, QObject*> temp2;
            foreach(QObject* q, temp[qs]){
                Spell* s = qobject_cast<Spell*>(q);
                temp2.insert(s->getName(),s);
            }
            sorted.append(temp2.values());
        }
        list = sorted;
    } else if(attribute.toLower()=="level"){
        QMap< QString, QList<Spell*> > temp;
        foreach(QObject* q, list){
            Spell* s = qobject_cast<Spell*>(q);
            temp[s->getLevel()].append(s);
        }
        QList<QObject*> sorted;
        foreach(QString qs, temp.keys()){
            QMap<QString, QObject*> temp2;
            foreach(QObject* q, temp[qs]){
                Spell* s = qobject_cast<Spell*>(q);
                temp2.insert(s->getName(),s);
            }
            sorted.append(temp2.values());
        }
        list = sorted;
    }

}
bool spellNameComparison(const Spell* s1, const Spell* s2){
    return s1->getName() < s2->getName();
}
bool spellSchoolComparison(const Spell &s1, const Spell &s2){
    return s1.getSchool() < s2.getSchool();
}
bool spellLevelComparison(const Spell &s1, const Spell &s2){
    return s1.getLevel() < s2.getLevel();
}
