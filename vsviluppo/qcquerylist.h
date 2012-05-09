#ifndef QCQUERYLIST_H
#define QCQUERYLIST_H

#include <QThread>
#include<database.h>
class QCQueryList : public QThread
{
private:
    Database* conn;

public:
    QCQueryList();
};

#endif // QCQUERYLIST_H
