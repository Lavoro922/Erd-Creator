#include "edittext.h"

EditText::EditText()
{
    text = "";
    setPositionatLast();
    font = new  QFontMetrics(QApplication::font());
}

EditText::~EditText()
{
  delete font;
  delete &text;
}

EditText::EditText(QString cap)
{
    text = cap;
    font = new  QFontMetrics(QApplication::font());
    setPositionatLast();
}

void EditText::applyChar(int value,QString txt)
{
    switch(value){
    case Qt::Key_Backspace:{
        if(text.count()!=1){
        text.remove(position,1);
        decPosition();
        }
        break;
    }
    case Qt::Key_Right:{
        incPosition();
        break;
    }
    case Qt::Key_Left:{
         decPosition();

        break;
    }

    }
    if ((value!=Qt::Key_Space)&&(QChar(value).isLetterOrNumber())){
        int add = (text.count()==1)?0:1;
        text.insert(position+add,txt);
        incPosition();
    }
}

int EditText::getPosition()
{
    return position+1;
}

QString EditText::getValue()
{
    QString copy = text;
    return copy;
}

qreal EditText::getWidth(int pos)
{
    return font->width(text.at(pos).toAscii());
}

qreal EditText::getHeigth()
{
    return font->height();
}

void EditText::setPosition(int value)
{
    if ((position<1) || (position>text.size())) throw new invalid_argument("Invalid argument Setposition");
    position = value -1;
}

void EditText::incPosition()
{
    position++;
    if (position==text.size()) position = text.count()-1;
}

void EditText::decPosition()
{
    position--;
    if (position<0) position = 0;
}

void EditText::setPositionatLast()
{
    position = text.length()-1;
}

void EditText::setPositionAtStart()
{
    position = 0;
}

void EditText::setValue(QString value)
{
     text=value;
     setPositionatLast();
}

qreal EditText::getStrHeight()
{
    return getHeigth();
}

qreal EditText::getStrWidth()
{
    qreal value =0;
    for (int i = 0;i<position;i++)
        value+=getWidth(i);
    return value;
}
