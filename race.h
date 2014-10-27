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
