/*
 * Monster
 *
 * A Monster is a QObject that is used to represent monsters that a player might
 * have as companions or be capable of transforming into.
 *
*/

#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QStringList>

class Monster : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString size READ getSize WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString alignment READ getAlignment WRITE setAlignment NOTIFY alignmentChanged)
    Q_PROPERTY(QString AC READ getAC WRITE setAC NOTIFY ACChanged)
    Q_PROPERTY(QString HP READ getHP WRITE setHP NOTIFY HPChanged)
    Q_PROPERTY(QString speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(QList<QString> scores READ getScores WRITE setScores NOTIFY traitsChanged)
    Q_PROPERTY(QString sThrows READ getSThrows WRITE setSThrows NOTIFY sThrowsChanged)
    Q_PROPERTY(QString skills READ getSkills WRITE setSkills NOTIFY skillsChanged)
    Q_PROPERTY(QString damvulns READ getDamVulns WRITE setDamVulns NOTIFY damVulnsChanged)
    Q_PROPERTY(QString damres READ getDamRes WRITE setDamRes NOTIFY damResChanged)
    Q_PROPERTY(QString damimms READ getDamImms WRITE setDamImms NOTIFY damImmsChanged)
    Q_PROPERTY(QString conimms READ getConImms WRITE setConImms NOTIFY conImmsChanged)
    Q_PROPERTY(QString senses READ getSenses WRITE setSenses NOTIFY sensesChanged)
    Q_PROPERTY(QString langs READ getLangs WRITE setLangs NOTIFY langsChanged)
    Q_PROPERTY(QString challenge READ getChallenge WRITE setChallenge NOTIFY challengeChanged)
    Q_PROPERTY(QStringList traits READ getTraits NOTIFY traitsChanged)
    Q_PROPERTY(QStringList spells READ getSpells NOTIFY spellsChanged)
    Q_PROPERTY(QStringList actions READ getActions NOTIFY actionsChanged)
    Q_PROPERTY(QStringList reactions READ getReactions NOTIFY reactionsChanged)
    Q_PROPERTY(QStringList lActions READ getLActions NOTIFY lActionsChanged)
public:
    explicit Monster(QObject *parent = 0);

    QString objectName();

    QString getSource() const;
    void setSource(QString newSource);

    QString getName() const;
    void setName(QString newName);

    QString getSize() const;
    void setSize(QString newSize);

    QString getType() const;
    void setType(QString newType);

    QString getAlignment() const;
    void setAlignment(QString newAlignment);

    QString getAC() const;
    void setAC(QString newAC);

    QString getHP() const;
    void setHP(QString newHP);

    QString getSpeed() const;
    void setSpeed(QString newSpeed);

    QList<QString> getScores() const;
    void setScores(QList<QString> newScores);

    QString getSThrows() const;
    void setSThrows(QString newSThrows);

    QString getSkills() const;
    void setSkills(QString newSkills);

    QString getDamVulns() const;
    void setDamVulns(QString newDamVulns);

    QString getDamRes() const;
    void setDamRes(QString newDamRes);

    QString getDamImms() const;
    void setDamImms(QString newDamImms);

    QString getConImms() const;
    void setConImms(QString newConImms);

    QString getSenses() const;
    void setSenses(QString newSenses);

    QString getLangs() const;
    void setLangs(QString newLangs);

    QString getChallenge() const;
    void setChallenge(QString newChallenge);

    QStringList getTraits() const;
    void addTrait(QString trait);

    QStringList getSpells() const;
    void addSpell(QString spell);

    QStringList getActions() const;
    void addAction(QString action);

    QStringList getReactions() const;
    void addReaction(QString reaction);

    QStringList getLActions() const;
    void addLAction(QString lAction);

signals:
    void sourceChanged();
    void nameChanged();
    void sizeChanged();
    void typeChanged();
    void alignmentChanged();
    void ACChanged();
    void HPChanged();
    void speedChanged();
    void scoresChanged();
    void sThrowsChanged();
    void skillsChanged();
    void damVulnsChanged();
    void damResChanged();
    void damImmsChanged();
    void conImmsChanged();
    void sensesChanged();
    void langsChanged();
    void challengeChanged();
    void traitsChanged();
    void actionsChanged();
    void spellsChanged();
    void reactionsChanged();
    void lActionsChanged();

private:
    QString source, name, size, type, alignment, AC, HP, speed;

    //0=STR, 1=DEX, 2=CON, 3=INT, 4=WIS, 5=CHA
    QList<QString> scores;

    QString sThrows, skills, damvulns, damres, damimms,
    conimms, senses, langs, challenge;

    //By parsing correctly, we can reduce each trait/action/laction to pre-formatted lines of text
    QStringList traits, spells, actions, reactions, lActions;

};

#endif // MONSTER_H
