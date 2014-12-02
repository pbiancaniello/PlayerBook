#include "castingpage.h"

CastingPage::CastingPage(QObject *parent) :
    QObject(parent){
    //stat = "";
    known = new ContentList();
    prepared = new ContentList();
}

QString CastingPage::getClass() const{
    return c_class;
}
bool CastingPage::setClass(QString c){
    if(c_class!=c){
        c_class = c;
        emit classChanged();
        return true;
    }
    return false;
}

QString CastingPage::getSubclass() const{
    return c_subclass;
}
bool CastingPage::setSubclass(QString s){
    if(c_subclass!=s){
        c_subclass = s;
        emit subclassChanged();
        return true;
    }
    return false;
}

QString CastingPage::getFormula() const{
    return formula;
}
int CastingPage::numPrep(QString str, int classLVL, QList<int> charMods){
    if(charMods.size()!=6){
        return -1;
    }
    if(str.contains("-")){
        QStringList qsl = str.split("-");
        int total = numPrep(qsl[0], classLVL, charMods);
        for(int i=1; i<qsl.length(); i++){
            total-=numPrep(qsl[i], classLVL, charMods);
        }
        return total;
    }
    if(str.contains("+")){
        QStringList qsl = str.split("+");
        int total = 0;
        for(int i=0; i<qsl.length(); i++){
            total+=numPrep(qsl[i], classLVL, charMods);
        }
        return total;
    }
    if(str.contains("/")){
        QStringList qsl = str.split("/");
        int total = numPrep(qsl[0], classLVL, charMods);
        for(int i=1; i<qsl.length(); i++){
            total/=numPrep(qsl[i], classLVL, charMods);
        }
        return total;
    }
    if(str.contains("*")){
        QStringList qsl = str.split("*");
        int total = 1;
        for(int i=0; i<qsl.length(); i++){
            total*=numPrep(qsl[i], classLVL, charMods);
        }
        return total;
    }
    if(str=="strmod"){
        return charMods[0];
    } else if(str.toLower()=="dexmod"){
        return charMods[1];
    } else if(str.toLower()=="conmod"){
        return charMods[2];
    } else if(str.toLower()=="intmod"){
        return charMods[3];
    } else if(str.toLower()=="wismod"){
        return charMods[4];
    } else if(str.toLower()=="chamod"){
        return charMods[5];
    } else if(str.toLower()=="classlevel"){
        return classLVL;
    } else{
        return str.toInt();
    }
}
bool CastingPage::setFormula(QString f){
    if(formula!=f){
        formula = f;
        emit formulaChanged();
        return true;
    }
    return false;
}

QString CastingPage::getStat() const{
    return stat;
}
bool CastingPage::setStat(QString s){
    if(stat!=s){
        stat = s;
        emit statChanged();
        return true;
    }
    return false;
}

int CastingPage::getWeight() const{
    return weight;
}
bool CastingPage::setWeight(int w){
    if(weight!=w){
        weight=w;
        emit weightChanged();
        return true;
    }
    return false;
}

ContentList* CastingPage::getKnown(){
    return known;
}

ContentList* CastingPage::getPrepared(){
    return prepared;
}
