#include "monster.h"

Monster::Monster(QObject *parent) :
    QObject(parent){}

QString Monster::getSource() const{
    return source;
}

QString Monster::objectName(){
    return name;
}

void Monster::setSource(QString newSource){
    if(source!=newSource){
        source = newSource;
        emit sourceChanged();
    }
}

QString Monster::getName() const{
    return name;
}

void Monster::setName(QString newName){
    if(name!=newName){
        name = newName;
        emit nameChanged();
    }
}

QString Monster::getSize() const{
    return size;
}

void Monster::setSize(QString newSize){
    if(size!=newSize){
        size = newSize;
        emit sizeChanged();
    }
}

QString Monster::getType() const{
    return type;
}

void Monster::setType(QString newType){
    if(type!=newType){
        type = newType;
        emit typeChanged();
    }
}

QString Monster::getAlignment() const{
    return alignment;
}

void Monster::setAlignment(QString newAlignment){
    if(alignment!=newAlignment){
        alignment = newAlignment;
        emit alignmentChanged();
    }
}

QString Monster::getAC() const{
    return AC;
}

void Monster::setAC(QString newAC){
    if(AC!=newAC){
        AC = newAC;
        emit ACChanged();
    }
}

QString Monster::getHP() const{
    return HP;
}

void Monster::setHP(QString newHP){
    if(HP!=newHP){
        HP = newHP;
        emit HPChanged();
    }
}

QString Monster::getSpeed() const{
    return speed;
}

void Monster::setSpeed(QString newSpeed){
    if(speed!=newSpeed){
        speed = newSpeed;
        emit speedChanged();
    }
}

QList<QString> Monster::getScores() const{
    return scores;
}

void Monster::setScores(QList<QString> newScores){
    if(scores!=newScores){
        scores = newScores;
        emit scoresChanged();
    }
}

QString Monster::getSThrows() const{
    return sThrows;
}

void Monster::setSThrows(QString newSThrows){
    if(sThrows!=newSThrows){
        sThrows = newSThrows;
        emit sThrowsChanged();
    }
}

QString Monster::getSkills() const{
    return skills;
}

void Monster::setSkills(QString newSkills){
    if(skills!=newSkills){
        skills = newSkills;
        emit skillsChanged();
    }
}

QString Monster::getDamVulns() const{
    return damvulns;
}

void Monster::setDamVulns(QString newDamVulns){
    if(damvulns!=newDamVulns){
        damvulns = newDamVulns;
        emit damVulnsChanged();
    }
}

QString Monster::getDamRes() const{
    return damres;
}

void Monster::setDamRes(QString newDamRes){
    if(damres!=newDamRes){
        damres = newDamRes;
        emit damResChanged();
    }
}

QString Monster::getDamImms() const{
    return damimms;
}

void Monster::setDamImms(QString newDamImms){
    if(damimms!=newDamImms){
        damimms = newDamImms;
        emit damImmsChanged();
    }
}

QString Monster::getConImms() const{
    return conimms;
}

void Monster::setConImms(QString newConImms){
    if(conimms!=newConImms){
        conimms = newConImms;
        emit conImmsChanged();
    }
}

QString Monster::getSenses() const{
    return senses;
}

void Monster::setSenses(QString getSenses){
    if(senses!=getSenses){
        senses = getSenses;
        emit sensesChanged();
    }
}

QString Monster::getLangs() const{
    return langs;
}

void Monster::setLangs(QString newLangs){
    if(langs!=newLangs){
        langs = newLangs;
        emit langsChanged();
    }
}

QString Monster::getChallenge() const{
    return challenge;
}

void Monster::setChallenge(QString newChallenge){
    if(challenge!=newChallenge){
        challenge = newChallenge;
        emit challengeChanged();
    }
}

QStringList Monster::getTraits() const{
    return traits;
}

void Monster::addTrait(QString trait){
    traits.append(trait);
    emit traitsChanged();
}

QStringList Monster::getSpells() const{
    return spells;
}

void Monster::addSpell(QString spell){
    spells.append(spell);
    emit spellsChanged();
}

QStringList Monster::getActions() const{
    return actions;
}

void Monster::addAction(QString action){
    actions.append(action);
    emit actionsChanged();
}

QStringList Monster::getReactions() const{
    return reactions;
}
void Monster::addReaction(QString reaction){
    reactions.append(reaction);
    emit reactionsChanged();
}

QStringList Monster::getLActions() const{
    return lActions;
}

void Monster::addLAction(QString lAction){
    lActions.append(lAction);
    emit lActionsChanged();
}
