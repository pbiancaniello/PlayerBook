/*
 * CastingPage
 *
 * A CastingPage represents a character's spellcasting ability in a
 * certain class/subclass.
 *
*/

#ifndef CASTINGPAGE_H
#define CASTINGPAGE_H

#include <QObject>

#include "contentlist.h"

class CastingPage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString c_class READ getClass WRITE setClass NOTIFY classChanged)
    Q_PROPERTY(QString c_subclass READ getSubclass WRITE setSubclass NOTIFY subclassChanged)
    Q_PROPERTY(QString formula READ getFormula WRITE setFormula NOTIFY formulaChanged)
    Q_PROPERTY(QString stat READ getStat WRITE setStat NOTIFY statChanged)
    Q_PROPERTY(int weight READ getWeight WRITE setWeight NOTIFY weightChanged)
    Q_PROPERTY(ContentList* known READ getKnown NOTIFY knownChanged)
    Q_PROPERTY(ContentList* prepared READ getPrepared NOTIFY preparedChanged)
public:
    explicit CastingPage(QObject *parent = 0);

    QString getClass() const;
    bool setClass(QString c);

    QString getSubclass() const;
    bool setSubclass(QString s);

    QString getFormula() const;
    Q_INVOKABLE int numPrep(QString str, int classLVL, QList<int> charMods);
    bool setFormula(QString f);

    QString getStat() const;
    bool setStat(QString s);

    int getWeight() const;
    bool setWeight(int w);

    ContentList* getKnown();
    ContentList* getPrepared();

signals:
    void classChanged();
    void subclassChanged();
    void formulaChanged();
    void statChanged();
    void weightChanged();
    void knownChanged();
    void preparedChanged();

private:
    QString c_class, c_subclass, formula;
    QString stat; //0 for STR, 1 for DEX, 2 for CON, etc.
    int weight;
    ContentList* known;
    ContentList* prepared;
    QMap< int, QList<int> > spellSlots;
};

#endif // CASTINGPAGE_H
