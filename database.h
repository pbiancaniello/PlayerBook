/*
 * Database
 *
 * A Database is a QObject that is used both as a container for all content
 * (monsters, spells, races, etc...) and to parse it from xml documents.
 *
 * Current tasks that require fairly urgent attention are:
 *
 * Parse order - Have to decide on how to deal with potentially parsing
 * content with certain dependencies before those dependencies i.e a
 * subrace before a race
 *
 * Folder parsing - Have to figure out what the process is for parsing
 * the entirety of a given folder
 *
*/

#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>

#include "contentlist.h"
#include "feature.h"
#include "race.h"
#include "castingpage.h"

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>
#include <QDir>

class Database : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ContentList* monsters READ getMonsters NOTIFY monstersChanged)
    //Q_PROPERTY(ContentList* races READ getRaces NOTIFY racesChanged)
    Q_PROPERTY(QQmlListProperty<Race> races READ getRaces NOTIFY racesChanged)
    Q_PROPERTY(ContentList* spells READ getSpells NOTIFY spellsChanged)
    Q_PROPERTY(QStringList spellList READ getSpellList NOTIFY spellListChanged)
    Q_PROPERTY(QStringList ritualList READ getRitualList NOTIFY ritualListChanged)
    Q_PROPERTY(QStringList langList READ getLangList NOTIFY langListChanged)
    Q_PROPERTY(QStringList errorLog READ getErrorLog NOTIFY errorLogChanged)
public:
    explicit Database(QObject *parent = 0);

    ContentList* getMonsters() const;

    //ContentList* getRaces() const;
    QQmlListProperty<Race> getRaces();
    Q_INVOKABLE Race* getRace(int i);

    ContentList* getSpells() const;

    QStringList getSpellList() const;
    QStringList getRitualList() const;
    QStringList getLangList() const;
    Q_INVOKABLE bool containsClass(QString c) const;

    Q_INVOKABLE QList<int> getMCSpellSlots(int casterLevel) const;
    Q_INVOKABLE int getMCSpellSlots(int casterLevel, int slotLevel) const;

    QStringList getErrorLog() const;
    void addError(QString error);

    bool loopCheck(QString currentTag);

    void buildDatabase();

signals:
    void monstersChanged();
    void racesChanged();
    void spellsChanged();
    void spellListChanged();
    void ritualListChanged();
    void langListChanged();
    void errorLogChanged();

private:
    QXmlStreamReader* xml;
    ContentList* monsters;
    //ContentList* races;
    QList<Race*> races;
    ContentList* spells;
    QStringList spellList, ritualList, langList, classList;
    QMap< int, QList<int> > MCSpellSlots; //Multiclass Spell Slots, hardcoded for now
    QStringList errorLog;

    bool parseFile(QString filename);
    bool buildMonster(Monster* m);
    bool buildRace(Race* r);
    bool buildSpell(Spell* s);
    bool buildSubrace(Race* r);
    bool buildFeature(Feature* f);
    bool buildChoice(Choice* c, QString s);

    void buildMCSpellSlots();

    int counter;
    QString tagType;
};

#endif // DATABASE_H
