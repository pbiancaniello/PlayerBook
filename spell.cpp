#include "spell.h"

Spell::Spell(QObject *parent) :
    QObject(parent){}

QString Spell::objectName() const{
    return name;
}

QString Spell::getSource() const{
    return source;
}
bool Spell::setSource(QString newSource){
    if(source!=newSource){
        source = newSource;
        emit sourceChanged();
        return true;
    }
    return false;
}

QString Spell::getName() const{
    return name;
}
bool Spell::setName(QString newName){
    if(name!=newName){
        name = newName;
        emit nameChanged();
        return true;
    }
    return false;
}

QString Spell::getLevel() const{
    return level;
}
bool Spell::setLevel(QString newLevel){
    if(level!=newLevel){
        level = newLevel;
        emit levelChanged();
        return true;
    }
    return false;
}

QString Spell::getSchool() const{
    return school;
}
bool Spell::setSchool(QString newSchool){
    if(school!=newSchool){
        school = newSchool;
        emit schoolChanged();
        return true;
    }
    return false;
}

QString Spell::getCastTime() const{
    return castTime;
}
bool Spell::setCastTime(QString newCastTime){
    if(castTime!=newCastTime){
        castTime = newCastTime;
        emit castTimeChanged();
        return true;
    }
    return false;
}

QString Spell::getRange() const{
    return range;
}
bool Spell::setRange(QString newRange){
    if(range!=newRange){
        range = newRange;
        emit rangeChanged();
        return true;
    }
    return false;
}

QString Spell::getComps() const{
    return comps;
}
bool Spell::setComps(QString newComps){
    if(comps!=newComps){
        comps = newComps;
        emit compsChanged();
        return true;
    }
    return false;
}

QString Spell::getDuration() const{
    return duration;
}
bool Spell::setDuration(QString newDuration){
    if(duration!=newDuration){
        duration = newDuration;
        emit durationChanged();
        return true;
    }
    return false;
}

QStringList Spell::getDesc() const{
    return desc;
}
bool Spell::addToDesc(QString line){
    if(!desc.contains(line)){
        desc.append(line);
        emit descChanged();
        return true;
    }
    return false;
}
