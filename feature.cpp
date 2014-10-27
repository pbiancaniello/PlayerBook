#include "feature.h"

Feature::Feature(QObject *parent) :
    QObject(parent){
    name = "TESTING";
    bonuses.append("addspell|mage hand");
}

QString Feature::getSource() const{
    return source;
}
void Feature::setSource(QString newSource){
    if(source!=newSource){
        source = newSource;
        emit sourceChanged();
    }
}

QString Feature::getName() const{
    return name;
}
void Feature::setName(QString newName){
    if(name!=newName){
        name = newName;
        emit nameChanged();
    }
}

QStringList Feature::getDesc() const{
    return desc;
}
bool Feature::addToDesc(QString line){
    if(!desc.contains(line)){
        desc.append(line);
        emit descChanged();
        return true;
    }
    return false;
}

QStringList Feature::getBonuses() const{
    return bonuses;
}
bool Feature::addToBonuses(QString bonus){
    /*if(!bonuses.contains(bonus)){
        bonuses.append(bonus);
        emit bonusesChanged();
        return true;
    }
    return false;*/
    bonuses.append(bonus);
    emit bonusesChanged();
    return true;
}

QMap<QString,QString> Feature::getChoiceMap() const{
    return choiceMap;
}
QStringList Feature::getChoices() const{
    return choiceMap.keys();
}
QStringList Feature::getEffects() const{
    return choiceMap.values();
}
bool Feature::addToChoiceMap(QString choice, QString effect){
    choiceMap.insert(choice, effect);
    emit choicesChanged();
    emit effectsChanged();
    return true; //for now
}
QString Feature::getEffect(QString choice) const{
    return choiceMap[choice];
}
