/*
 * Choice
 *
 * A Choice is a QObject that represents a choice that a user must make.
 * Currently only used by features, but may be used for leveling up.
 *
*/

#ifndef CHOICE_H
#define CHOICE_H

#include <QObject>
#include <QStringList>
#include <QMap>

class Choice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString desc READ getDesc WRITE setDesc NOTIFY descChanged)
    Q_PROPERTY(QStringList options READ getOptions NOTIFY optionsChanged)
    Q_PROPERTY(QStringList effects READ getEffects NOTIFY effectsChanged)
    Q_PROPERTY(int sel READ getSel WRITE setSel NOTIFY selChanged)
    Q_PROPERTY(int lvl READ getLvl WRITE setLvl NOTIFY lvlChanged)
public:
    explicit Choice(QObject *parent = 0);

    QString getDesc() const;
    bool setDesc(QString newDesc);

    Q_INVOKABLE void add(QString option, QString effect);
    QStringList getOptions() const;
    QStringList getEffects() const;

    int getSel() const;
    bool setSel(int newSel);

    int getLvl() const;
    bool setLvl(int newLvl);

signals:
    void descChanged();
    void optionsChanged();
    void effectsChanged();
    void selChanged();
    void lvlChanged();

private:
    QString desc;
    QMap<QString,QString> choices;
    int sel; //the currently selected option
    int lvl; //the level a character must be to make a choice

};

#endif // CHOICE_H
