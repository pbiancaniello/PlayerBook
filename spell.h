/*
 * Spell
 *
 * A Spell is a QObject that is used to represent spells that a character or
 * monster might cast.
 *
*/

#ifndef SPELL_H
#define SPELL_H

#include <QObject>
#include <QStringList>

class Spell : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString level READ getLevel WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(QString school READ getSchool WRITE setSchool NOTIFY schoolChanged)
    Q_PROPERTY(QString castTime READ getCastTime WRITE setCastTime NOTIFY castTimeChanged)
    Q_PROPERTY(QString range READ getRange WRITE setRange NOTIFY rangeChanged)
    Q_PROPERTY(QString comps READ getComps WRITE setComps NOTIFY compsChanged)
    Q_PROPERTY(QString duration READ getDuration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(QString desc READ getDesc WRITE setDesc NOTIFY descChanged)
public:
    explicit Spell(QObject *parent = 0);

    QString getSource() const;
    bool setSource(QString newSource);

    QString getName() const;
    bool setName(QString newName);

    QString getLevel() const;
    bool setLevel(QString newLevel);

    QString getSchool() const;
    bool setSchool(QString newSchool);

    QString getCastTime() const;
    bool setCastTime(QString newCastTime);

    QString getRange() const;
    bool setRange(QString newRange);

    QString getComps() const;
    bool setComps(QString newComps);

    QString getDuration() const;
    bool setDuration(QString newDuration);

    QString getDesc() const;
    bool setDesc(QString newDesc);

signals:
    void sourceChanged();
    void nameChanged();
    void levelChanged();
    void schoolChanged();
    void castTimeChanged();
    void rangeChanged();
    void compsChanged();
    void durationChanged();
    void descChanged();

private:
    QString source, name, level, school,
    castTime, range, comps, duration, desc;

};

#endif // SPELL_H
