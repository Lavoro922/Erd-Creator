#include "sconnection.h"

SConnection:: SConnection(QString* Constant ,QString* Connection_name){
    m_conn = new QSqlDatabase(QSqlDatabase::addDatabase(*Constant,*Connection_name));
    if (!m_conn->isValid()) throw  new SCExceptionInvalidDbType(m_conn->lastError().databaseText().toLatin1());
}

void SConnection::CloseConnection()
{
    if (m_conn->isOpen())
        m_conn->close();
}

bool SConnection::Connect(QString HostName,QString User,QString Pass,QString Db,int Port )
{
    if (m_conn->isOpen()) throw new SCExceptionConnectionExists("Connection Exists");
    //SPLIT STRING.
    m_conn->setHostName(HostName);
    m_conn->setUserName(User);
    m_conn->setPassword(Pass);
    m_conn->setDatabaseName(Db);
    m_conn->setPort(Port);
    return ( m_conn->open());
}

bool SConnection::ExecQuery(QString *Query)
{
    if (m_conn!=NULL){
        try{
            m_Equery = new QSqlQuery(*m_conn);
            bool res = m_Equery->exec(*Query);
            result = m_Equery->result();
            return res;
        }
        catch(exception e){
            delete m_Equery;
            throw new SCExceptionExecQuery(*Query->toAscii()+" doesn't work .");
        }

    }
    else
    return false;
}

bool SConnection::IsConnect()
{
    return ((m_conn !=NULL )&&(m_conn->isOpen()));
}
