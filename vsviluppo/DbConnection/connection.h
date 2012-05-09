#ifndef CONNECTION_H
#define CONNECTION_H

#include<QLibrary>
#include<QDir>
#include<QtSql/QSqlResult>
class Connection {
    protected:
    const QSqlResult* result;
    bool isConnect;
    public:
   const QSqlResult* GetResult(){ return result; }
    bool IsConnect(){return isConnect;}
     bool Connect(QString *ConnectionString){return false;};
     bool ExecQuery(QString*  Query){ return false;};
     void CloseConnection(){}  ;
};



#endif // CONNECTION_H
