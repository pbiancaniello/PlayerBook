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

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>

class Database : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ContentList* monsters READ getMonsters NOTIFY monstersChanged)
    Q_PROPERTY(ContentList* spells READ getSpells NOTIFY spellsChanged)
    Q_PROPERTY(QStringList spellList READ getSpellList NOTIFY spellListChanged)
    Q_PROPERTY(QStringList errorLog READ getErrorLog NOTIFY errorLogChanged)
public:
    explicit Database(QObject *parent = 0);

    ContentList* getMonsters() const;
    ContentList* getSpells() const;

    QStringList getSpellList() const;
    void addSpellToList(QString spell);

    QStringList getErrorLog() const;
    void addError(QString error);

    bool loopCheck(QString currentTag);

    void buildDatabase();

signals:
    void monstersChanged();
    void spellsChanged();
    void spellListChanged();
    void errorLogChanged();

private:
    QXmlStreamReader* xml;
    ContentList* monsters;
    ContentList* spells;
    QStringList spellList;
    QStringList errorLog;

    bool buildMonster(Monster* m);   
    bool buildSpell(Spell* s);

    int counter;
    QString tagType;
};

#endif // DATABASE_H
