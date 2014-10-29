/*
 * Feat
 *
 * A Feat is a QObject that is used to represent feats. Initially I believed
 * that such a class may be necessary but upon further development I am fairly
 * certain that feats will simply be represented by Features, and this class
 * will soon be removed.
 *
*/

#ifndef FEAT_H
#define FEAT_H

#include <QObject>

class Feat : public QObject
{
    Q_OBJECT
public:
    explicit Feat(QObject *parent = 0);

signals:

public slots:

};

#endif // FEAT_H
