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

class Race : public QObject
{
    Q_OBJECT
public:
    explicit Race(QObject *parent = 0);

signals:

private:
    QString name;
    QList<Race*> subraces;
};

#endif // RACE_H
