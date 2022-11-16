#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "signvec.h"
#include <QObject>

enum AddResponse {
    Success,
    StartCollision,
    EndCollision
};

class Transport : public QObject
{
    Q_OBJECT
public:
    explicit Transport(QObject *parent = nullptr);

    QList<SignVec> *signs;

    AddResponse addSign(SignVec sign, long timestamp);
    AddResponse removeSign(unsigned int id);

signals:

};

#endif // TRANSPORT_H
