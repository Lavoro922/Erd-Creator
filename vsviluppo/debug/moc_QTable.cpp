/****************************************************************************
** Meta object code from reading C++ file 'QTable.h'
**
** Created: Wed 29. Feb 22:31:30 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QTable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QTable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QLineList[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   11,   10,   10, 0x05,
      79,   62,   10,   10, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QLineList[] = {
    "QLineList\0\0Multiplicity,start\0"
    "DrawStartSimbol(QString*,Node*)\0"
    "Multiplicity,end\0DrawEndSimbol(QString*,Node*)\0"
};

const QMetaObject QLineList::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QLineList,
      qt_meta_data_QLineList, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QLineList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QLineList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QLineList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QLineList))
        return static_cast<void*>(const_cast< QLineList*>(this));
    return QObject::qt_metacast(_clname);
}

int QLineList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: DrawStartSimbol((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< Node*(*)>(_a[2]))); break;
        case 1: DrawEndSimbol((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< Node*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QLineList::DrawStartSimbol(QString * _t1, Node * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QLineList::DrawEndSimbol(QString * _t1, Node * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_QgraphicsItemTable[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,   19,   19,   19, 0x0a,
      72,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QgraphicsItemTable[] = {
    "QgraphicsItemTable\0\0rect,nvalue\0"
    "UpdateRect(QRectF,QRectF)\0DeleteTable()\0"
    "NewAttribute()\0"
};

const QMetaObject QgraphicsItemTable::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QgraphicsItemTable,
      qt_meta_data_QgraphicsItemTable, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QgraphicsItemTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QgraphicsItemTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QgraphicsItemTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QgraphicsItemTable))
        return static_cast<void*>(const_cast< QgraphicsItemTable*>(this));
    if (!strcmp(_clname, "QGraphicsItemResizable"))
        return static_cast< QGraphicsItemResizable*>(const_cast< QgraphicsItemTable*>(this));
    return QObject::qt_metacast(_clname);
}

int QgraphicsItemTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: UpdateRect((*reinterpret_cast< QRectF(*)>(_a[1])),(*reinterpret_cast< QRectF(*)>(_a[2]))); break;
        case 1: DeleteTable(); break;
        case 2: NewAttribute(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QgraphicsItemTable::UpdateRect(QRectF _t1, QRectF _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_QTableManager[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   15,   14,   14, 0x05,
      55,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QTableManager[] = {
    "QTableManager\0\0ch,nodo\0"
    "DrawStartSimbol(QString*,Node*)\0"
    "DrawEndSimbol(QString*,Node*)\0NewTable()\0"
};

const QMetaObject QTableManager::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_QTableManager,
      qt_meta_data_QTableManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QTableManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QTableManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QTableManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTableManager))
        return static_cast<void*>(const_cast< QTableManager*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int QTableManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: DrawStartSimbol((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< Node*(*)>(_a[2]))); break;
        case 1: DrawEndSimbol((*reinterpret_cast< QString*(*)>(_a[1])),(*reinterpret_cast< Node*(*)>(_a[2]))); break;
        case 2: NewTable(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QTableManager::DrawStartSimbol(QString * _t1, Node * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QTableManager::DrawEndSimbol(QString * _t1, Node * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_QAttribute[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QAttribute[] = {
    "QAttribute\0\0DelAttribute()\0"
};

const QMetaObject QAttribute::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QAttribute,
      qt_meta_data_QAttribute, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QAttribute::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QAttribute::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QAttribute::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QAttribute))
        return static_cast<void*>(const_cast< QAttribute*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< QAttribute*>(this));
    return QObject::qt_metacast(_clname);
}

int QAttribute::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: DelAttribute(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
