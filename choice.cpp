#include "choice.h"

Choice::Choice(QObject *parent) :
    QObject(parent)
{
    choices.insert("<Make your choice>","");
    sel = 0;
}

QString Choice::getDesc() const{
    return desc;
}
bool Choice::setDesc(QString newDesc){
    if(desc!=newDesc){
        desc = newDesc;
        emit descChanged();
        return true;
    }
    return false;
}

void Choice::add(QString option, QString effect){
    choices.insert(option, effect);
}

QStringList Choice::getOptions() const{
    return choices.keys();
}
QStringList Choice::getEffects() const{
    return choices.values();
}

int Choice::getSel() const{
    return sel;
}
bool Choice::setSel(int newSel){
    if(sel!=newSel){
        sel = newSel;
        emit selChanged();
        return true;
    }
    return false;
}
