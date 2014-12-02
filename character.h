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
#include <QXmlStreamWriter>
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
    Q_PROPERTY(QString className READ getClassName WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(QString alignment READ getAlignment WRITE setAlignment NOTIFY alignmentChanged)
    Q_PROPERTY(QString background READ getBackground WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(int level READ getLevel WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(QList<int> scores READ getScores NOTIFY scoresChanged)
    Q_PROPERTY(ContentList* features READ getFeatures NOTIFY featuresChanged)
    Q_PROPERTY(QList<CastingPage*> castingPages READ getCastingPages NOTIFY castingPagesChanged)
    Q_PROPERTY(ContentList* extraSpells READ getExtraSpells NOTIFY extraSpellsChanged)
public:
    explicit Character(QObject *parent = 0);

    void setDatabase(Database* d);

    Q_INVOKABLE void readCharacter();

    QString getName() const;
    void setName(QString newName);

    QString getRace() const;
    void setRace(QString newRace);
    Q_INVOKABLE void setRace(Race* r);

    QString getSubrace() const;
    void setSubrace(QString newSubrace);
    Q_INVOKABLE void setSubrace(Race* r);

    QString getClassName() const;
    void setClassName(QString newClassName);
    void generateClassName();

    QString getAlignment() const;
    void setAlignment(QString newAlignment);

    QString getBackground() const;
    void setBackground(QString newBackground);

    QList<int> getScores() const;
    Q_INVOKABLE QList<int> getMods();
    Q_INVOKABLE int getMod(int score);
    Q_INVOKABLE void addToScore(int score, int amount);

    int getLevel() const;
    void setLevel(int newLevel);

    Q_INVOKABLE int getClassLevel(QString className);
    Q_INVOKABLE void setClassLevel(QString className, int level);

    Q_INVOKABLE void addFeature(Feature* feature);
    Q_INVOKABLE bool addEffect(QString effect);
    Q_INVOKABLE bool removeEffect(QString effect);

    ContentList* getFeatures() const;
    Q_INVOKABLE QList<CastingPage*> getCastingPages() const;
    void addCastingPage(CastingPage* c);
    Q_INVOKABLE CastingPage* getCastingPage(QString name);
    Q_INVOKABLE CastingPage* getCastingPage(int i);
    Q_INVOKABLE int numPages() const;
    Q_INVOKABLE int casterLevel() const;
    Q_INVOKABLE bool isCaster() const;
    ContentList* getExtraSpells() const;

    Q_INVOKABLE QStringList getLeveledEffects(int l) const;

    Q_INVOKABLE void saveCharacter();

signals:
    void nameChanged();
    void raceChanged();
    void subraceChanged();
    void classNameChanged();
    void alignmentChanged();
    void backgroundChanged();
    void levelChanged();
    void scoresChanged();
    void featuresChanged();
    void castingPagesChanged();
    void extraSpellsChanged();

private:
    Database* database;
    QString name, race, subrace, className, subClass;
    QString alignment, background;
    QString speed, size;

    //0=STR, 1=DEX, 2=CON, 3=INT, 4=WIS, 5=CHA
    QList<int> scores;

    int level; //the character's overall level
    QMap<QString, int> levels;
    QStringList langs, profs;
    ContentList* features;
    QList<CastingPage*> castingPages;
    ContentList* extraSpells;
    QMap<int, QStringList> leveledEffects;

};

#endif // CHARACTER_H
