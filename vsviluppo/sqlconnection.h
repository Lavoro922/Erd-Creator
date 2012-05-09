#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include <QObject>
/**
  Define a interface of Connection.
  */

class SqlConnection : public QObject
{
    Q_OBJECT
public:
    explicit SqlConnection(QObject *parent = 0);

signals:

public slots:

};

#endif // SQLCONNECTION_H
