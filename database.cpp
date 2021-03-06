#include "database.h"

Database::Database(QObject *parent) :
    QObject(parent){
    monsters = new ContentList();
    //races = new ContentList();
    //races = new QList<Race*>();
    spells = new ContentList();
    tagType = "temp";
    buildMCSpellSlots();
}

ContentList* Database::getMonsters() const{
    return monsters;
}

/*ContentList* Database::getRaces() const{
    return races;
}*/
QQmlListProperty<Race> Database::getRaces(){
    return QQmlListProperty<Race>(this, races);
}
Race* Database::getRace(int i){
    return races.at(i);
}

ContentList* Database::getSpells() const{
    return spells;
}

QStringList Database::getSpellList() const{
    return spellList;
}

QStringList Database::getRitualList() const{
    return ritualList;
}

QStringList Database::getLangList() const{
    return langList;
}

bool Database::containsClass(QString c) const{
    return classList.contains(c);
}

QList<int> Database::getMCSpellSlots(int casterLevel) const{
    return MCSpellSlots[casterLevel];
}
int Database::getMCSpellSlots(int casterLevel, int slotLevel) const{
    return  MCSpellSlots[casterLevel][slotLevel];
}

QStringList Database::getErrorLog() const{
    return errorLog;
}

void Database::addError(QString error){
    errorLog.append(error);
    emit errorLogChanged();
}

bool Database::loopCheck(QString currentTag){
    if(currentTag==tagType){
        counter++;
        if(counter>=6){
            tagType="";
            counter=0;
            return false;
        }
    }
    return true;
}

void Database::buildDatabase(){
    QDir dir(":/libraries");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QStringList list = dir.entryList();
    for(int i=0; i<list.length(); i++){
        //addError(list.at(i));
        parseFile(dir.path()+"/"+list.at(i));
        //addError(dir.path()+"/"+list.at(i));
    }
}

bool Database::parseFile(QString filename){
    QFile* file = new QFile(filename); // If we can't open it, show an error message.
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        addError("Parsing error: Couldn't open "+filename);
        return false;
    }
    QXmlStreamReader newXml(file);
    xml = &newXml;
    if (!xml->atEnd()){ //We'll parse the XML until we reach end of it.
        if(xml->readNext() == QXmlStreamReader::StartDocument) { //1st line
            if(xml->readNext() == QXmlStreamReader::StartElement) { //source
                while(xml->name().toString()!="name"){
                    xml->readNext();
                    if(xml->tokenType()==QXmlStreamReader::EndDocument){
                        std::cerr << "Unexpected end of document";
                        return -1;
                    }
                }
                QString source = xml->readElementText();
                //std::cerr << source.toStdString() << "\n";
                while(xml->name().toString()!="content"){
                    xml->readNext();
                    if(xml->tokenType()==QXmlStreamReader::EndDocument){
                        std::cerr << "Unexpected end of document";
                        break;
                    }
                }
                xml->readNext(); // We should be at the first content item now
                while(xml->tokenType()!=QXmlStreamReader::EndDocument){
                    if(xml->tokenType()!=QXmlStreamReader::EndElement){
                        QString type = xml->name().toString();
                        if(xml->hasError()){
                            addError("Parsing of source '"+source+"' was interrupted by an error");
                            return false;
                        }
                        if(type=="feat"){
                            std::cerr << "FEATTTTTTT\n";
                        }
                        if(type=="language"){ //Now at open language tag
                            QString lang = xml->readElementText();
                            if(langList.contains(lang)){
                                addError("Duplicate language entry in "+source+": "+lang);

                            } else{
                                langList.append(lang);
                            }
                        }
                        if(type=="monster"){ //Now at open monster tag
                            Monster* m = new Monster();
                            m->setSource(source);
                            if(buildMonster(m)){
                                monsters->addContent(m);
                                emit monstersChanged();
                            }
                        }
                        if(type=="race"){ //Now at open race tag
                            Race* r = new Race();
                            r->setSource(source);
                            if(buildRace(r)){
                                races.append(r);
                                emit racesChanged();
                            }
                        }
                        if(type=="spell"){ //Now at open spell tag
                            Spell* s = new Spell();
                            s->setSource(source);
                            if(buildSpell(s)){
                                spells->addContent(s);
                                emit spellsChanged();
                                spellList.append(s->getName().toLower());
                                emit spellListChanged();
                            } else{
                                std::cerr << "Unable to build spell\n";
                            }
                        }
                        if(type=="subrace"){ //Now at open subrace tag
                            Race* r = new Race();
                            r->setSource(source);
                            if(buildSubrace(r)){
                                //races.append(r);
                                //emit racesChanged();
                                std::cerr << "Subrace " << r->getName().toStdString() << " parsed.\n";
                            }
                        }
                    }
                    xml->readNext();
                }
            }
        } else{
            std::cerr << "XML version tag not found";
            //break;
        }
    }
}

bool Database::buildMonster(Monster* m){
    QString error = "In source "+m->getSource()+" while parsing a monster: ";
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="name"){ //should be at name
        m->setName(xml->readElementText());
        error += m->getName()+" has ";
        if(monsters->containsMonster(m->getName().toLower())>=0){
            addError(error+" a duplicate entry");
            return false;
        }
    } else{
        addError(error+"an improper tag order and/or a missing name tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="size"){ //should be at size
        m->setSize(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing size tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="type"){ //should be at type
        m->setType(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing type tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="alignment"){ //should be at alignment
        m->setAlignment(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing alignment tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="ac"){ //should be at ac
        m->setAC(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing ac tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="hp"){ //should be at hp
        m->setHP(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing hp tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="speed"){ //should be at speed
        m->setSpeed(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing speed tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="scores"){ //should be at scores
        QList<QString> scores = xml->readElementText().split(" ");
        if(scores.length()!=6){
            addError(error+"an incorrect number of ability scores");
            return false;
        }
        m->setScores(scores);
    } else{
        addError(error+"an improper tag order and/or a missing scores tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="sthrows"){ //may be at sthrows
        m->setSThrows(xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="skills"){ //may be at sthrows
        m->setSkills(xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="damvulns"){ //may be at damvulns
        m->setDamVulns(xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="damres"){ //may be at damres
        m->setDamRes(xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="damimms"){ //may be at damimms
        m->setDamImms(xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="conimms"){ //may be at conimms
        m->setConImms(xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="senses"){ //should be at senses
        m->setSenses(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing senses tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="langs"){ //should be at langs
        m->setLangs(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing langs tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="challenge"){ //should be at challenge
        m->setChallenge(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing challenge tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="traits"){ //may be at traits
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="traits"){ //loop until traits end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a trait end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="trait"){ //we are at a basic trait
                m->addTrait(xml->readElementText());
            } else if(xml->name().toString()=="spellcasting"){
                xml->readNext();
                xml->readNext();
                if(xml->name().toString()=="desc"){
                    m->addTrait(xml->readElementText());
                    xml->readNext();
                    xml->readNext();
                    if(xml->name().toString()=="spells"){
                        QStringList spells = xml->readElementText().toLower().split(",");
                        for(int i=1; i<spells.length(); i++){
                            QString ts = spells[i].trimmed();
                            m->addSpell(ts);
                        }
                        xml->readNext();
                        xml->readNext();
                    } else{
                        addError(error+"a misformatted spellcasting trait");
                        return false;
                    }
                } else{
                    addError(error+"a misformatted spellcasting trait");
                    return false;
                }
            } else{
                addError(error+"a misformatted trait");
                return false;
            }
            xml->readNext();
            xml->readNext();
        }
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="actions"){ //may be at actions
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="actions"){ //loop until actions end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing an action end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="action"){ //we are at an action
                m->addAction(xml->readElementText());
            } else{
                addError(error+"a misformatted action section");
                return false;
            }
            xml->readNext();
            xml->readNext();
        }
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="reactions"){ //may be at reactions
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="reactions"){ //loop until reactions end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a reaction end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="reaction"){ //we are at a reaction
                m->addReaction(xml->readElementText());
            } else{
                addError(error+"a misformatted reaction section");
                return false;
            }
            xml->readNext();
            xml->readNext();
        }
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="lactions"){ //may be at legendary actions
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="lactions"){ //loop until laction end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a laction end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="laction"){ //at a laction
                m->addLAction(xml->readElementText());
            } else{
                addError(error+"a misformatted legendary action section");
                return false;
            }
            xml->readNext();
            xml->readNext();
        }
    }
    return true;
}

bool Database::buildRace(Race* r){
    QString error = "In source "+r->getSource()+" while parsing a race: ";
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="name"){ //should be at name tag
        r->setName(xml->readElementText());
        error += r->getName()+" has ";
        /*for(int i=0; i<races.length(); i++){
            if(races.at(i)->getName()==r->getName()){
                addError(error+"a duplicate entry");
                return false;
            }
        }*///Currently disabled for the sake of human variant
    } else{
        addError(error+"an improper tag order and/or a missing name tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="desc"){ //should be at description
        r->setDesc(xml->readElementText());
        if(xml->hasError()){
            addError(error+"an incorrectly formatted description");
            return false;
        }
        xml->readNext();
        xml->readNext();
    } else{
        addError(error+"an improper tag order and/or a missing desc tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="size"){ //should be at size
        r->setSize(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing size tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="speed"){ //should be at size
        r->setSpeed(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing speed tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="languages"){ //should be at languages
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="languages"){ //loop until languages end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a line end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="language"){ //we are at a language
                r->addToLangs(xml->readElementText());
                //std::cerr << r->getLangs().at(0).toStdString();
            }
            if(xml->name().toString()=="choice"){ //we are at a language choice
                QStringList qsl = xml->readElementText().split(",");
                if(qsl.length()>1){ //we have a list of choices
                    Choice* c = new Choice();
                    c->setDesc("Choose a language:");
                    for(int i=0; i<qsl.length(); i++){
                        c->add(qsl.at(i),"addlanguage|"+qsl.at(i));
                    }
                    r->getChoices()->addContent(c);
                } else{ //we should have a choice of any
                    if(qsl.at(0)=="any"){
                        Choice* c = new Choice();
                        c->setDesc("Choose a language:");
                        for(int i=0; i<langList.length(); i++){
                            c->add(langList.at(i),"addlanguage|"+langList.at(i));
                        }
                        r->getChoices()->addContent(c);
                    } else{
                        addError(error+"an incorrectly formatted language choice");
                        return false;
                    }
                }
            }
            xml->readNext();
            xml->readNext();
        }
    } else{
        addError(error+"an improper tag order and/or a missing languages tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="scores"){ //should be at scores
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="scores"){ //loop until languages end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a line end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="bonus"){ //we are at a bonus
                QStringList qsl = xml->readElementText().split(" ");
                if(qsl.length()==2){
                    int b = qsl.at(1).toInt();
                    if(b<1){
                        addError(error+"an incorrectly formatted score bonus");
                        return false;
                    }
                    if(qsl.at(0).toLower()=="str"){
                        r->setScore(0,b);
                    }
                    if(qsl.at(0).toLower()=="dex"){
                        r->setScore(1,b);
                    }
                    if(qsl.at(0).toLower()=="con"){
                        r->setScore(2,b);
                    }
                    if(qsl.at(0).toLower()=="int"){
                        r->setScore(3,b);
                    }
                    if(qsl.at(0).toLower()=="wis"){
                        r->setScore(4,b);
                    }
                    if(qsl.at(0).toLower()=="cha"){
                        r->setScore(5,b);
                    }
                } else{
                    addError(error+"an incorrectly formatted score bonus");
                    return false;
                }
            }
            if(xml->name().toString()=="choice"){ //we are at a score choice
                QStringList qsl = xml->readElementText().split(" ");
                if(qsl.length()==2){ //we have proper formatting
                    if(qsl.at(1).toInt()<1){
                        addError(error+"an incorrectly formatted score choice");
                        return false;
                    }
                    QString b = qsl.at(1);
                    //std::cerr << b.to << "\n";
                    if(qsl.at(0).split(",").length()==1){ //should be at any
                        if(qsl.at(0).toLower()=="any"){
                            Choice* c = new Choice();
                            c->setDesc("Choose an ability score to increase by "+b+":");
                            c->add("Strength","incrSTR|"+b);
                            c->add("Dexterity","incrDEX|"+b);
                            c->add("Constitution","incrCON|"+b);
                            c->add("Intelligence","incrINT|"+b);
                            c->add("Wisdom","incrWIS|"+b);
                            c->add("Charisma","incrCHA|"+b);
                            r->getChoices()->addContent(c);
                        } else{
                            addError(error+"an incorrectly formatted score choice");
                            return false;
                        }
                    } else{ //we should have a selection of scores
                        Choice* c = new Choice();
                        c->setDesc("Choose an ability score to increase by "+b+":");
                        QStringList scores = qsl.at(0).split(",");
                        for(int i=0; i<scores.length(); i++){
                            QString score = scores.at(i);
                            c->add(score.toUpper(),"incr"+score.toUpper()+"|"+b);
                        }
                        r->getChoices()->addContent(c);
                    }
                } else{
                    addError(error+"an incorrectly formatted score choice");
                    return false;
                }
            }
            xml->readNext();
            xml->readNext();
        }
    } else{
        addError(error+"an improper tag order and/or a missing scores tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="features"){ //might be at features
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="features"){ //loop until features end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a line end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="feature"){ //we are at a feature
                Feature* f = new Feature();
                f->setSource(r->getName());
                if(buildFeature(f)){
                    r->getFeatures()->addContent(f);
                } else{
                    addError(error+"an improperly formatted feature.");
                    return false;
                }
            }
            xml->readNext();
            xml->readNext();
        }
    } /*else{
        addError(error+"an improper tag order and/or a missing features tag");
        return false;
    }*/
    return true;
}

bool Database::buildSpell(Spell* s){
    QString error = "In source "+s->getSource()+" while parsing a spell: ";
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="name"){ //should be at name
        s->setName(xml->readElementText());
        error += s->getName()+" has ";
        //std::cerr << s->getName().toStdString()+"\n";
        if(spells->containsSpell(s->getName())>=0){
            addError(error+"a duplicate entry");
            return false;
        }
    } else{
        addError(error+"an improper tag order and/or a missing name tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="level"){ //should be at level
        s->setLevel(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing level tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="school"){ //should be at school
        s->setSchool(xml->readElementText());
        if(s->getSchool().split(" ").size()>1){
            ritualList.append(s->getName());
        }
    } else{
        addError(error+"an improper tag order and/or a missing school tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="casttime"){ //should be at casttime
        s->setCastTime(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing casttime tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="range"){ //should be at range
        s->setRange(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing range tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="comps"){ //should be at comps
        s->setComps(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing comps tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="duration"){ //should be at duration
        s->setDuration(xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing duration tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="desc"){ //should be at description
        s->setDesc(xml->readElementText());
        if(xml->hasError()){
            addError(error+"an improperly formatted description");
            return false;
        }
    } else{
        addError(error+"an improper tag order and/or a missing desc tag");
        return false;
    }
    return true;
}

bool Database::buildSubrace(Race* r){
    QString error = "In source "+r->getSource()+" while parsing a subrace: ";
    Race* parent;
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="name"){ //should be at name tag
        r->setName(xml->readElementText());
        error += r->getName()+" has ";
    } else{
        addError(error+"an improper tag order and/or a missing name tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="parent"){ //should be at parent tag
        QString parentName = xml->readElementText();
        for(int i=0; i<races.length(); i++){
            if(races.at(i)->getName()==parentName){
                parent = races.at(i);
                parentName = "";
            }
        }
        if(parentName!=""){
            addError(error+"a parent that isn't in the database. Check spelling and file parse order.");
            return false;
        }
    } else{
        addError(error+"an improper tag order and/or a missing parent tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="desc"){ //should be at description
        r->setDesc(xml->readElementText());
        if(xml->hasError()){
            addError(error+"an improperly formatted description");
            return false;
        }
    } else{
        addError(error+"an improper tag order and/or a missing desc tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="scores"){ //should be at scores
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="scores"){ //loop until languages end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a line end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="bonus"){ //we are at a bonus
                QStringList qsl = xml->readElementText().split(" ");
                if(qsl.length()==2){
                    int b = qsl.at(1).toInt();
                    if(b<1){
                        addError(error+"an incorrectly formatted score bonus");
                        return false;
                    }
                    if(qsl.at(0).toLower()=="str"){
                        r->setScore(0,b);
                    }
                    if(qsl.at(0).toLower()=="dex"){
                        r->setScore(1,b);
                    }
                    if(qsl.at(0).toLower()=="con"){
                        r->setScore(2,b);
                    }
                    if(qsl.at(0).toLower()=="int"){
                        r->setScore(3,b);
                    }
                    if(qsl.at(0).toLower()=="wis"){
                        r->setScore(4,b);
                    }
                    if(qsl.at(0).toLower()=="cha"){
                        r->setScore(5,b);
                    }
                } else{
                    addError(error+"an incorrectly formatted score bonus");
                    return false;
                }
            }
            if(xml->name().toString()=="choice"){ //we are at a score choice
                QStringList qsl = xml->readElementText().split(" ");
                if(qsl.length()==2){ //we have proper formatting
                    if(qsl.at(1).toInt()<1){
                        addError(error+"an incorrectly formatted score choice");
                        return false;
                    }
                    QString b = qsl.at(1);
                    //std::cerr << b.to << "\n";
                    if(qsl.at(0).split(",").length()==1){ //should be at any
                        if(qsl.at(0).toLower()=="any"){
                            Choice* c = new Choice();
                            c->setDesc("Choose an ability score to increase by "+b+":");
                            c->add("Strength","incrSTR|"+b);
                            c->add("Dexterity","incrDEX|"+b);
                            c->add("Constitution","incrCON|"+b);
                            c->add("Intelligence","incrINT|"+b);
                            c->add("Wisdom","incrWIS|"+b);
                            c->add("Charisma","incrCHA|"+b);
                            r->getChoices()->addContent(c);
                        } else{
                            addError(error+"an incorrectly formatted score choice");
                            return false;
                        }
                    } else{ //we should have a selection of scores
                        Choice* c = new Choice();
                        c->setDesc("Choose an ability score to increase by "+b+":");
                        QStringList scores = qsl.at(0).split(",");
                        for(int i=0; i<scores.length(); i++){
                            QString score = scores.at(i);
                            c->add(score.toUpper(),"incr"+score.toUpper()+"|"+b);
                        }
                        r->getChoices()->addContent(c);
                    }
                } else{
                    addError(error+"an incorrectly formatted score choice");
                    return false;
                }
            }
            xml->readNext();
            xml->readNext();
        }
    } else{
        addError(error+"an improper tag order and/or a missing scores tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="features"){ //should be at features
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="features"){ //loop until features end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a line end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="feature"){ //we are at a feature
                Feature* f = new Feature();
                f->setSource(r->getName());
                if(buildFeature(f)){
                    r->getFeatures()->addContent(f);
                } else{
                    addError(error+"an improperly formatted feature.");
                    return false;
                }
            }
            xml->readNext();
            xml->readNext();
        }
    } else{
        addError(error+"an improper tag order and/or a missing features tag");
        return false;
    }
    parent->getSubraces()->addContent(r);
    return true;
}

bool Database::buildFeature(Feature* f){
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="name"){ //should be at name
        QString temp = xml->readElementText();
        f->setName(temp);
    } else{
        addError("A feature is missing a name tag");
        return false;
    }
    QString error = f->getName()+" has ";
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="desc"){ //should be at description
        f->setDesc(xml->readElementText());
        if(xml->hasError()){
            addError(error+"an improperly formatted description");
            return false;
        }
    } else{
        addError(error+"an improper tag order and/or a missing desc tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="effects"){ //we may be at effects
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="effects"){ //loop until effects end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a line end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="effect"){ //we are at an effect
                f->addToBonuses(xml->readElementText());
            } else if(xml->name().toString()=="choice"){ //we are at a choice
                Choice* c = new Choice();
                if(buildChoice(c,xml->readElementText())){
                    f->addToChoices(c);
                } else{
                    addError(error+"an improperly formatted choice.");
                    return false;
                }
            }
            xml->readNext();
            xml->readNext();
        }
        xml->readNext();
        xml->readNext();
    }
    return true;
}

bool Database::buildChoice(Choice* c, QString s){
    QStringList qsl = s.split("|");
    if(qsl.length()==2){
        if(qsl.at(0).toLower()=="addlanguage"){
            c->setDesc("Choose a language:");
            if(qsl.at(1)=="any"){
                for(int i=0; i<langList.length(); i++){
                    c->add(langList.at(i),"addlanguage|"+langList.at(i));
                }
                return true;
            } else{
                QStringList langs = qsl.at(1).split(",");
                if(langs.size()<=1){
                    return false;
                }
                for(int i=0; i<langs.length(); i++){
                    c->add(langs.at(i),"addlanguage|"+langs.at(i));
                }
            }
        } else if(qsl.at(0).toLower()=="trainskill"){
            return true;
        } else if(qsl.at(0).toLower()=="addfeat"){
            return true;
        } else if(qsl.at(0).toLower()=="custom"){
            QStringList choices = qsl.at(1).split("+");
            for(int i=0; i<choices.length(); i++){
                QStringList option = choices.at(i).split(",");
                QString effect = option.at(1);
                effect.replace(":","|");
                c->add(option.at(0),effect);
            }
            return true;
        } else{
            return true;
        }
    } else if(qsl.length()==3){
        if(qsl.at(0).toLower()=="addspell"){
            return true; //for now
        } else if(qsl.at(0).toLower()=="custom"){
            c->setDesc(qsl.at(1));
            QStringList choices = qsl.at(2).split("+");
            for(int i=0; i<choices.length(); i++){
                QStringList option = choices.at(i).split(",");
                QString effect = option.at(1);
                effect.replace(":","|");
                c->add(option.at(0),effect);
            }
            return true;
        } else{
            return true;
        }
    } else{
        return true;
    }
    return true;
}

void Database::buildMCSpellSlots(){

    //1st level
    QList<int> a = QList<int>() << 2;
    for(int i=0; i<8; i++){
        a << 0;
    }
    MCSpellSlots[1] = a;

    //2nd level
    QList<int> b = QList<int>() << 3;
    for(int i=0; i<8; i++){
        b << 0;
    }
    MCSpellSlots[2] = b;

    //3rd level
    QList<int> c = QList<int>() << 4 << 2;
    for(int i=0; i<7; i++){
        c << 0;
    }
    MCSpellSlots[3] = c;

    //4th level
    QList<int> d = QList<int>() << 4 << 3;
    for(int i=0; i<7; i++){
        d << 0;
    }
    MCSpellSlots[4] = d;

    //5th level
    QList<int> e = QList<int>() << 4 << 3 << 2;
    for(int i=0; i<6; i++){
        e << 0;
    }
    MCSpellSlots[5] = e;

    //6th level
    QList<int> f = QList<int>() << 4 << 3 << 3;
    for(int i=0; i<6; i++){
        f << 0;
    }
    MCSpellSlots[6] = f;

    //7th level
    QList<int> g = QList<int>() << 4 << 3 << 3 << 1;
    for(int i=0; i<5; i++){
        g << 0;
    }
    MCSpellSlots[7] = g;

    //8th level
    QList<int> h = QList<int>() << 4 << 3 << 3 << 2;
    for(int i=0; i<5; i++){
        h << 0;
    }
    MCSpellSlots[8] = h;

    //9th level
    QList<int> i = QList<int>() << 4 << 3 << 3 << 3 << 1;
    for(int n=0; n<4; n++){
        i << 0;
    }
    MCSpellSlots[9] = i;

    //10th level
    QList<int> j = QList<int>() << 4 << 3 << 3 << 3 << 2;
    for(int i=0; i<4; i++){
        j << 0;
    }
    MCSpellSlots[10] = j;

    //11th level
    QList<int> k = QList<int>() << 4 << 3 << 3 << 3 << 2 << 1;
    for(int i=0; i<3; i++){
        k << 0;
    }
    MCSpellSlots[11] = k;

    //12th level
    QList<int> l = QList<int>() << 4 << 3 << 3 << 3 << 2 << 1;
    for(int i=0; i<3; i++){
        l << 0;
    }
    MCSpellSlots[12] = l;

    //13th level
    QList<int> m = QList<int>() << 4 << 3 << 3 << 3 << 2 << 1 << 1 << 0 << 0;
    MCSpellSlots[13] = m;

    //14th level
    QList<int> n = QList<int>() << 4 << 3 << 3 << 3 << 2 << 1 << 1 << 0 << 0;
    MCSpellSlots[14] = n;

    //15th level
    QList<int> o = QList<int>() << 4 << 3 << 3 << 3 << 2 << 1 << 1 << 1 << 0;
    MCSpellSlots[15] = o;

    //16th level
    QList<int> p = QList<int>() << 4 << 3 << 3 << 3 << 2 << 1 << 1 << 1 << 0;
    MCSpellSlots[16] = p;

    //17th level
    QList<int> q = QList<int>() << 4 << 3 << 3 << 3 << 2 << 1 << 1 << 1 << 1;
    MCSpellSlots[17] = q;

    //18th level
    QList<int> r = QList<int>() << 4 << 3 << 3 << 3 << 3 << 1 << 1 << 1 << 1;
    MCSpellSlots[18] = r;

    //19th level
    QList<int> s = QList<int>() << 4 << 3 << 3 << 3 << 3 << 2 << 1 << 1 << 1;
    MCSpellSlots[19] = s;

    //20th level
    QList<int> t = QList<int>() << 4 << 3 << 3 << 3 << 3 << 2 << 2 << 1 << 1;
    MCSpellSlots[20] = t;
}
