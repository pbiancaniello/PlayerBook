/*
 * Feature
 *
 * A Feature is a QObject that is used to represent the features that are granted
 * to a character by their race and class(es).
 *
*/

#ifndef FEATURE_H
#define FEATURE_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QStringList>

#include "contentlist.h"
#include "choice.h"

class Feature : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QStringList desc READ getDesc NOTIFY descChanged)
    Q_PROPERTY(QStringList bonuses READ getBonuses NOTIFY bonusesChanged)
    Q_PROPERTY(ContentList* choices READ getChoices NOTIFY choicesChanged)
public:
    explicit Feature(QObject *parent = 0);

    QString getSource() const;
    void setSource(QString newSource);

    QString getName() const;
    void setName(QString newName);

    QStringList getDesc() const;
    bool addToDesc(QString line);

    QStringList getBonuses() const;
    bool addToBonuses(QString bonus);

    ContentList* getChoices() const;
    void addToChoices(Choice* choice);

signals:
    void sourceChanged();
    void nameChanged();
    void descChanged();
    void bonusesChanged();
    void choicesChanged();

private:
    QString source, name;
    QStringList desc, bonuses;
    ContentList* choices;

};

#endif // FEATURE_H
