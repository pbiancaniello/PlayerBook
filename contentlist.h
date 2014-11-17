/*
 * ContentList
 *
 * A ContentList is a QObject that is used as a wrapper for lists of custom
 * objects. Rather than have separate QQmlListProperty instances and methods
 * to interact with them for each separate list of custom QObjects in classes
 * like Database and Character only a ContentList is needed.
 *
*/

#ifndef CONTENTLIST_H
#define CONTENTLIST_H

#include <QObject>
#include <QQmlListProperty>

#include <stdlib.h>
#include <iostream>

#include "monster.h"
//#include "race.h"
#include "spell.h"

class ContentList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> list READ getList NOTIFY listChanged)
public:
    explicit ContentList(QObject *parent = 0);  
    QQmlListProperty<QObject> getList();
    Q_INVOKABLE bool addContent(QObject* c);
    Q_INVOKABLE QObject* get(int i);
    Q_INVOKABLE bool contains(QObject* o);
    Q_INVOKABLE int containsMonster(QString s);
    //Q_INVOKABLE int containsRace(QString s);
    Q_INVOKABLE int containsSpell(QString s);
    Q_INVOKABLE void remove(int i);
    Q_INVOKABLE void clear();
    Q_INVOKABLE int length();
    //Q_INVOKABLE void sort();
    //QList<QObject*> list;

signals:
    void listChanged();
    void contentAdded();

private:
    QList<QObject*> list;
    //bool contentLessThan(const QObject* o1, const QObject* o2);
};

#endif // CONTENTLIST_H
