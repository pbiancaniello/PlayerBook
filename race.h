/*
 * Race
 *
 * A Race is a QObject that is used to represent character race. Currently unsure
 * of how races and subraces will be implemented. Most likely a race will have
 * all elements necessary to represent a complete race, a base race, and a subrace.
 * Current idea is to have "abstract" or base races marked in their xml as such and
 * then at parse time create the base object then create copies and alter the
 * necessary attributes for its subraces, but never actually add the base...
 *
 * Or maybe instead have each Race object contain a list of references to its subraces,
 * so selection at character creation is less complex.
 *
*/

#ifndef RACE_H
#define RACE_H

#include <QObject>
#include "contentlist.h"
//#include "feature.h"
//#include <QStringList>

class Race : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QStringList desc READ getDesc NOTIFY descChanged)
    Q_PROPERTY(QString size READ getSize WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(QStringList langs READ getLangs NOTIFY langsChanged)
    //Q_PROPERTY(ContentList* features READ getFeatures NOTIFY featuresChanged)
    //Q_PROPERTY(ContentList* features READ getFeatures NOTIFY featuresChanged)
    Q_PROPERTY(ContentList* choices READ getChoices NOTIFY choicesChanged)
    Q_PROPERTY(QList<int> scores READ getScores NOTIFY scoresChanged)
    Q_PROPERTY(ContentList* features READ getFeatures NOTIFY featuresChanged)
    Q_PROPERTY(ContentList* subraces READ getSubraces NOTIFY subracesChanged)
public:
    explicit Race(QObject *parent = 0);

    QString getSource() const;
    bool setSource(QString s);

    QString getName() const;
    bool setName(QString n);

    QStringList getDesc() const;
    void addToDesc(QString s);

    QString getSize() const;
    bool setSize(QString s);

    QString getSpeed() const;
    bool setSpeed(QString s);

    QStringList getLangs() const;
    void addToLangs(QString l);

    ContentList* getChoices() const;

    QList<int> getScores() const;
    void setScore(int i, int s);

    ContentList* getFeatures() const;

    ContentList* getSubraces() const;

signals:
    void sourceChanged();
    void nameChanged();
    void descChanged();
    void sizeChanged();
    void speedChanged();
    void langsChanged();
    void choicesChanged();
    void scoresChanged();
    void featuresChanged();
    void subracesChanged();

private:
    QString source, name, size, speed;
    QStringList desc, langs;
    ContentList* choices;
    QList<int> scores; //0=STR, 1=DEX, 2=CON, 3=INT, 4=WIS, 5=CHA
    ContentList* features;
    ContentList* subraces;

};

#endif // RACE_H
