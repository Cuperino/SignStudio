// SPDX-FileCopyrightText: 2022 Javier O. Cordero Pérez
//
// SPDX-License-Identifier: AGPL-3.0-only

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
