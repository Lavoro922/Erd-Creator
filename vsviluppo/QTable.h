#ifndef QGRAPHICSITEMTABLE_H
#define QGRAPHICSITEMTABLE_H

#include<QMessageBox>
#include <QApplication>
#include <QGraphicsItem>
#include<QGraphicsSceneMouseEvent>
#include <QRectF>
#include<qpainter.h>
#include <QInputDialog>
#include <QGraphicsWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include<QGraphicsScene>
#include<QMenu>
#include<QDebug>
#include<QList>
#include<QTextItem>
#include<QObject>
#include<QGraphicsProxyWidget>
#include <QFile>
#include <QDir>
#include <QErrorMessage>
#include<database.h>
#include<Exception/listisempty.h>
#include<projectdata.h>

class QgraphicsItemTable;
class QAttribute;
const  int attribute_width=50;// larghezza attributo.
class Grabber{
private:
    QGraphicsItem* gItem;
    int ItemDevices;
public:
    Grabber();
    void EnableGrabber(QGraphicsItem* grabber,int device);
    void DisableGrabber();
    bool isEnableGrabber();
    QGraphicsItem* GrabberItem();
    int GrabberDeviceItem();
};
/**
  * this class manage list of db type .
  * Default class:
  *
  */


class QTableManager;
class QGraphicsItemResizable : public QGraphicsItem
{
private:
    QPointF first;// posizione iniziale di riferimento
    QColor SColor,BColor; // Select Color and Background Color.
    qreal lrx,lry,lrw,lrh; //  limiti  dimensione del rettangolo
         // margini
    bool isnear(QPointF value); // serve per vedere se un punto è   in fondo al rect.
public:
   virtual  void change(qreal x,qreal y, qreal w,qreal h);// cambia le dimensioni
    QGraphicsItemResizable(qreal x,qreal y,qreal width,qreal height,QColor back = Qt::white,QColor select = Qt::red); // costruttore
    void SetColorSelected(QColor color);// setto il colore quand'� selezionato.
    QColor ColorSelected();// colore selezionato.
    void   SetColor(QColor color);// setto il colore
    QColor Color();// ottengo il colore
    void Setlimit(qreal x ,qreal y ,qreal w,qreal h); // setto i limiti
    void SetMargin(qreal x, qreal y, qreal w,qreal h);// setto i margini .
    bool isResizing();
    bool isSelected();
    QRectF boundingRect () const;// funzione che serve per restituire le dimensioni del rettangolo (QrectF)
protected:
    qreal mx,my,mw,mh; //margini
    qreal rx,ry,rw,rh; // dimensione del rettangolo
    bool isResize;  // se è in fase di resize
    bool ispressed; // se è stato premuto
    bool select;    // se è stato selezionato
    void mousePressEvent(QGraphicsSceneMouseEvent *event); // se il mouse è premuto
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);// se il mouse è in movimento
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);// se il mouse viene rilasciato
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);// evento di paint
};

class QgraphicsItemTable : public QObject,public QGraphicsItemResizable
{
Q_OBJECT
private:
    QList<QAttribute*> attributelist;
    QGraphicsTextItem *text;// oggetto per la gestione del testo
    QMenu *menu; // menu per gestire l' eliminazione della tabella.
    Grabber* grabRefer;
    QDTable* TableData;
    QTableManager* VisRef;
public:
    QgraphicsItemTable(QTableManager* VisualRef ,QDTable* table,qreal x, qreal y, qreal width, qreal height,Grabber* grab, QColor back =Qt::white, QColor select =Qt::red); // costruttore .
    QTableManager* GetParentList();// ritorno il gestore delle tabelle.
    ~QgraphicsItemTable(); // ridefinisco il distruttore della tabella.
    // metodi Get
    bool canAddAttribute();
    qreal x();//restituisco la x della tabella .
    qreal y();//restituisco la y della tabella .
    qreal width(); //restituisco la width della tabella .
    qreal height();//restituisco la height della tabella.
    qreal Ay(); // restituisce la y da dove partono gli attributi.
    qreal Amx(); // restituisce la x massima .
    QString *GetCaption();
    void     SetCaption(QString value);
    QRectF  GetInternalRect();// ottengo il rettangolo in mezzo
    QRectF  GetRightRect(); // Rectangle where i need to move every line if i resize the Rect
    QRectF  GetDownRect(); // Rectangle where i need to move every line if i resize the Rect
    QRectF  GetUpRect();
    QRectF  GetLeftRect();
    Grabber* GetgrabRefer();
    void addAttribute(QString caption,int type);
    void removeAttribute(QAttribute* attr);
    int attributeCount();
    void ClearAttribute();
    void AttributeRepaint();
    // Metodi Set
    void SetX(qreal x);// setto la x della tabella.
    void SetY(qreal y);//setto la y della tabella.
    void SetWidth(qreal width);//setto la width della tabella.
    void SetHeight(qreal height);//setto la height della tabella.
    // Generic Method.
    void change(qreal x, qreal y, qreal w, qreal h);// setto tutto (consigliato)
    void SetParentList(QTableManager *value);
    void DeselectAll();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);// metodo di paint
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);//metodo di doubleclick
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);// metodo che viene richiamato quando si muove il mouse
    void mousePressEvent(QGraphicsSceneMouseEvent *event);// metodo che viene richiamato quando si preme il mouse
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);// metodo che viene richiamato al rilascio del mouse,
    void keyPressEvent(QKeyEvent *event); // metodo che viene chiamato quando premi un pulsante
public slots:
    void DeleteTable(); // slot  che viene attivato quando si clicca su DeleteTable.
    void NewAttribute(); // slot che viene attivato quando si clicca su Nuovo Attributo.
signals:
    void UpdateRect(QRectF rect,QRectF nvalue); // segnale al movimento della tabella.
};

class QTableManager : public QGraphicsView
{
    Q_OBJECT
private:
    Grabber grab;
    QMenu *men;// popup menu.
    QGraphicsScene *scene;// scene
    QList<QgraphicsItemTable*> ListofTable;
    Project* ProjectData;
    Node* nodo;
    int ReservedValue;
    qreal calcolaMedia(qreal pos,qreal start, qreal end);
    qreal calcolaPos(qreal Media,qreal start, qreal end);
public:
    explicit QTableManager(QWidget *parent = 0);//  costruttore
    Grabber* getGrabber();
    // Setta Reserved value
    void SetReservedValue(int value);
    QGraphicsScene* GraphicsScene();
    // Tabelle.
    QgraphicsItemTable *addTable(QString* caption,qreal x, qreal y,qreal width ,qreal height);
    QgraphicsItemTable* getTable(int i );
    bool deleteTable(QString caption);
    int  TableCount();
    // Collegamento
    void StartLink(QgraphicsItemTable* table,QPointF* point);
    bool isStartLink();
    void CloseLink(QgraphicsItemTable* table);
   // restituisce l'inizio e la linea del collegamento.
    QgraphicsItemTable* GetStartNode();
    QGraphicsLineItem* GetLineNode();
    // Muovere la linea.
     void Update(QgraphicsItemTable *table, qreal Vx,qreal Vy);
    void EUpdate(QgraphicsItemTable *table, qreal Vx, qreal Vy);
    // Muovere la linea .
    void MoveLinkStart(QPointF pos);
    void MoveLineEnd(QPointF pos);
    int GetTableByPoint(QPointF value, QgraphicsItemTable *obj);
    int GetBTableByPoint(QPointF value, QgraphicsItemTable *obj);
    QList<Node *> *GetTableLinked(QGraphicsItemResizable *value);
    QList<Node *> *GetTableLinkEnd(QGraphicsItemResizable *value);
    void deleteNode(int i);
    int TableExist(QString name);
    QList<Node *> *GetTableStart(QGraphicsItemResizable *value);
    void CancelRefer(QgraphicsItemTable *table);
public slots:
   void NewTable();// nuova tabella .
protected:
    void  mousePressEvent(QMouseEvent *event);// definisco l' evento alla pressione .
    void mouseReleaseEvent(QMouseEvent *event);// definisco l' evento di rilascio.
    void mouseMoveEvent(QMouseEvent *event);
signals:
    void DrawStartSimbol(QString* ch,Node*nodo);
    void DrawEndSimbol(QString* ch,Node*nodo);
};

class QAttribute :public QObject,public QGraphicsItem{
Q_OBJECT
private:
    // POSITION OF ATTRIBUTE.
    qreal x;// avanzamento x
    qreal y;// avanzamento y
    qreal w;// larghezza
    qreal h;// altezza
    //  END POSITION OF ATTRIBUTE.
    Grabber* grabRefer; // riferimento per capire chi ha il cursore.
    bool selct;// se � selezionato o meno.
    // Interaction menu.
    QMenu *menu;// popup menu.
    QDAttribute* attribute;
    QgraphicsItemTable* ref;
    public:
    // Costruttore
    QAttribute(QgraphicsItemTable* tab, QDAttribute* list,Grabber* grab); // costruttore .
    // metodi Set

    void SetAvX(qreal value); // setta la x dell' attributo
    void SetAvY(qreal value );// setta la y dell' attributo
    void SetWidth(qreal value ); // setta la larghezza dell' attributo
    void SetHeight(qreal value ); //setta l' altezza dell' attributo.
    void setSelected(bool selected);

    qreal Width()  const; // ottengo la larghezza
    qreal Height() const; // ottengo l' altezza
    qreal AvX()    const ; // ottengo la x
    qreal AvY()    const; // ottengo la y
    bool select();// restituisce se � selezionato o meno.
    void Repaint(); // ridisegno
    QRectF* GetRectangle() const ;// restituisce il rettangolo del tipo.
    QRectF* GetTextRectangle() const ;// restituisce il rettangolo del nome del testo.
    Grabber* GetGrabber();
    virtual QRectF boundingRect() const;// restituisce il rettangolo dell' attributo.
    QTkey ColorToTkey(QColor value);
    QColor TkeyToColor(QTkey value);
    void SetColorNormalKey(QColor value);
    void SetColorPrimaryKey(QColor value);
    void SetColorForeignKey(QColor value);//
    void SetColorIndexKey(QColor value);
    void SetColorKeyPrimaryForeign(QColor value);//
    void SetColorPrimaryAndIndexKey(QColor value);
    void SetColorForeignIndexKey(QColor value);//
protected:
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);// metodo di disegno
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);// metodo di movimento del mouse.
   void mousePressEvent(QGraphicsSceneMouseEvent *event);// metodo di pressione del mouse.
   void keyPressEvent(QKeyEvent *event);
public slots:
   void DelAttribute(); // cancella attributo .
};

#endif // QGRAPHICSITEMTABLE_H
