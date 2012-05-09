#include "projectdata.h"

ProjectData::ProjectData()
{

}

bool Project::CheckUnidirezionalLink(QDTable *tstart, QDTable *tend)
{
    for (int i = 0 ;i<=NodeCount()-1;i++){
        if ((tstart==static_cast<QDTable*>(getNode(i)->end)) &&(tend==static_cast<QDTable*>(getNode(i)->start)))
            return false;
    }
    return true;
}

Project::Project()
{
    NodeList = QList<Node*>();
    TableList = QList<QDTable*>();
    type = new GestType();
    type->LoadFromFile(new QString("conf/type.dat"));
    qDebug()<<type->ListDb()->count(); // is empty -.-'
  // ref da assegnare .
}

void Project::addTable(QDTable *tab)
{
    if (tab==NULL) throw new invalid_argument("Table is null.");
    TableList.append(tab);
}

QDTable *Project::getTable(int i)
{
    if (i<0 || i>TableList.count()-1) throw invalid_argument("GetTable allows only value >0 and <=count-1");
    return TableList.at(i);
}

int Project::containsTable(QString value)
{
    for (int i = 0;i<TableList.count();i++){
        if (TableList.at(i)->GetCaption()==value) return i;
    }
    return -1;
}

void Project::deleteTable(int i )
{
    TableList.removeAt(i);
}

int Project::TableCount()
{
    return TableList.count();
}

bool Project::addNode(Node *node)
{
    if(CheckUnidirezionalLink(static_cast<QDTable*>(node->start),static_cast<QDTable*>(node->end)))
    {
        NodeList.append(node);
        return true;
     }
      return false;

}

Node *Project::getNode(int i)
{
    return NodeList.at(i);
}

void Project::deleteNodeByIndex(int i)
{
    NodeList.removeAt(i);
}

int Project::NodeCount()
{
    return NodeList.count();
}

QStringList *Project::GetDatabaseList()
{
    return  type->ListDb();
}

QString Project::GetTypeByInt(int i)
{
    return type->ListDbType(CurrentDatabaseName())->at(i);
}





void QDAttribute::SetCaption(QString value)
{
    if (value.trimmed()=="") throw new invalid_argument("Attribute cannot accept Empty String as Name.");
    int i = 0;
    if(ref->contains(value)){
    while (ref->contains(value+QString::number(i)))i++;
    value +=QString::number(i);
    }
    caption->setValue(value);
}

void QDAttribute::SetAttributeType(int value)
{
    if (value<0 || value>=ref->ParentList()->GetTypeCount() ) throw new invalid_argument("Type must included between >0 and <TypeCount()-1");
    Attribute_type = value;
}

void QDAttribute::SetKeyType(QTkey value)
{
    KeyType = value;
}

QDTable *QDAttribute::GetReferForeignTab()
{
    return ReferForeignTab;
}

QString *QDAttribute::GetReferForeignIndex()
{
    return ReferForeignIndex;
}

QDTable *QDAttribute::GetIndexTab()
{
    return ReferIndexTab;
}

QString *QDAttribute::GetIndexLindex()
{
    return ReferIndexIndex;
}

void QDAttribute::applyOneChar(int value,QString str)
{
    caption->applyChar(value,str);
}

void QDAttribute::NextKeyType()
{
    if (static_cast<int>(KeyType)==6)
    KeyType = static_cast<QTkey>(0);
    else
    KeyType =static_cast<QTkey>(static_cast<int>(KeyType)+1);
}

void QDAttribute::PrevKeyType()
{
    if (static_cast<int>(KeyType)!=0)
    KeyType =static_cast<QTkey>(static_cast<int>(KeyType)-1);
}

void QDAttribute::SetReferForeignTab(QDTable *Value)
{
    if (!isNotValidForeignKey(static_cast<QTkey>(this->Attribute_type),Value,ReferForeignIndex))
    ReferForeignTab = Value;
}

void QDAttribute::SetReferForeignIndex(QString *Value)
{
    if (!isNotValidForeignKey(static_cast<QTkey>(this->Attribute_type),ReferForeignTab,Value))
    ReferForeignIndex = Value;
}

void QDAttribute::SetIndexTab(QDTable *Value)
{
    if (!isNotValidIndexKey(static_cast<QTkey>(this->Attribute_type),Value,ReferIndexIndex))
    ReferIndexTab = Value;
}

void QDAttribute::SetIndexLindex(QString *value)
{
    if (!isNotValidIndexKey(static_cast<QTkey>(this->Attribute_type),ReferIndexTab,value))
        ReferIndexIndex = value;
}

QString QDAttribute::Caption()
{
    return caption->getValue();
}

qreal QDAttribute::getCaptionWidth()
{
    return caption->getStrWidth();
}

qreal QDAttribute::getCaptionHeight()
{
    return caption->getStrHeight();
}


QDTable::QDTable(Project *pr, QString Caption)
{
    ref = pr;
    this->Caption = new EditText(Caption);
}

void QDTable::SetCaption(QString value)
{

    Caption->setValue(value);
}

QString *QDTable::GetCaption()
{
    return new QString(Caption->getValue());
}

void QDTable::SetParentList(Project *value)
{
    ref = value;
}

Project *QDTable::ParentList()
{
    return ref;
}

void QDTable::applyCChar(int value, QString str)
{
    Caption->applyChar(value,str);
}



bool QDAttribute::isNotValidForeignKey(QTkey KeyType,QDTable* ReferForeignTable,QString* ReferForeignAttribute)
{
    if (KeyType==KeyForeign ||KeyType==KeyForeignIndex || KeyType==KeyPrimaryForeign )
        return (ReferForeignTable==NULL|| *ReferForeignAttribute=="");
    return true;
}

bool QDAttribute::isNotValidIndexKey(QTkey KeyType, QDTable *ReferIndexTable, QString *ReferIndexAttribute)
{
    if (KeyType==KeyIndex ||KeyType==KeyForeignIndex || KeyType==KeyPrimaryIndex )
        return (ReferIndexTable==NULL|| *ReferIndexAttribute=="");
        return true;
}

QDAttribute::QDAttribute(QDTable *ref, QString *Name, int Type, QTkey KeyType, QDTable* ReferForeignTable, QString ReferForeignAttribute, QDTable* ReferIndexTable, QString ReferIndexAttribute)
{
    caption  = new EditText();

    if (ref==NULL) throw new invalid_argument("Ref is null.");
    if (Name==NULL) throw new invalid_argument("Name is null.");
    this->ref = ref;
    this->SetAttributeType(Type);
    this->SetReferForeignTab(ReferForeignTable);
    this->SetReferForeignIndex(&ReferForeignAttribute);
    this->SetIndexTab(ReferIndexTable);
    this->SetIndexLindex(&ReferIndexAttribute);
    SetCaption(*Name);
}

QDAttribute::~QDAttribute()
{
    delete caption;
}

int Project::GetTypeCount()
{
    return type->ListDb()->count();
}



QTkey QDAttribute::GetKeyType()
{
    return KeyType;
}

int QDAttribute::GetattributeType()
{
    return Attribute_type;
}

QString QDAttribute::GetattributeTypeStr()
{
    return ref->ParentList()->GetTypeByInt(Attribute_type);
}

bool QDTable::contains(QString value)
{
    for (int i = 0 ;i<AttributeList.count();i++){
        if (AttributeList.at(i)->Caption()==value) return true;
    }
    return false;
}

void QDTable::addAttribute(QDAttribute *attribute)
{
    AttributeList.append(attribute);
}

void QDTable::deleteAttribute(QDAttribute *attribute)
{
    AttributeList.removeOne(attribute);
}

void QDTable::deleteAttributeIndex(int i)
{
    if (i>=0 && i<AttributeList.count())
        deleteAttribute(AttributeList.at(i));
}

void QDTable::ClearAttribute()
{
    AttributeList.clear();
}

QDAttribute *QDTable::getAttribute(int i)
{
    return AttributeList.at(i);
}

int QDTable::attributeCount()
{
    return AttributeList.count();
}

QDTable::~QDTable()
{
    AttributeList.clear();
    delete Caption;
}

QString* Project::CurrentDatabaseName()
{
    return type->getCurrentDatabaseName();
}

int Project::CurrentDatabaseIndex()
{
    return   type->CurrentDatabaseIndex();
}

qreal QDTable::getStrWidth()
{
    return Caption->getStrWidth();
}

qreal QDTable::getStrHeight()
{
    return Caption->getStrHeight();
}

void Project::deleteNode(Node *node)
{
    NodeList.removeOne(node);
}



