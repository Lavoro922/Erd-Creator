#ifndef PROJECTDATA_H
#define PROJECTDATA_H
#include<QList>
#include<QColor>
#include<QGraphicsLineItem>
#include<edittext.h>
#include<database.h>
#include<Definition.h>
class Project;
class QDTable;
class QDAttribute;

struct Node{
    void* start;// start table.
    void* end;  // end   table.
    QGraphicsLineItem  *link ; // Link  node .
    QMultiplicity mult;
};

class ProjectData
{
private:
    QList<Project*> ProjectList;
public:
    ProjectData();
};

class Project
{
private:   
    QList<Node*> NodeList;
    QList<QDTable*> TableList;
    GestType* type;
    ProjectData* ref;
    bool CheckUnidirezionalLink(QDTable* tstart,QDTable* tend);
public:
    Project();
    void addTable(QDTable* tab);
    QDTable* getTable(int i );
    int  containsTable(QString value);
    void deleteTable(int i);
    int TableCount();
    bool addNode(Node* node);
    Node* getNode(int i);
    void deleteNodeByIndex(int i);
    void deleteNode(Node* node);
    int NodeCount();
    QStringList*  GetDatabaseList();
    QString GetTypeByInt(int i);
    QString *CurrentDatabaseName();
    int CurrentDatabaseIndex();
    int GetTypeCount();
    int CancelRefer(QDTable* table);
 };

class QDTable
{
private:
    QList<QDAttribute*> AttributeList;
    EditText* Caption; //  Caption
    Project* ref;
public:
    QDTable(Project* pr,QString Caption);
    void SetCaption(QString value );// Setto la caption
    QString *GetCaption();// ottengo la caption della tabella
    void  SetParentList(Project* value);// setta il gestore delle tabelle.
    Project* ParentList();
    void  applyCChar(int value,QString str);
    int   getPosition();
    qreal getStrWidth();
    qreal getStrHeight();
    bool  contains(QString value);
    void addAttribute(QDAttribute* attribute);
    void deleteAttribute(QDAttribute* attribute);
    void deleteAttributeIndex(int i );
    void ClearAttribute();

    QDAttribute* getAttribute(int i );
    int  attributeCount();
    ~QDTable();
};


class QDAttribute
{
private:
    EditText* caption; // nome dell' attributo.
    int  Attribute_type;// tipo dell' attributo
    QTkey  KeyType; //  tipo della chiave ( primaria , esterna indice ... )
    //  ONLY FOR  FOREIGN KEY AND INDEX KEY .
    QDTable* ReferForeignTab;// tabella di riferimento chiave esterna.
    QString* ReferForeignIndex;// attributo di riferimento della tab. di rif  chiave esterna.
    QDTable* ReferIndexTab;// tabella di riferimento chiave indice.
    QString* ReferIndexIndex; // Attributo di riferimento della tabella di rif. chiave indice.
   // END ONLY FOR  FOREIGN KEY AND INDEX KEY .
    QDTable* ref; // riferimento alla lista degli attributi.
    bool isNotValidForeignKey(QTkey KeyType, QDTable *ReferForeignTable, QString *ReferForeignAttribute);
    bool isNotValidIndexKey(QTkey KeyType, QDTable *ReferIndexTable, QString *ReferIndexAttribute);
public:
    QDAttribute(QDTable* ref,QString* Name,int Type,QTkey KeyType,QDTable* ReferForeignTable= NULL ,QString ReferForeignAttribute= "",QDTable* ReferIndexTable= NULL,QString ReferIndexAttribute= "");
    ~QDAttribute();
    // Set
    void SetCaption(QString value); // setta la caption
    void SetAttributeType(int value);//  setta il tipo dell' attributo
    void SetKeyType(QTkey value); // setta il tipo di chiave
    void SetReferForeignTab(QDTable* Value); // setta il nome della tabella dell' attributo.
    void SetReferForeignIndex(QString* Value); // setta gli attributi della chiave esterna
    void SetIndexTab(QDTable *Value); // setta la tabella dell' index
    void SetIndexLindex(QString* value); // setta l' attributi dell' index
    QString Caption(); // setta la caption
    qreal getCaptionWidth();
    qreal getCaptionHeight();
    QTkey GetKeyType();
    int     GetattributeType();
    QString GetattributeTypeStr();
    QDTable* GetReferForeignTab(); // setta il nome della tabella dell' attributo.
    QString* GetReferForeignIndex(); // setta gli attributi della chiave esterna
    QDTable* GetIndexTab(); // setta la tabella dell' index
    QString* GetIndexLindex(); // setta l' attributi dell' index
    void applyOneChar(int value, QString str);
    void NextKeyType();
    void PrevKeyType();
};
#endif // PROJECTDATA_H
