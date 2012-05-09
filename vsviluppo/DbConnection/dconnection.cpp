#include "dconnection.h"

DConnection::DConnection(QString *dllname)
{
    lib_loader = new QLibrary(*dllname);

    Fconnect = (ConnectQuery)lib_loader->resolve("connect");
    Fexec = (ExecQ)lib_loader->resolve("ExecQuery");
    Fclose = (CloseConnect)lib_loader->resolve("Disconnect");
    if ((!Fconnect) || (!Fexec) || (!Fclose))
        throw new DllException("The dll don't follow the format (connect,ExecQuery,Disconnect).");
}

bool DConnection::Connect(QString *ConnectionString)
{
    if (!isConnect){
    try{
            return Fconnect(ConnectionString);
    }catch (exception e ){
            throw new  DllExceptionExecute((char*)"Connect execute Failed");
    }

    }
    else
        throw new DllExceptionConnectionExists("Connection exists.");
}

bool DConnection::ExecQuery(QString *Query)
{
    if ( isConnect){
        try{return Fexec(Query);}catch(exception e ){ throw new DllExceptionExecute(e.what());}
    }
}

void DConnection::CloseConnection()
{
    if ( isConnect){
        try{
        Fclose();
        }
        catch(exception e){
            throw new DllExceptionExecute(e.what());
        }
    }
}
