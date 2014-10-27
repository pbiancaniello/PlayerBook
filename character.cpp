#include "character.h"

Character::Character(QObject *parent) :
    QObject(parent)
{
    name = "Jace";
    race = "Human";
    subRace = "";
    charClass = "Wizard";
    spells = new ContentList();
    features = new ContentList();
}

void Character::setDatabase(Database* d){
    database = d;
}

QString Character::getName(){
    return name;
}
void Character::setName(QString newName){
    name = newName;
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
                spells->addContent(database->getSpells()->get(i));
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
    return effect.isNull();
    //return true;
}

ContentList* Character::getFeatures() const{
    return features;
}

ContentList* Character::getSpells() const{
    return spells;
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

