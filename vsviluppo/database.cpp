#include "database.h"

Database::Database(int connectionNumber,QObject *parent) :
    QObject(parent)
{

        LQuery = new GestQuery(Erd_Constant_Query_File);
        cNumb = connectionNumber;
}


void GestType::LoadFromFile(QString *nfile)
    {
        QFile file (*nfile);

        if (!file.open(QIODevice::ReadOnly))
          throw new FileNotFound(" The file "+file.fileName().toAscii());
        QTextStream  in (&file);
        int i = 0;
        while (!in.atEnd()){
                i++;

                QString app = in.readLine();
                QStringList liString = app.split(";");
                qDebug()<<QString::number(liString.count());
                if (liString.count()==0){
                        QErrorMessage *error = new QErrorMessage();
                        error->showMessage("Errore nela riga "+QString::number(i)+": Elementi 0 .");
                    }
                CreaDb(&liString[0]);
                QStringList *pLs = new QStringList(liString);
                CreaDbTypeList(&liString[0],pLs,1,liString.count());
            }

    }

void GestType::CreaListDb(QStringList *db,int start,int end)
    {
        for (int i = 0;i<db->count();i++){
                if ((i>=start )&& (i<=end)){
                        QString value = (db->at(i));
                        QString* pval = new QString(value);
                        CreaDb(pval);

                    }
            }
    }

void GestType::CreaDbTypeList(QString* ndb ,QStringList *typelist,int start,int end)
    {
        int numb = ExistDb(ndb);
        if (numb!=-1)
            {
                Db *dbtype = &lista[numb];
                dbtype->ListaTipi = new QStringList();
                for (int i = 0;i<typelist->count();i++){
                        if ((i>=start )&& (i<=end)){
                                dbtype->ListaTipi->append(typelist->at(i));
                            }
                    }
            }
    }

void GestType::CreaDbType(QString *ndb, QString *value)
    {
        int numb = ExistDb(ndb);
        if (numb!=-1)
            {
                Db dbtype = lista[numb];
                dbtype.ListaTipi->append(*value);
            }
    }

QStringList * GestType::ListDb()
    {
        QStringList *app = new QStringList();
        for (int i = 0 ;i<lista.count();i++)
            app->append(*lista[i].nomeDb);
        return app;
}

QStringList *GestType::ListDbType(QString *db)
{
    for (int i=0;i<lista.count();i++){
        if (lista.at(i).nomeDb==*db)
            return lista.at(i).ListaTipi;
    }
    return NULL;
}




void GestType::CreaDb(QString *db)
    {
        Db value;
        value.nomeDb = db;
        value.ListaTipi =  new QStringList();
        lista.append(value);
    }

int GestType::ExistDb(QString* value)
    {
        for (int i = 0 ; i<this->lista.count();i++)
            {
                if(*value==lista.at(i).nomeDb)
                    return i;
            }
        return -1;
    }

int GestType::FindDbType(QString *db, QString *value)
    {
        int i2 = ExistDb(db);
        if (i2!=-1){
                for (int i = 0 ; i<lista[i2].ListaTipi->count();i++){
                        if (lista[i2].ListaTipi->at(i)==*value)
                            return i;
                    }
            }
        return -1;
    }

GestType::GestType()
    {
        Database = 0;
    }

GestQuery::GestQuery(QString ConstantFile)
    {
        LoadConstantFromFile(ConstantFile);
    }

void GestQuery::AddQuery(Query value)
    {
        lista.append(value);
        if (!loaded) loaded = true;
    }

void GestQuery::Clear()
    {
        lista.clear();
        loaded = false;
    }



void GestQuery::IDeleteQuery(int i)
    {
        if ((i>=0) &&(i<lista.count()))
            lista.removeAt(i);
        if (lista.isEmpty())
            loaded = false;

    }

Query* GestQuery::GetQueryFromConstant(QString constant)
    {
   if (loaded){
   int index = CQuery.indexOf(constant);
   if (index!=-1){
   for (int i = 0 ; i<CQuery.count();i++){
       Query que = lista.at(i);
       Query *rque = &que;
       if (constant==que.GetConstant()) return rque;
       delete rque;
   }
   }
   }
   return NULL;
}
int Query::paramNumber()
    {
        return pNumber;
    }

QString Query::GetConstant()
    {
        return Constant;
    }

QString Query::QueryStr(QStringList pLParamString)
    {
        if (pLParamString.count()!=pNumber)
            return " Number of param is not equal of number of param required.";
        else{
            QString app  ;
            int c  = 0 ;
            int p = 0;
            for ( int i = 0 ; i<QueryString.count();i++)
                    {
                    if (QueryString[i]=='$')
                       c++;
                    else{
                         c =0 ;
                         app.append(QueryString[i]);
                        }
                    if (c==3){
                            app.append(pLParamString.at(p));
                             c =0;
                             p++;
                        }

                    }
                return app;
            }

    }

void Query::SetQueryString(QString value)
    {
        QueryString = value;
        int c = 0 ;
        pNumber = 0;
        for ( int i = 0  ; i< QueryString.count();i++){
                if ( QueryString[i]=='$')
                    c++;
                    if (c==3 ){
                    pNumber++;
                    c = 0;
                    }
            }
    }

Query::Query(QString pQueryString, QString pConstant)
    {
        SetQueryString(pQueryString);
        Constant = pConstant;
    }

bool GestQuery::LoadConstantFromFile(QString value)
    {
        QFile* file = new QFile(value);
        if (!file->open(QFile::ReadOnly))
            return false;
            QTextStream *reader  = new QTextStream(file);
            while (!reader->atEnd()){
                    QString line = reader->readLine();
                    CQuery.append(line);
                }
            file->close();
            return true;
    }

bool GestQuery::LoadQueryFromFile(QString value,QString nDb)
    {
        loaded = false;
        lista.clear();// clear list.
        QFile* file = new QFile(value);// create file .
        if (!file->open(QFile::ReadOnly))// open file in readonly mode .
            return false;// if fail return false.
        QDomDocument *dom = new QDomDocument(); // create the class of xml document
        if (!dom->setContent(file)) { file->close();return false;} // if fail set content close the file e return false.
        QDomElement elem = dom->firstChildElement();// fetch the root  element
        if (elem.tagName() !="QueryList"){file->close(); return false;} // se non inizia per queryList give error.
         QDomNode elem2 = elem.firstChild();// down in the gerarchy.
         while (!elem2.isNull()){
                 QDomElement e = elem2.toElement(); //fetch the element.
                 if (e.nodeValue()==nDb){ // if is the same db fetch all query.
                 QDomNode RDb = e.firstChild(); // down in the gearchy.
                 while (!RDb.isNull()){  // cycle
                         QDomElement ssElement =RDb.toElement();// fetch the element.
                         Query query(e.nodeValue(),e.attribute("Constant")); // read all information
                         lista.append(query); // append in a list.
                         RDb = ssElement.nextSibling(); // go on the cycle.
                     }
                 file->close();// close file .
                 loaded = true;
                 return true;
                 }
                elem2 = e.nextSibling();  // go on the cycle.
             }
         file->close();// close file .
         return false;

}

bool Database::CreateConnection(QString *hostName, QString *dbType, QString *nameDb, QString *user, QString *pass, int port)
{
    QString* number =  new QString(QString::number(cNumb));
     conn = new SConnection(dbType,number);
    LQuery->Clear();
    LQuery->LoadQueryFromFile(Erd_Query_File,*dbType);
    static_cast<SConnection*>(conn)->Connect(*hostName,*user,*pass,*nameDb,port);
    delete number;
}

bool Database::DeleteConnection()
{
     delete conn;
    LQuery->Clear();
}

QSqlQuery*  Database::ExecQuery(QString constant, QStringList *list)
{
    Query *app = this->LQuery->GetQueryFromConstant(constant);
    QString value = app->QueryStr(*list);
    QSqlQuery *query = new QSqlQuery(value);
    return query;
}

bool Database::isConnect()
{
    return ((conn!=NULL)&&(conn->IsConnect()));
}

bool GestType::isEmpty()
{
    return  lista.isEmpty();
}

QString *GestType::getCurrentDatabaseName()
{
    return lista.at(Database).nomeDb;
}

bool GestType::setDatabaseName(QString db)
{
    for (int i = 0;i<lista.count();i++){
        if (lista.at(i).nomeDb==db) {Database = i; return true;}
    }
    return false;
}

bool GestType::setDatabaseNamebyIndex(int value)
{
    if((value>=0) &&(value<lista.count())) Database = value;
    else
        return false;
}

int GestType::CurrentDatabaseIndex()
{
    return Database;
}
