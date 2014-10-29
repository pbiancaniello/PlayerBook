/*
 * DItem
 *
 * A DItem is a QObject that is used to represent items like weapons, armor,
 * etc. Current implementation is being evaluated, I am still undecided on
 * whether or not to make it an abstract class or just have it contain all
 * of the various elements that different items might have.
 *
*/

#ifndef DITEM_H
#define DITEM_H

#include <QObject>

class DItem : public QObject
{
    Q_OBJECT
public:
    explicit DItem(QObject *parent = 0);

signals:

public slots:

};

#endif // DITEM_H
