/*
 * Level
 *
 * Currently under evaluation, in theory a Level is a QObject that represents
 * each level a character attains. This would allow for potentially easy
 * retconning, but the current projected solution seems more elegant. Instead
 * a Character and/or the file that represents it will contain "snapshots" of
 * the character at different levels. In this way a user can simply roll back
 * to an earlier iteration. The only real downside to this approach is that
 * a user would then have to re-level for everything in between. I.e. if a
 * user wants to changed something from level 5 and is now level 12, levels
 * 6-12 would have to be regenerated. Of course it may also be possible to
 * simply load and alter only level 5, but at present I am unsure of how
 * complex a task that might be.
 *
*/

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
