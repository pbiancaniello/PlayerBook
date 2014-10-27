#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>
//#include <QTextStream>
#include <QMessageBox>

#include <iostream>

#include "contentlist.h"
#include "database.h"

class Character : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(ContentList* features READ getFeatures NOTIFY featuresChanged)
    Q_PROPERTY(ContentList* spells READ getSpells NOTIFY spellsChanged)
public:
    explicit Character(QObject *parent = 0);

    void setDatabase(Database* d);

    Q_INVOKABLE void readCharacter();
    //Q_INVOKABLE void testRead();
    Q_INVOKABLE QString getName();
    Q_INVOKABLE void setName(QString newName);

    Q_INVOKABLE void addFeature(Feature* feature);
    Q_INVOKABLE bool addEffect(QString effect);
    Q_INVOKABLE bool removeEffect(QString effect);

    ContentList* getFeatures() const;
    ContentList* getSpells() const;

signals:
    void featuresChanged();
    void spellsChanged();

private:
    Database* database;
    QString name, race, subRace, charClass, subClass;
    QStringList languages;
    ContentList* features;
    ContentList* spells;
};

#endif // CHARACTER_H
