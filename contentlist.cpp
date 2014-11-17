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
    int length = list.length();
    for(int i=0; i<length; i++){
        list.removeLast();
    }
    emit listChanged();
}

int ContentList::length(){
    return list.length();
}

/*bool ContentList::contentLessThan(const QObject* o1, const QObject* o2){
    return o1->objectName() < o2->objectName();
}

void ContentList::sort(){
    qSort(list.begin(), list.end(), contentLessThan);
}*/
