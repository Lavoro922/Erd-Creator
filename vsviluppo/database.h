#ifndef DATABASE_H
#define DATABASE_H
#include<QMessageBox>
#include <QApplication>
#include <QInputDialog>
#include<QDebug>
#include<QList>
#include <QFile>
#include <QDir>
#include <QErrorMessage>
#include <QObject>
#include <QtXml>
#include<DbConnection/dconnection.h>
#include<DbConnection/sconnection.h>
#include<Exception/filenotfound.h>
/**
  This class work only  about the type of all database  .
  The first class (GestType) manage a list of type for all database.
  Add a type in a database.
  Load from file a list that rappresent a list of type for all database in the follow format :
   NAME ;type;type;type; ecc..
   NAME ;type;type;type;ecc..
  The third class work about the query that can make in any  database .
  The different between the First Class and the third Class is that:
  the first load all type in  RAM.
  the third can load all query  of one database in RAM.
  */
/** Definition of constant of Database*/
const QString Erd_Constant_Query_File ="conf/cquery.dat";
const QString Erd_Query_File ="conf/query.xml";
const QString Erd_Type_File = "conf/type.dat";
/** Definition of constant of Database End*/
struct Db{
    QString* nomeDb;// nome database
    QStringList* ListaTipi;// lista dei tipi.
    };

class GestType{
private:
    QList<Db> lista;// lista dei db .
    int Database;
public:
    GestType();
    void CreaDb(QString* db);// crea un db
    void CreaDbType(QString* ndb,QString* value);// aggiungi un tipo a un db.
    void CreaListDb(QStringList* db,int start,int end);
    void CreaDbTypeList(QString* ndb ,QStringList* typelist,int start,int end);
    int  ExistDb(QString* dbname);
    int  FindDbType(QString* db,QString* value);
    bool DeleteDbType(QString* db,QString* value);
    void DeleteDb(QString* db);
    void LoadFromFile(QString* nfile);
    QStringList* ListDb();// lista db.
    QStringList* ListDbType(QString* db);// lista tipi di un db.
    QString* getCurrentDatabaseName();
    bool setDatabaseName(QString db);
    bool setDatabaseNamebyIndex(int value);
    int CurrentDatabaseIndex();
    bool isEmpty();
};
/**
  This class permits to describe a query .
  This has  QueryString that is the query.
  the query format is for example  " SELECT $$$ FROM $$$"
  where $$$ is param.
  ParamNumber is a number that represent a number of param.


  */
class Query{
    private :
    QString QueryString;
    QString Constant;
   int pNumber;
public:
    Query(QString pQueryString,QString pConstant);
    void    SetQueryString(QString value);
    QString QueryStr(QStringList pLParamString); // return Query compiled with pLParamString
    int paramNumber(); // list of number
    QString GetConstant(); // return a constant that rappresent a String.
    };
/**
   File of Constant example:
  Constant1
  Constant2
  Constant3
  - Every Line represent a Constant

    File of Query Example:
   <QueryList>
    <database>
      <Query1 Costant="Add_Attribute">
      Alter table user add column pippo char;
      </Query1>
     </database>
   </QueryList>
   -XML the name of tag is free and the attribute constant is the costant of Query.
   -The  value  of Node  is the query.

  */
class GestQuery{
 private:
    QList<Query> lista;
    QStringList CQuery;
    bool loaded;
 public:
    GestQuery(QString ConstantFile);
    void AddQuery(Query value);
    void IDeleteQuery(int i);
    Query* GetQueryFromConstant(QString constant);
    bool LoadConstantFromFile(QString value); //
    bool LoadQueryFromFile(QString value,QString nDb);//
    void Clear();
    };

class Database : public QObject
{
    Q_OBJECT
private:
    GestQuery *LQuery;
    Connection *conn;
    int cNumb;
public:
    explicit Database(int connectionNumber,QObject *parent = 0);
    bool CreateConnection(QString* hostName,QString* dbType,QString* nameDb,QString* user,QString* pass,int port =3306);
    bool CreateConnection(QString* dllname,QString* ConnectionString);
    bool DeleteConnection();
    QSqlQuery *ExecQuery(QString constant,QStringList* list);
    bool isConnect();
signals:

public slots:

};

#endif // DATABASE_H
