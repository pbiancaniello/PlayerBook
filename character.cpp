#include "character.h"

Character::Character(QObject *parent) :
    QObject(parent)
{
    name = "Jace Beleren";
    race = "Human";
    subrace = "";
    className = "Wizard";
    level = 1;
    levels.insert("Wizard",1);
    spells = new ContentList();
    extraSpells = new ContentList();
    features = new ContentList();
    for(int i=0; i<6; i++){
        scores.append(0);
    }
}

void Character::setDatabase(Database* d){
    database = d;
}

QString Character::getName() const{
    return name;
}
void Character::setName(QString newName){
    name = newName;
    emit nameChanged();
}

QString Character::getRace() const{
    return race;
}
void Character::setRace(QString newRace){
    race = newRace;
    emit raceChanged();
}
void Character::setRace(Race* r){
    race = r->getName();
    size = r->getSize();
    speed = r->getSpeed();
    for(int i=0; i<r->getLangs().length(); i++){
        langs.append(r->getLangs().at(i));
    }
    for(int i=0; i<6; i++){
        scores[i] += r->getScores()[i];
    }
    for(int i=0; i<r->getFeatures()->length(); i++){
        addFeature(qobject_cast<Feature*>(r->getFeatures()->get(i)));
    }
    emit raceChanged();
}

QString Character::getSubrace() const{
    return subrace;
}
void Character::setSubrace(QString newSubrace){
    subrace = newSubrace;
    emit subraceChanged();
}
void Character::setSubrace(Race* r){
    subrace = r->getName();
    for(int i=0; i<6; i++){
        scores[i] += r->getScores()[i];
    }
    for(int i=0; i<r->getFeatures()->length(); i++){
        addFeature(qobject_cast<Feature*>(r->getFeatures()->get(i)));
    }
    emit subraceChanged();
}

QString Character::getClassName() const{
    return className;
}
void Character::setClassName(QString newClassName){
    className = newClassName;
    emit classNameChanged();
}
void Character::generateClassName(){
    //className = newClassName;
    QString n;
    foreach(QString c,levels.keys()){
        n += c + " " + levels[c];
    }
    className = n;
    emit classNameChanged();
}

QString Character::getAlignment() const{
    return alignment;
}
void Character::setAlignment(QString newAlignment){
    alignment = newAlignment;
    emit alignmentChanged();
}

QString Character::getBackground() const{
    return background;
}
void Character::setBackground(QString newBackground){
    background = newBackground;
    emit backgroundChanged();
}

int Character::getLevel() const{
    return level;
}
void Character::setLevel(int newLevel){
    level = newLevel;
    emit levelChanged();
}

QList<int> Character::getScores() const{
    return scores;
}
void Character::addStr(int s){
    scores[0] += s;
}
void Character::addDex(int d){
    scores[1] += d;
}
void Character::addCon(int c){
    scores[2] += c;
}
void Character::addInt(int i){
    scores[3] += i;
}
void Character::addWis(int w){
    scores[4] += w;
}
void Character::addCha(int c){
    scores[5] += c;
}

int Character::getClassLevel(QString className){
    if(levels.keys().contains(className)){
        return levels.value(className);
    }
    return -1;
}

void Character::setClassLevel(QString className, int level){
    if(levels.keys().contains(className)){
        levels[className] = level;
    } else{
        levels.insert(className,level);
    }
}

void Character::addFeature(Feature* feature){
    features->addContent(feature);
    QStringList bonuses = feature->getBonuses();
    //std::cerr << "in addFeature";
    for(int i=0; i<bonuses.length(); i++){
        addEffect(bonuses.at(i));
    }
}

bool Character::addEffect(QString effect){
    QStringList params = effect.toLower().split("|");
    if(params.size()==1){
        return true;
    } else if(params.size()==2){
        if(params[0]=="addspell"){
            int i = database->getSpells()->containsSpell(params[1]);
            if(i>=0){
                //spells->addContent(database->getSpells()->get(i));
                extraSpells->addContent(database->getSpells()->get(i));
                return true;
            }
            return false;
        }
        return false;
    }
    else if(params.size()==3){
        return true;
    } else {
        return false;
    }
}

bool Character::removeEffect(QString effect){
    QStringList params = effect.toLower().split("|");
    if(params.size()==1){
        return true;
    } else if(params.size()==2){
        if(params[0]=="addspell"){
            int i = extraSpells->containsSpell(params[1]);
            if(i>=0){
                extraSpells->remove(extraSpells->containsSpell(params[1]));
                return true;
            }
            return false;
        }
        return false;
    }
    else if(params.size()==3){
        return true;
    } else {
        return false;
    }
}

ContentList* Character::getFeatures() const{
    return features;
}

ContentList* Character::getSpells() const{
    return spells;
}

ContentList* Character::getExtraSpells() const{
    return extraSpells;
}

void Character::saveCharacter(){
    QFile file("file.txt");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    //out << QString("the answer is");   // serialize a string
    //out << (qint32)42;        // serialize an integer
    //out << getSpells()->list;

}

void Character::readCharacter() {
    QFile* file = new QFile(":/example.xml");
        /* If we can't open it, let's show an error message. */
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
            name = "error";
    }
        /* QXmlStreamReader takes any QIODevice. */
    QXmlStreamReader xml(file);
        /* We'll parse the XML until we reach end of it.*/
    while (!xml.atEnd()) {
        //name = t.readLine();
        //name = "Yea";
        //xml.readNext();
        //name = xml.name().toString();
        //break;
        //QXmlStreamReader::TokenType token = xml.readNext();
        if(xml.readNext() == QXmlStreamReader::StartDocument) {
            //name = "cool";
            if(xml.readNext() == QXmlStreamReader::StartElement) {
                //name = xml.name().toString();
                xml.readNext();
                xml.readNext();
                if(xml.name().toString()=="name"){
                    name = xml.readElementText();
                    break;
                }
            }
        } else{
            name = "no";
            break;
        }
    }
    /*while(!xml.atEnd()){
            QXmlStreamReader::TokenType token = xml.readNext();
                    // If token is just StartDocument, we'll go to next.
                    if(token == QXmlStreamReader::StartDocument) {
                        continue;
                    }
                    // If token is StartElement, we'll see if we can read it.
                    if(token == QXmlStreamReader::StartElement) {
                        // If it's named character, we'll go to the next.
                        if(xml.name() == "character") {
                            //continue;
                            QXmlStreamAttributes attributes = xml.attributes();
                            name = attributes.value("name").toString();
                        }
                        // If it's named person, we'll dig the information from there.
                    }
        }*/
}

