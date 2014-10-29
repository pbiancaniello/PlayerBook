/*
 * Character
 *
 * A Character is a QObject that represents the user's currently loaded
 * character.
 *
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>

#include <iostream>

#include "contentlist.h"
#include "database.h"

class Character : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString race READ getRace WRITE setRace NOTIFY raceChanged)
    Q_PROPERTY(QString subrace READ getSubrace WRITE setSubrace NOTIFY subraceChanged)
    Q_PROPERTY(QString charClass READ getCharClass WRITE setCharClass NOTIFY charClassChanged)
    Q_PROPERTY(int level READ getLevel WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(ContentList* features READ getFeatures NOTIFY featuresChanged)
    Q_PROPERTY(ContentList* spells READ getSpells NOTIFY spellsChanged)
    Q_PROPERTY(ContentList* extraSpells READ getExtraSpells NOTIFY extraSpellsChanged)
public:
    explicit Character(QObject *parent = 0);

    void setDatabase(Database* d);

    Q_INVOKABLE void readCharacter();

    QString getName() const;
    void setName(QString newName);

    QString getRace() const;
    void setRace(QString newRace);

    QString getSubrace() const;
    void setSubrace(QString newSubrace);

    QString getCharClass() const;
    void setCharClass(QString newCharClass);

    int getLevel() const;
    void setLevel(int newLevel);

    Q_INVOKABLE void addFeature(Feature* feature);
    Q_INVOKABLE bool addEffect(QString effect);
    Q_INVOKABLE bool removeEffect(QString effect);

    ContentList* getFeatures() const;
    ContentList* getSpells() const;
    ContentList* getExtraSpells() const;

signals:
    void nameChanged();
    void raceChanged();
    void subraceChanged();
    void charClassChanged();
    void levelChanged();
    void featuresChanged();
    void spellsChanged();
    void extraSpellsChanged();

private:
    Database* database;
    QString name, race, subrace, charClass, subClass;
    int level;
    QStringList languages;
    ContentList* features;
    ContentList* spells;
    ContentList* extraSpells;
};

#endif // CHARACTER_H
