#ifndef SCONNECTION_H
#define SCONNECTION_H
#include<DbConnection/connection.h>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlDriver>
#include<QtSql/QSqlQuery>
#include<DbConnection/cexception.h>
#include<QtSql/QSqlError>
class SConnection : public Connection{ // standard connection.
private:
     QSqlDatabase *m_conn; // Connector.
     QSqlQuery    *m_Equery;// Execute query.
public:
    SConnection(QString* Constant,QString* Connection_name );
    bool Connect(QString HostName,QString User,QString Pass,QString Db,int Port = 3306) ;
    bool ExecQuery(QString*  Query)  ;
    bool IsConnect();
    void CloseConnection();
};
#endif // SCONNECTION_H
