#include "database.h"

Database::Database(QObject *parent) :
    QObject(parent){
    monsters = new ContentList();
    //races = new ContentList();
    //races = new QList<Race*>();
    spells = new ContentList();
    tagType = "temp";
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
    QFile* file = new QFile(filename);
        // If we can't open it, let's show an error message.
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << "Couldn't open file";
    } else{
        //std::cerr << "yup";
    }
        // QXmlStreamReader takes any QIODevice.
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
                    //std::cerr << type.toStdString() <<"\n";
                    if(xml->tokenType()!=QXmlStreamReader::EndElement){
                        QString type = xml->name().toString();
                        /*std::cerr << type.toStdString() << "\n";
                        if(!loopCheck(type)){
                            addError("Infinite loop encountered in "+source+", missing an end tag somewhere.");
                            break;
                        }
                        tagType = type;*/
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
        m->setSThrows("<b>Saving Throws</b> "+xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="skills"){ //may be at sthrows
        m->setSkills("<b>Skills</b> "+xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="damvulns"){ //may be at damvulns
        m->setDamVulns("<b>Damage Vulnerabilities</b> "+xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="damres"){ //may be at damres
        m->setDamRes("<b>Damage Resistances</b> "+xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="damimms"){ //may be at damimms
        m->setDamImms("<b>Damage Immunities</b> "+xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="conimms"){ //may be at conimms
        m->setConImms("<b>Condition Immunities</b> "+xml->readElementText());
        xml->readNext();
        xml->readNext();
    }
    if(xml->name().toString()=="senses"){ //should be at senses
        m->setSenses("<b>Senses</b> "+xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing senses tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="langs"){ //should be at langs
        m->setLangs("<b>Languages</b> "+xml->readElementText());
    } else{
        addError(error+"an improper tag order and/or a missing langs tag");
        return false;
    }
    xml->readNext();
    xml->readNext();
    if(xml->name().toString()=="challenge"){ //should be at challenge
        m->setChallenge("<b>Challenge</b> "+xml->readElementText());
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
            if(xml->name().toString()=="trait"){ //we are at a trait
                xml->readNext();
                xml->readNext();
                if(xml->name().toString()=="name"){ //should be at trait name
                    QString traitname = "<b><i>"+xml->readElementText()+"</b></i>";
                    xml->readNext();
                    xml->readNext();
                    if(xml->name().toString()=="effect"){ //should be at trait effect
                        QString effect = xml->readElementText();
                        m->addTrait(traitname+effect);
                        xml->readNext();
                        xml->readNext(); //skip the effect endtag
                    } else{
                        addError(error+"a misformatted trait named "+traitname+", check effect tags");
                        return false;
                    }
                } else{
                    addError(error+"a misformatted trait, check name tags");
                    return false;
                }
            } else if(xml->name().toString()=="spellcasting"){ //found a spellcasting trait
                xml->readNext();
                xml->readNext();
                if(xml->name().toString()=="name"){ //should be at name
                    QString castingname = "<b><i>"+xml->readElementText()+"</b></i>";
                    xml->readNext();
                    xml->readNext();
                    if(xml->name().toString()=="effect"){ //should be at effect
                        QString castingeffect = xml->readElementText()+"";
                        xml->readNext();
                        xml->readNext();
                        QString totalSpells = castingname+castingeffect+"<br>";
                        if(xml->name().toString()=="lines"){ //should be at spell lines
                            xml->readNext();
                            xml->readNext();
                            while(xml->name().toString()!="lines"){ //loop until lines end tag
                                /*QString type = xml->name().toString();
                                if(!loopCheck(type)){
                                    addError(error+"is missing a trait line end tag somewhere.");
                                    break;
                                }
                                tagType = type;*/
                                if(xml->name().toString()=="line"){ //found a line
                                    xml->readNext();
                                    xml->readNext();
                                    if(xml->name().toString()=="usage"){ //should be at usage
                                        QString usage = "<br>"+xml->readElementText();
                                        xml->readNext();
                                        xml->readNext();
                                        if(xml->name().toString()=="spells"){ //should be at spells
                                            QString text = xml->readElementText();
                                            QString spells = "<i>"+text+"</i>";
                                            QStringList tempSpells = text.toLower().split(",");
                                            m->addSpell(tempSpells[0]);
                                            if(tempSpells.length()>1){
                                                for(int i=1; i<tempSpells.length(); i++){
                                                    QString ts = tempSpells[i].trimmed();
                                                    //ts = ts.left(1).toUpper()+ts.right(ts.length()-1);
                                                    m->addSpell(ts);
                                                    //std::cerr << ts.toStdString() << "\n";
                                                }
                                            }
                                            //std::cerr << m->objectName().toStdString() << "\n";
                                            totalSpells+=usage+spells;
                                            xml->readNext();
                                            xml->readNext();
                                        } else{
                                            addError(error+"a misformatted spellcasting trait, check spell tags");
                                            return false;
                                        }
                                    } else{
                                        addError(error+"a misformatted spellcasting trait, check usage tags");
                                        return false;
                                    }
                                }
                                xml->readNext();
                                xml->readNext();
                            }
                            xml->readNext();
                            xml->readNext();
                        } else{
                            addError(error+"a misformatted spellcasting trait, check lines tags");
                            return false;
                        }
                        m->addTrait(totalSpells);
                    } else{
                        addError(error+"a misformatted spellcasting trait, check effect tags");
                        return false;
                    }
                } else{
                    addError(error+"a misformatted spellcasting trait, check name tags");
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
                xml->readNext();
                xml->readNext();
                if(xml->name().toString()=="name"){ //should be at name
                    QString action = "<b><i>"+xml->readElementText()+"</i></b>";
                    xml->readNext();
                    xml->readNext();
                    if(xml->name().toString()=="attack"){ // we may be at an attack
                        action+="<i>"+xml->readElementText()+"</i>";
                        xml->readNext();
                        xml->readNext();
                    }
                    if(xml->name().toString()=="effect"){ // should be at an effect
                        action+=xml->readElementText();
                        m->addAction(action);
                        xml->readNext();
                        xml->readNext();
                    } else{
                        addError(error+"a misformatted action, check effect tags");
                        return false;
                    }
                } else{
                    addError(error+"a misformatted action, check name tags");
                    return false;
                }
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
                xml->readNext();
                xml->readNext();
                if(xml->name().toString()=="name"){ //should be at name
                    QString reaction = "<b><i>"+xml->readElementText()+"</i></b>";
                    xml->readNext();
                    xml->readNext();
                    if(xml->name().toString()=="effect"){ // should be at an effect
                        reaction+=xml->readElementText();
                        m->addReaction(reaction);
                        xml->readNext();
                        xml->readNext();
                    } else{
                        addError(error+"a misformatted reaction, check effect tags");
                        return false;
                    }
                } else{
                    addError(error+"a misformatted reaction, check name tags");
                    return false;
                }
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
        if(xml->name().toString()=="details"){ //should be at details tag
            m->addLAction(xml->readElementText()+"<br>");
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
                    xml->readNext();
                    xml->readNext();
                    if(xml->name().toString()=="name"){ //should be at name
                        QString laction = "<b>"+xml->readElementText()+"</b>";
                        xml->readNext();
                        xml->readNext();
                        if(xml->name().toString()=="effect"){
                            laction += xml->readElementText();
                            m->addLAction(laction);
                            xml->readNext();
                            xml->readNext();
                            xml->readNext();
                            xml->readNext();
                        } else{
                            addError(error+"a misformatted legendary action, check effect tags");
                            return false;
                        }
                    } else{
                        addError(error+"a misformatted legendary action, check name tags");
                        return false;
                    }
                } else{
                    addError(error+"a misformatted legendary action, check laction tags");
                    return false;
                }
            }
        } else{
            addError(error+"a misformatted legendary action, check details tags");
            return false;
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
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="desc"){ //loop until description end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a line end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="line"){ //we are at a line
                xml->readNext();
                xml->readNext();
                QString line = "";
                while(xml->name().toString()!="line"){ //loop until line end tag
                    if(xml->name().toString()=="plain"){
                        line+=xml->readElementText();
                    } else if (xml->name().toString()=="bold"){
                        line+="<b>"+xml->readElementText()+"</b>";
                    } else if (xml->name().toString()=="italic"){
                        line+="<i>"+xml->readElementText()+"</i>";
                    } else if (xml->name().toString()=="bolditalic"){
                        line+="<b><i>"+xml->readElementText()+"</b></i>";
                    } else{
                        addError(error+"has improper formatting in its description");
                        return false;
                    }
                    xml->readNext();
                    xml->readNext();
                }
                r->addToDesc(line);
            } else{
                addError(error+"has improper formatting in its desc");
                return false;
            }
            xml->readNext();
            xml->readNext();
        }
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
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="desc"){ //loop until description end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a line end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="line"){ //we are at a line
                xml->readNext();
                xml->readNext();
                QString line = "";
                while(xml->name().toString()!="line"){ //loop until line end tag
                    if(xml->name().toString()=="plain"){
                        line+=xml->readElementText();
                    } else if (xml->name().toString()=="bold"){
                        line+="<b>"+xml->readElementText()+"</b>";
                    } else if (xml->name().toString()=="italic"){
                        line+="<i>"+xml->readElementText()+"</i>";
                    } else if (xml->name().toString()=="bolditalic"){
                        line+="<b><i>"+xml->readElementText()+"</b></i>";
                    } else{
                        addError(error+"has improper formatting in its description");
                        return false;
                    }
                    xml->readNext();
                    xml->readNext();
                }
                s->addToDesc(line);
            } else{
                addError(error+"has improper formatting in its desc");
                return false;
            }
            xml->readNext();
            xml->readNext();
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
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="desc"){ //loop until description end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a line end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="line"){ //we are at a line
                xml->readNext();
                xml->readNext();
                QString line = "";
                while(xml->name().toString()!="line"){ //loop until line end tag
                    if(xml->name().toString()=="plain"){
                        line+=xml->readElementText();
                    } else if (xml->name().toString()=="bold"){
                        line+="<b>"+xml->readElementText()+"</b>";
                    } else if (xml->name().toString()=="italic"){
                        line+="<i>"+xml->readElementText()+"</i>";
                    } else if (xml->name().toString()=="bolditalic"){
                        line+="<b><i>"+xml->readElementText()+"</b></i>";
                    } else{
                        addError(error+"has improper formatting in its description");
                        return false;
                    }
                    xml->readNext();
                    xml->readNext();
                }
                r->addToDesc(line);
            } else{
                addError(error+"has improper formatting in its description");
                return false;
            }
            xml->readNext();
            xml->readNext();
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
        xml->readNext();
        xml->readNext();
        while(xml->name().toString()!="desc"){ //loop until description end tag
            /*QString type = xml->name().toString();
            if(!loopCheck(type)){
                addError(error+"is missing a line end tag somewhere.");
                break;
            }
            tagType = type;*/
            if(xml->name().toString()=="line"){ //we are at a line
                xml->readNext();
                xml->readNext();
                QString line = "";
                while(xml->name().toString()!="line"){ //loop until line end tag
                    if(xml->name().toString()=="plain"){
                        line+=xml->readElementText();
                    } else if (xml->name().toString()=="bold"){
                        line+="<b>"+xml->readElementText()+"</b>";
                    } else if (xml->name().toString()=="italic"){
                        line+="<i>"+xml->readElementText()+"</i>";
                    } else if (xml->name().toString()=="bolditalic"){
                        line+="<b><i>"+xml->readElementText()+"</b></i>";
                    } else{
                        addError(error+"improper formatting in its description");
                        return false;
                    }
                    xml->readNext();
                    xml->readNext();
                }
                f->addToDesc(line);
            } else{
                addError(error+"improper formatting in its description");
                return false;
            }
            xml->readNext();
            xml->readNext();
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
