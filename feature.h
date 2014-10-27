#ifndef FEATURE_H
#define FEATURE_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QStringList>

class Feature : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QStringList desc READ getDesc NOTIFY descChanged)
    Q_PROPERTY(QStringList bonuses READ getBonuses NOTIFY bonusesChanged)
    Q_PROPERTY(QStringList choices READ getChoices NOTIFY choicesChanged)
    Q_PROPERTY(QStringList effects READ getEffects NOTIFY effectsChanged)
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

    QMap<QString,QString> getChoiceMap() const;
    QStringList getChoices() const;
    QStringList getEffects() const;
    bool addToChoiceMap(QString choice, QString effect);
    Q_INVOKABLE QString getEffect(QString choice) const;

    /*QStringList getChoices() const;
    bool addToChoices(QString choice);*/


signals:
    void sourceChanged();
    void nameChanged();
    void descChanged();
    void bonusesChanged();
    void choicesChanged();
    void effectsChanged();

private:
    QString source, name;
    QStringList desc, bonuses;//, choices, effects;
    QMap<QString,QString> choiceMap; //Map list of choices to effects (spell, feature, bonus etc.)
    //QList<QMap<QString,QString>> temp;

};

#endif // FEATURE_H
