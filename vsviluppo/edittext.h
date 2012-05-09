#ifndef EDITTEXT_H
#define EDITTEXT_H
#include<QString>
#include<QFontMetrics>
#include<QApplication>
#include <iostream>
#include <stdexcept>
#include <bitset>
#include<QMessageBox>
using namespace std;
class EditText
{
private:
    QString text;
    QFontMetrics* font;
    int position;
public:
    EditText();
    ~EditText();
    EditText(QString cap);
    void applyChar(int value,QString txt);
    void setPosition(int value);
    void incPosition();
    void decPosition();
    void setPositionatLast();
    void setPositionAtStart();
    void setValue(QString value);
    int  getPosition();
    QString getValue();
    qreal getWidth(int pos );
    qreal getHeigth();
    qreal getStrWidth();
    qreal getStrHeight();
};

#endif // EDITTEXT_H
