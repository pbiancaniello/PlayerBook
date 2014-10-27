#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>

#include "feature.h"

class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QObject *parent = 0);

signals:

private:
    int level;
    QList<Feature*> features;
};

#endif // LEVEL_H
