#include "race.h"

Race::Race(QObject *parent) :
    QObject(parent){
    choices = new ContentList();
    features = new ContentList();
    subraces = new ContentList();
    for(int i=0; i<6; i++){
        scores.append(0);
    }
}

QString Race::getSource() const{
    return source;
}
bool Race::setSource(QString s){
    if(source!=s){
        source = s;
        emit sourceChanged();
        return true;
    }
    return false;
}

QString Race::getName() const{
    return name;
}
bool Race::setName(QString n){
    if(name!=n){
        name = n;
        emit nameChanged();
        return true;
    }
    return false;
}

QStringList Race::getDesc() const{
    return desc;
}
void Race::addToDesc(QString s){
    desc.append(s);
    emit descChanged();
}

QString Race::getSize() const{
    return size;
}
bool Race::setSize(QString s){
    if(size!=s){
        size = s;
        emit sizeChanged();
        return true;
    }
    return false;
}

QString Race::getSpeed() const{
    return speed;
}
bool Race::setSpeed(QString s){
    if(speed!=s){
        speed = s;
        emit speedChanged();
        return true;
    }
    return false;
}

QStringList Race::getLangs() const{
    return langs;
}
void Race::addToLangs(QString l){
    langs.append(l);
    emit langsChanged();
}

ContentList* Race::getChoices() const{
    return choices;
}

QList<int> Race::getScores() const{
    return scores;
}

void Race::setScore(int i, int s){
    scores[i]=s;
}

ContentList* Race::getFeatures() const{
    return features;
}

ContentList* Race::getSubraces() const{
    return subraces;
}
