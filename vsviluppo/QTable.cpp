#include "QTable.h"
QColor sColor[6];

QGraphicsItemResizable::QGraphicsItemResizable(qreal x,qreal y,qreal w,qreal h,QColor back ,QColor select)
    {

        change(x,y,w,h);// setto le dimensione del rettangolo

        SetColor(back);// setto il colore di sfondo
        SetColorSelected(select);// setto il colore del rettangolo selezionato
        lrx = 0;// disabilito i limiti x,y,w,h
        lry = 0;
        lrw = 0;
        lrh = 0;
        this->select = false;//setto il flag di selezione .
    }


void QGraphicsItemResizable::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

        QRectF bord = boundingRect();// prendo la dimensione
        bord.setTop(bord.top()-my);
        bord.setLeft(bord.left()-mx);
        bord.setWidth(bord.width()-mw);
        bord.setHeight(bord.height()-mh);

        QRect  rect(bord.left()+5,bord.top()+5,bord.width()-10,bord.height()-10);// dimensione rettangolo selezionato

        painter->fillRect(bord,QBrush(BColor));// disegno il rettangolo di contorno
        painter->drawRect(bord);
        if (select){ // se è selezionato disegno
                QPen pen;// nuovo Qpen
                QPen pr =  painter->pen();// mi salvo il pen attuale
                pen.setColor(SColor); // setto il colore del pen nuovo
                pen.setStyle(Qt::DashDotLine);// metto il tratteggio al pen
                painter->setPen(pen);// setto il nuovo pen
                painter->drawRect(rect);  // disegno il rettangolo selezionato
                painter->setPen(pr);// ripristino il pen
            }




    }

void QGraphicsItemResizable::mousePressEvent(QGraphicsSceneMouseEvent *event)

    {

        ispressed = true;

        if (select)
            select = false;
        else
            select = true;
        if (select)
        grabKeyboard();
        else
        ungrabKeyboard();
        first = event->scenePos();// prendo la posizione
        isResize = isnear(first);// vedo se è in basso a destra
        if  (isResize)
            QApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));// setto il cursore di resize
        else
            QApplication::setOverrideCursor(QCursor(Qt::DragMoveCursor));// setto il cursore  di spostamento
        prepareGeometryChange();
        update(boundingRect());
    }


void QGraphicsItemResizable::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        if (ispressed){
                if (isResize) {// se è in basso a destra quindi in modalita resize
                        qreal incx =  event->scenePos().x()-first.x();// calcolo le posizioni
                        qreal incy =  event->scenePos().y()-first.y();//
                        if ((rw+incx>=10)&& (rh+incy>=10))// se queste posizioni sommate alla larg e alte è maggiore uguale di 10.
                            change(rx,ry,rw+incx,rh+incy);// attuo la modifica
                        first = event->scenePos();// prendo la posizione di riferimento
                    }
                else
                    {// se non è in resize mode allora è in move mode
                        rx =  rx+(event->scenePos().x()-first.x());// calcolo la coordinata x
                        ry =ry +(event->scenePos().y()-first.y());// calcolo la coordinata y
                        change(rx,ry,rw,rh);// setto le nuove coordinate
                        first = event->scenePos();// prendo la posizione di riferimento
                    }

            }

    }

void QGraphicsItemResizable::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {

        ispressed= false;
        isResize = false;// disabilito la resize mode in ogni caso
        QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));

    }

QRectF QGraphicsItemResizable::boundingRect() const
    {
        return QRectF(rx,ry,rw,rh); // restituisco il rettangolo
    }

bool QGraphicsItemResizable::isnear(QPointF value)
    {
        const int diff =  40;// costante di margine
        return ( (rx+rw-diff<=value.x())  && (rh+ry-diff<=value.y()));// vedo se è nell' intorno
    }
void QGraphicsItemResizable::change(qreal x,qreal y, qreal w,qreal h){

    prepareGeometryChange();// preparo il qgraphicsitem al cambio
        // controlli per vedere se rientra in un eventuale limite

        if((lrx==0)||(x<lrx))  this->rx = x; // setto le nuove coordinate x,y,w,h
        if ((lry==0)||(y<lry))  this->ry = y;
        if ((lrw==0)||(w<lrw))  this->rw= w;
        if ((lrh==0)||(h<lrh))  this->rh= h;
        update(x,y,w,h);// e infine faccio l' aggiornamento .
    }

void QGraphicsItemResizable::SetColor(QColor color)
    {
        BColor = color;
    }

QColor QGraphicsItemResizable::Color()
    {
        return BColor;
    }

void QGraphicsItemResizable::SetColorSelected(QColor color)
    {
        SColor = color;
    }

QColor QGraphicsItemResizable::ColorSelected()
    {
        return SColor;
    }

void QGraphicsItemResizable::Setlimit(qreal x, qreal y, qreal w, qreal h)
    {
        lrx = x;// setta limite x  se è 0 il limite non è attivo
        lry = y;// setta limite y
        lrw = w;// setta limite width
        lrh = h;// setta limite height
    }

void QGraphicsItemResizable::SetMargin(qreal x, qreal y, qreal w, qreal h)
    {
        mx = x;
        my = y;
        mw = w;
        mh =h;
    }

QgraphicsItemTable::QgraphicsItemTable(QTableManager* visualRef,QDTable* table,qreal x, qreal y, qreal width, qreal height,Grabber* grab,QColor back, QColor select)
    :QGraphicsItemResizable(x,y,width, height, back, select)
    {
        VisRef = visualRef;
        TableData = table;
        SetMargin(-10,-10,15,15);
        menu = new QMenu(0);

        grabRefer = grab; // setto il grabber .
        QAction *AddAtr =   menu->addAction("Nuovo attributo");
        QAction *act = menu->addAction("Cancella la tabella ");
        connect(act,SIGNAL(triggered()),this,SLOT(DeleteTable()));
        connect(AddAtr,SIGNAL(triggered()),this,SLOT(NewAttribute()));
    }

void QgraphicsItemTable::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)

    {

        QGraphicsItemResizable::paint(painter,option,widget);
        QPen pen;
        pen.setStyle(Qt::DashDotLine);
        QPen def = painter->pen();
        painter->setPen(pen);
        painter->drawRect(boundingRect());
        painter->setPen(def);
        QRectF bord = boundingRect();
        bord.setTop(bord.top()-my);
        bord.setLeft(bord.left()-mx);
        bord.setWidth(bord.width()-mw);
        bord.setHeight(bord.height()-mh);
        QRectF *bord2 = new QRectF();
        def.setColor(Qt::white);
        painter->setPen(def);
        painter->drawText(bord,Qt::AlignCenter,*(TableData->GetCaption()),bord2);
        qreal px = bord2->left()+TableData->getStrWidth();
        qreal py = bord2->top()+TableData->getStrHeight();
        bord2->setTop(bord2->top()-5);
        bord2->setHeight(bord2->height()+5);
        bord2->setLeft(bord2->left()-5);
        bord2->setWidth(bord2->width()+5);
        painter->fillRect(*bord2,QColor(128,128,128,100));
        painter->drawText(bord,Qt::AlignCenter,*(TableData->GetCaption()),bord2);
        if (GetgrabRefer()->GrabberItem()==this) painter->drawLine(px,py,px+5,py);

}

void QgraphicsItemTable::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
    AttributeRepaint();

    // alist->Repaint();

    QPointF value = event->pos();

        if (VisRef->isStartLink()){ // se il collegamento � iniziato
            VisRef->MoveLineEnd(value);
                //  QGraphicsItemResizable::mouseMoveEvent(event);
            }
        else {
                if (!isResize){
                        // sposto
                        int Vx =this->x();
                        int Vy =this->y();

                        QGraphicsItemResizable::mouseMoveEvent(event);
                        Vx = this->x()-Vx;
                        Vy = this->y()-Vy;
                        VisRef->Update(this,Vx,Vy);
                    }
                else{// fase di resize.
                        int Vw = this->width();
                        int Vh = this->height();
                        QGraphicsItemResizable::mouseMoveEvent(event);
                        Vw = this->width()-Vw;
                        Vh = this->height()-Vh;
                        VisRef->EUpdate(this,Vw,Vh);
                    }
            }

    }

void QgraphicsItemTable::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
    {
        QInputDialog *dialog = new QInputDialog(QApplication::topLevelWidgets()[0],Qt::Window);// creo la form di dialogo
        dialog->setLabelText("Inserisci il nome della tabella ");
        if (dialog->exec()==1){// la visualizzo e vedo se ha premuto ok
                QString  value = dialog->textValue();
                TableData->SetCaption(value);
            }
    }

QString *QgraphicsItemTable::GetCaption()
    {
        return (TableData->GetCaption());
    }

void QgraphicsItemTable::SetCaption(QString value)
    {
    TableData->SetCaption(value);

    }
void QgraphicsItemTable::mousePressEvent(QGraphicsSceneMouseEvent *event)
    {

        if (event->button()==Qt::RightButton){ // if press rightbutton
                  VisRef->SetReservedValue(4);
                QPointF value =  mapToScene(event->lastScreenPos().x(),event->lastScreenPos().y());
                menu->popup(value.toPoint());
            }
        else
            { // if press leftbutton.

                QPointF value= mapToScene(event->lastScenePos().x(),event->lastScenePos().y());// prendo la posizione .
                if (GetInternalRect().contains(value)){// vedo se � contenuta nel rettangolo interno.
                    QGraphicsItemResizable::mousePressEvent(event);
                    if (isSelected()){ // se � selezionato.
                        grabRefer->EnableGrabber(this,0); // attivo il grabber.
                    }
                    else
                        grabRefer->DisableGrabber();// disabilito.
                }
                else{
                        VisRef->StartLink(this,&value);
                    }

            }

    }



QRectF QgraphicsItemTable::GetInternalRect()
    {
        QRectF bord = boundingRect();// prendo la dimensione
        bord.setTop(bord.top()-my);
        bord.setLeft(bord.left()-mx);
        bord.setWidth(bord.width()-mw);
        bord.setHeight(bord.height()-mh);
        return bord;

    }

void QgraphicsItemTable::SetParentList(QTableManager *value)
    {
        VisRef = value;
    }



void QgraphicsItemTable::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsItemResizable::mouseReleaseEvent(event);

        // definire se quando lascio il mouse lo lascio sopra fuori o meno.
        int value = VisRef->GetBTableByPoint(mapToScene(event->pos()),this);
        if (value!=-1)
            VisRef->CloseLink(VisRef->getTable(value));
        else
            VisRef->CloseLink(NULL);
}

void QgraphicsItemTable::keyPressEvent(QKeyEvent *event)
{
    if(GetgrabRefer()->GrabberItem()==this){
        TableData->applyCChar(event->key(),event->text());
        this->update();
    }
}





void QTableManager::mousePressEvent(QMouseEvent *event)
    {
        ReservedValue =1;
        QGraphicsView::mousePressEvent(event);
        if ((event->button()==Qt::RightButton)&&(ReservedValue==1)){
                men->popup(event->globalPos());// richiamo il menu
            }


    }

void QTableManager::NewTable()
    {
        // creo la tabella
    QPointF value = this->mapToScene(QCursor::pos());

    QgraphicsItemTable* table = addTable(new QString("NuovaTab"),value.x(),value.y(),250,100);
    table->addAttribute("id",0);
}

QTableManager::QTableManager(QWidget *parent)
    {
        scene =  new QGraphicsScene(this);
        setScene(scene);
        ProjectData= new  Project();
        this->
        men = new QMenu(this);
        men->addAction("Nuova Tabella");
        grab =  Grabber();
        connect(men,SIGNAL(triggered(QAction*)),this,SLOT(NewTable()));
        ReservedValue = 0;
        nodo = new Node();
        nodo->end = NULL;
        nodo->start = NULL;
        nodo->link = NULL;

    }

QTableManager * QgraphicsItemTable::GetParentList()
    {
        return VisRef;
    }

void QTableManager::mouseReleaseEvent(QMouseEvent *event)
    {
    QGraphicsView::mouseReleaseEvent(event);
}








//Line list
//Implementation .
void QTableManager::MoveLinkStart(QPointF pos)
    {
        if (isStartLink()){
                nodo->link->setLine(pos.x(),pos.y(),nodo->link->line().x2(),nodo->link->line().y2());
                QString *ch = new QString((nodo->mult==OnetoN||nodo->mult==OneToOne)?"1":"N");
                emit DrawStartSimbol(ch,nodo);
            }
    }

void QTableManager::MoveLineEnd(QPointF pos)
    {
        if (isStartLink()){
                nodo->link->setLine(nodo->link->line().x1(),nodo->link->line().y1(),pos.x(),pos.y());
                QString  *ch = new QString((nodo->mult==NtoOne)?"1":"N");
                emit DrawEndSimbol(ch,nodo);
            }
    }




void QAttribute::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        // Rettangolo

        if (selct)// se selezionato allora .
            painter->fillRect(boundingRect(),QColor(255,19,0,125)); // riempo tutto il rettangolo di rosso.
        QRectF Rect = boundingRect();// ottengo  il rettangolo
        qreal bx =(Rect.width()/6)+(Rect.width()/8);
        qreal by =(Rect.height()*(80))/100 ;
        qreal ox =(Rect.left()+Rect.width()/2.8);
        qreal oy =Rect.topLeft().y()+Rect.height()-by ;
        painter->fillRect(ox+1,oy+11,bx-1,by-12,Qt::white);
        // Testo
        QRectF *typetext = new  QRectF();
        painter->drawText(QRectF(Rect.x(),oy-25,Rect.width(),30),Qt::AlignCenter,attribute->Caption(),typetext);
        qreal px = typetext->left()+this->attribute->getCaptionWidth();
        qreal py = typetext->top()+this->attribute->getCaptionHeight();
        typetext->translate(20,typetext->height()+1);
        typetext->setLeft(Rect.x()+16);

        painter->drawText(*typetext,attribute->GetattributeTypeStr(),QTextOption(Qt::AlignVCenter));

        painter->drawRect(ox,oy+10,bx,by-11);
        if (this->grabRefer->GrabberItem()==this)
        painter->drawLine(px,py,px+5,py);
        // inserire tipo ....
// draw right and left arrow that permit to change type.
    }

qreal QAttribute::AvX()const
    {
        return x;
    }

qreal QAttribute::AvY() const
    {
        return y;
    }

qreal QAttribute::Height() const
    {
        return h;
    }

qreal QAttribute::Width()const
    {
        return w;
    }

void QAttribute::SetAvX(qreal value)
    {
        x= value;
        Repaint();
    }



void QAttribute::SetWidth(qreal value)
    {
    w = value;
}

void QAttribute::SetHeight(qreal value)
{
   h = value;
}

void QAttribute::SetAvY(qreal value)
    {
        y=value;

    }








int QTableManager::GetTableByPoint(QPointF value,QgraphicsItemTable  *obj)
    {
        for (int i = 0;i<=TableCount()-1;i++){
                if ((obj!=getTable(i))&&(getTable(i)->GetInternalRect().contains(value))){
                        return i;
                    }
            }
        return -1;
}

int QTableManager::GetBTableByPoint(QPointF value, QgraphicsItemTable *obj)
{
    for (int i = 0;i<=TableCount()-1;i++){
            if ((obj!=getTable(i))&&(!getTable(i)->GetInternalRect().contains(value) && getTable(i)->boundingRect().contains(value) )){
                    return i;
                }
        }
    return -1;
}

QList<Node*>* QTableManager::GetTableStart(QGraphicsItemResizable* value)
    {
        QList<Node*> *list;
        list = new QList<Node*>();
        for (int i = 0 ;i<=ProjectData->NodeCount();i++){
                if ((ProjectData->getNode(i)->start==value))
                    list->append(ProjectData->getNode(i));

            }
        return list;
}

void QTableManager::CancelRefer(QgraphicsItemTable *table)
{

        QList<Node*> list = QList<Node*>();
        for (int i = 0 ; i<ProjectData->NodeCount();i++){
            if ((table==ProjectData->getNode(i)->start)|| ( table==ProjectData->getNode(i)->end))
                list.append(ProjectData->getNode(i));
        }
        for (int i= 0;i<list.count();i++){
            delete list[i]->link;
            ProjectData->deleteNode(list[i]);
        }

}

int QTableManager::TableExist(QString name)
    {
        for (int i = 0 ;i<=TableCount()-1;i++){
                if (ProjectData->getTable(i)->GetCaption()==name)
                    return i;
            }
        return -1;
}

Grabber *QTableManager::getGrabber()
{
    return &this->grab;
}

void QTableManager::SetReservedValue(int value)
{
    ReservedValue = value;
}

QGraphicsScene *QTableManager::GraphicsScene()
{
   return scene;
}

QgraphicsItemTable* QTableManager::addTable(QString *caption, qreal x, qreal y, qreal width, qreal height)
{
    QDTable* table = new QDTable(ProjectData,*caption);
    ProjectData->addTable(table);
    QgraphicsItemTable* vtable = new QgraphicsItemTable(this,table,x,y,width,height,&grab);
    scene->addItem(vtable);
    vtable->change(x,y,width,height);
    ListofTable.append(vtable);
    return vtable;
}

QgraphicsItemTable *QTableManager::getTable(int i)
{
    return ListofTable.at(i);
}

bool QTableManager::deleteTable(QString caption)
{
    int pos = ProjectData->containsTable(caption);
    if (pos==-1) return false;
    ListofTable.removeAt(pos);
    ProjectData->deleteTable(pos);
    return true;
}

int QTableManager::TableCount()
{
    return ListofTable.count();
}
/**
  Comincia il nodo con la tabella table.
  */
void QTableManager::StartLink(QgraphicsItemTable *table,QPointF* point)
{
    if(table==NULL) throw new invalid_argument("Null exception");
    QGraphicsLineItem * line = scene->addLine(point->x()-4,point->y(),point->x()+3,point->y());
    nodo->start =table;
    nodo->link = line;
    nodo->end = NULL;
    MoveLinkStart(*point);
}

bool QTableManager::isStartLink()
{
    return (nodo->start!=NULL);
}

QgraphicsItemTable *QTableManager::GetStartNode()
{
    if(nodo->start==NULL) throw new exception();
    return static_cast<QgraphicsItemTable*>(nodo->start);
}

QGraphicsLineItem *QTableManager::GetLineNode()
{
    if(nodo->link==NULL) throw new exception();
    return nodo->link;
}
/**
  * Restituisce la lista dei nodi che hanno come punto terminale questa tabella .
  */
QList<Node*> * QTableManager::GetTableLinkEnd(QGraphicsItemResizable *value)
    {
        QList<Node*> *list;
        list = new QList<Node*>();
        for (int i = 0 ;i<ProjectData->NodeCount();i++){
                if ((ProjectData->getNode(i)->start==value))
                    list->append(ProjectData->getNode(i));
            }
        return list;
    }
/**
  * Restituisce la lista dei nodi che hanno come punto terminale o come punto di inizio questa tabella .
  */
QList<Node *> * QTableManager::GetTableLinked(QGraphicsItemResizable *value)
    {
        QList<Node*> *list = new QList<Node*>();
        for (int i = 0 ;i<ProjectData->NodeCount();i++){
                if ((ProjectData->getNode(i)->start==value)||(ProjectData->getNode(i)->end==value))
                    list->append(ProjectData->getNode(i));
            }
        return list;
    }

void QTableManager::Update(QgraphicsItemTable *table, qreal Vx,qreal Vy)
    {
     QGraphicsLineItem* line ;
        for (int i = 0 ;i<ProjectData->NodeCount();i++){
            line = ProjectData->getNode(i)->link;
            if (ProjectData->getNode(i)->start==table)
                line->setLine(line->line().x1()+Vx,line->line().y1()+Vy,line->line().x2(),line->line().y2());
                if (ProjectData->getNode(i)->end==table){
                    line->setLine(line->line().x1(),line->line().y1(),line->line().x2()+Vx,line->line().y2()+Vy);
                }
            }
    }

qreal QgraphicsItemTable::x()
    {
        return rx;
    }

qreal QgraphicsItemTable::y()
    {
        return ry;

    }

qreal QgraphicsItemTable::width()
    {
        return rw;
    }

qreal QgraphicsItemTable::height()
    {
    return rh;
}
/**
  Return the next position x for attribute.
  */


QgraphicsItemTable::~QgraphicsItemTable()
 {
        VisRef->deleteTable(*(this->GetCaption()));
        VisRef->CancelRefer(this);
        ClearAttribute();
        delete TableData;
}

bool QgraphicsItemTable::canAddAttribute()
{
    return ((attributelist.count()+1)*attribute_width<width());
}



void QgraphicsItemTable::DeleteTable()
    {
        delete this;
    }

void QgraphicsItemTable::NewAttribute()
    {
        QInputDialog *input = new QInputDialog();
        input->setLabelText("Inserisci il valore");
        if (input->exec()==1){
                QString nome = input->textValue();
                 addAttribute(nome,0);
            }

    }


//QAttribute * QAttributeList::AddAttribute(QString capt)
//    {
//        QAttribute* value = new QAttribute(this,parent->GetgrabRefer()); // creo un attributo
//        value->SetCaption( capt); // setto il nome dell' attributo.
//        List.append(value);
//        value->SetAvX(AvX()-attribute_width);
//        value->SetWidth(attribute_width);
//        value->SetHeight(attribute_height);
//        value->SetAttributeType(valore);
//        if (AvX()>=parent->width())// se supera la dimensione della tabella  allargo .
//            parent->SetWidth(wid+attribute_width);
//        parent->GetParentList()->scene->addItem(value);
//        return value;

//    }

QRectF QAttribute::boundingRect() const
    {
        return QRectF(ref->x()+AvX(),ref->Ay(),Width(),Height());
    }

void QgraphicsItemTable::change(qreal x, qreal y, qreal w, qreal h)
    {
        // emit UpdateRect(boundingRect(),QRectF(x,y,w,h));
    if (w>Amx())
                QGraphicsItemResizable::change(x,y,w,h);
}
QAttribute::QAttribute(QgraphicsItemTable *tab,QDAttribute *list, Grabber *grab)
 {
        ref = tab; // riferimento tabella .
        attribute = list; // riferimento dati attributo.
        this->grabRefer = grab;// grab
        menu = new QMenu();
        connect(menu->addAction("Elimina Attributo"),SIGNAL(triggered()),this,SLOT(DelAttribute()));

}

void QAttribute::Repaint()
    {
        prepareGeometryChange();
        update(boundingRect());
    }


void QgraphicsItemTable::SetX(qreal x)
    {
        change(x,y(),width(),height());
    }

void QgraphicsItemTable::SetY(qreal y)
    {
        change(x(),y,width(),height());
    }

void QgraphicsItemTable::SetWidth(qreal width)
    {
        change(x(),y(),width,height());
    }

void QgraphicsItemTable::SetHeight(qreal height)
    {
        change(x(),y(),width(),height);
    }

QRectF* QAttribute::GetRectangle() const
    {
        QRectF Rect = boundingRect();// ottengo  il rettangolo
        qreal bx =(Rect.width()/6)+(Rect.width()/8);
        qreal by =(Rect.height()*(80))/100;
        qreal ox =(Rect.left()+Rect.width()/2.8);
        qreal oy =Rect.topLeft().y()+Rect.height()-by;
        return  new  QRectF(ox,oy,bx,by);
    }

void QAttribute::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        QPointF mouse = event->pos();// prendo la posizione del mouse
        QGraphicsItem::mouseMoveEvent(event);
    }

QRectF* QAttribute::GetTextRectangle() const
    {
        QRectF Rect = boundingRect();
        QRectF* Rect2 = GetRectangle();
        return  new QRectF(Rect.x(),Rect2->y()-25,Rect.width(),30);
    }

void QAttribute::mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        QPointF point = this->mapToScene(event->lastScreenPos());
        if (event->button()==Qt::RightButton){
                ref->GetParentList()->SetReservedValue(0);
                menu->popup(point.toPoint());
            }
        else {
                if (!selct) ref->DeselectAll();
                setSelected(!selct);
                if ((!grabRefer->isEnableGrabber()) &&(GetTextRectangle()->contains(point)));
        }
        QGraphicsItem::mousePressEvent(event);
}

void QAttribute::keyPressEvent(QKeyEvent *event)
{
    if (grabRefer->GrabberItem()==this){
        attribute->applyOneChar(event->key(),event->text());
       this->update();
     }

}




QTkey QAttribute::ColorToTkey(QColor value)
    {
        for (int i = 0 ;i<=6;i++){
                if (sColor[i]==value){
                        return static_cast<QTkey>(i);
                    }
            }
        return  static_cast<QTkey>(0);
    }

QColor QAttribute::TkeyToColor(QTkey value)
    {
        if ((value>=0)&&(value<=6))
            return sColor[value];
        else
            return Qt::white;
    }

bool QAttribute::select()
    {
        return selct;
    }

void QAttribute::setSelected(bool selected)
    {
        this->selct = selected;
        Repaint();
        if (selected){
            grabRefer->EnableGrabber(this,0);
            grabKeyboard();
        }
        else{
            grabRefer->DisableGrabber();
            ungrabKeyboard();
        }

    }


void QAttribute::SetColorNormalKey(QColor value)
    {
    sColor[0] = value;
    }

void QAttribute::SetColorPrimaryKey(QColor value)
    {
    sColor[1] = value;
}

void QAttribute::SetColorForeignKey(QColor value)
{
    sColor[2] = value;
}


void QAttribute::SetColorIndexKey(QColor value)
    {
    sColor[3] = value;
}

void QAttribute::SetColorKeyPrimaryForeign(QColor value)
{
     sColor[4] = value;
}


void QAttribute::SetColorPrimaryAndIndexKey(QColor value)
    {
    sColor[5] = value;
}

void QAttribute::SetColorForeignIndexKey(QColor value)
{
     sColor[6] = value;
}


void QTableManager::mouseMoveEvent(QMouseEvent *event)
    {
        QGraphicsView::mouseMoveEvent(event);

    }

void QgraphicsItemTable::DeselectAll()
    {
        for ( int i = 0 ; i<this->attributelist.count();i++){
                attributelist.at(i)->setSelected(false);
            }
    }

//QList<QAttribute *> QAttributeList::ListSelected()
//    {
//        QList<QAttribute*> *app = new QList<QAttribute *>();
//        for (int i = 0 ; i<List.count();i++)
//            { if (List[i]->select()) app->append(List[i]);
//            }
//        return app;
//    }

//bool QAttributeList::DeleteAttribute(QAttribute* attribute)
//    {
//        if (attribute==NULL)
//            return false;
//        else{
//                int i = .indexOf(attribute);
//                if  (i==-1)return false;
//                for (int p = i+1; p<List.count();p++)
//                    List[p]->SetAvX(List[p]->AvX()-attribute_width);
//                List.removeAt(i);
//                attribute->deleteLater();
//}
//}
void QAttribute::DelAttribute()
    {
    if (ref->attributeCount()==1)
    QMessageBox::warning(NULL,"Warning ","Cannot delete last attribute");
    else {
        ref->removeAttribute(this);
        delete this;
    }
    }


bool QGraphicsItemResizable::isResizing()
    {
    return isResize;
}

bool QGraphicsItemResizable::isSelected()
{
    return select;
}


QRectF QgraphicsItemTable::GetRightRect()
    {
        QRectF F =boundingRect();
        QRectF S =GetInternalRect();
        qreal x =S.x()+S.width();
        qreal y = F.y();
        qreal w = (F.width()-S.width())-(S.x()-F.x());
        qreal h = F.height();
        return QRectF(x,y,w,h);
    }

QRectF QgraphicsItemTable::GetDownRect()
    {
        QRectF F =boundingRect();
        QRectF S =GetInternalRect();
        qreal x = F.x();
        qreal y = S.y()+S.height();
        qreal w = F.width();
        qreal h = F.height()-S.height()-(S.x()-F.x());
        return QRectF(x,y,w,h);

}

QRectF QgraphicsItemTable::GetUpRect()
{
    QRectF F =boundingRect();
    QRectF S =GetInternalRect();
    qreal x = F.x();
    qreal y = F.y();
    qreal w = F.width();
    qreal h = S.y()-F.y();
    return QRectF(x,y,w,h);

}

QRectF QgraphicsItemTable::GetLeftRect()
{
    QRectF F =boundingRect();
    QRectF S =GetInternalRect();
    qreal x = F.x();
    qreal y = F.y();
    qreal w = S.x()-F.x();
    qreal h =  F.height();
    return QRectF(x,y,w,h);
}

Grabber *QgraphicsItemTable::GetgrabRefer()
{
    return grabRefer;
}

void QgraphicsItemTable::addAttribute(QString caption,int tipo)
{
    if (canAddAttribute()){
    QDAttribute* attribute = new QDAttribute(TableData, new QString(caption),tipo,NormalKey);
    QAttribute*  visual_attribute = new QAttribute(this,attribute,this->GetgrabRefer());
    visual_attribute->SetAvX(Amx());
    visual_attribute->SetAvY(y());
    visual_attribute->SetWidth(attribute_width);
    visual_attribute->SetHeight(attribute_height);// DA QUI
    attributelist.append(visual_attribute);
    TableData->addAttribute(attribute);
    VisRef->GraphicsScene()->addItem(visual_attribute);
}
    }

void QgraphicsItemTable::removeAttribute(QAttribute *attr)
{
    if(attr==NULL) throw new invalid_argument("QgraphicsItemTable::removeAttribute(QAttribute *attr) where attr is null");
     int attrvalue = attributelist.indexOf(attr);
     if(attrvalue==-1) throw new invalid_argument("QGraphicsitemtable::removeAttribute(QAttribute *attr) where attr doesn't exists in  list");
     for (int i = attrvalue+1;i<attributelist.count();i++){
         attributelist.at(i)->SetAvX(attributelist.at(i)->AvX()-attribute_width);
     }
     this->TableData->deleteAttributeIndex(attrvalue);
     attributelist.removeAt(attrvalue);
}

int QgraphicsItemTable::attributeCount()
{
    return attributelist.count();
}

void QgraphicsItemTable::ClearAttribute()
{
    for (int i = 0;i<attributelist.count();i++){
        QAttribute* attr = attributelist.at(i);
        delete attr;
    }
    attributelist.clear();
}

void QTableManager::EUpdate(QgraphicsItemTable *table, qreal Vx, qreal Vy)
    {
        QRectF *up = new QRectF(table->GetUpRect());
        QRectF *down = new QRectF(table->GetDownRect());
        QRectF *right = new QRectF(table->GetRightRect());
        QRectF *left = new QRectF(table->GetLeftRect());


        //QPointF  sbottom = sec->bottomRight()
        for ( int i = 0 ; i<ProjectData->NodeCount();i++){

            QLineF line = ProjectData->getNode(i)->link->line();

            QPointF *point  = new QPointF(line.x1(),line.y1());
            QPointF *point2 = new QPointF(line.x2(),line.y2());
           qreal xbottom = 0 ;
           qreal ybottom  = 0 ;

            if (ProjectData->getNode(i)->start==table){

                            xbottom = point->x();
                            ybottom = point->y();

                          //  ProjectData->getNode(i)->link->setLine(xbottom,ybottom,point2->x(),point2->y());
                        }
            if (ProjectData->getNode(i)->end==table){
                            xbottom = point2->x();
                            ybottom = point2->y();
                            //xbottom = (bottom.x()*xbottom)/(bottom.x()+Vx);
                          //  ybottom = (bottom.y()*ybottom)/(bottom.y()+Vy);
                           // ProjectData->getNode(i)->link->setLine(point->x(),point->y(),point2->x()+Vx,point2->y()+Vy);
                            }
            if ((xbottom!=0 || ybottom !=0)){
                if (right->contains(*point)||right->contains(*point2) ){
                    xbottom+=Vx;
                    // y media.
                }
                if (up->contains(*point)|| up->contains(*point2)){
                    // media x

                }
                if (down->contains(*point)|| down->contains(*point2)){
                    // media x
                    ybottom +=Vy;
                }
               if (left->contains(*point)||left->contains(*point2) ){
                   // media y.
            }
               if (ProjectData->getNode(i)->end==table)
            ProjectData->getNode(i)->link->setLine(point->x(),point->y(),point2->x()+Vx/2,point2->y()+Vy/2);
            else
            ProjectData->getNode(i)->link->setLine(xbottom,ybottom,point2->x(),point2->y());
            }
}
}

Grabber::Grabber()
{
    gItem = NULL;

}

void Grabber::EnableGrabber(QGraphicsItem *grabber, int device)
{
    if (grabber==NULL) throw new invalid_argument("Error EnableGrabber NullPointerException.");
    if ((device<0) || (device>255)) throw new invalid_argument("Error device must included between 0 and 255 .");
    QGraphicsItem * item = gItem;
    gItem = grabber;
    ItemDevices = device;
    if (item!=NULL) item->update(item->boundingRect());// refresh schermata.
    gItem->update(gItem->boundingRect());
}

void Grabber::DisableGrabber()
{
    gItem = NULL;
}

bool Grabber::isEnableGrabber()
{
    return (gItem!=NULL);
}

QGraphicsItem *Grabber::GrabberItem()
{
    return gItem;
}

int Grabber::GrabberDeviceItem()
{
    return ItemDevices;
}

void QTableManager::CloseLink(QgraphicsItemTable *table)
{
    if (isStartLink()){
        if ((nodo->start!=table)&& (table!=NULL)){
    nodo->end = table;
    if ( ProjectData->addNode(nodo)){
    nodo = new Node();
    nodo->start = NULL;
    nodo->link = NULL;
    }
    else
    CloseLink(NULL);
    }
    else {
    delete  nodo->link;
        nodo->start = NULL;
        nodo->link = NULL;
    }
    }
}

qreal QgraphicsItemTable::Ay()
{
    return y()-attribute_height;
}

qreal QgraphicsItemTable::Amx()
{
    return (attributelist.count()*attribute_width);
}

void QgraphicsItemTable::AttributeRepaint()
{
    for(int i = 0;i< attributelist.count();i++)
        attributelist.at(i)->Repaint();
}

qreal QTableManager::calcolaPos(qreal Media, qreal start, qreal end)
{
    return (Media/100)*end-start;
}

qreal QTableManager::calcolaMedia(qreal pos, qreal start, qreal end)
{
    return (((start+pos)/end)*100);
}
















