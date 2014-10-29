#include "feature.h"

Feature::Feature(QObject *parent) :
    QObject(parent){
    choices = new ContentList();
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

ContentList* Feature::getChoices() const{
    return choices;
}
void Feature::addToChoices(Choice* choice){
    choices->addContent(choice);
}
