#ifndef DCONNECTION_H
#define DCONNECTION_H
#include<DbConnection/connection.h>
#include<DbConnection/cexception.h>

typedef void (*CloseConnect)();
typedef bool (*ConnectQuery)(QString*);
typedef bool (*ExecQ)(QString*);

class DConnection :public Connection{ // "Dynamic" connection
private:
    QLibrary *lib_loader;
    ConnectQuery Fconnect;
    CloseConnect Fclose;
    ExecQ Fexec;
public:
    DConnection(QString* dllname);
    bool Connect(QString *ConnectionString);
    bool ExecQuery(QString*  Query)  ;
    void CloseConnection();
};

#endif // DCONNECTION_H
