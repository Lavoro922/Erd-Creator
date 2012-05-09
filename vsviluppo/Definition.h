#ifndef DEFINITION_H
#define DEFINITION_H
enum QMultiplicity  {OnetoN = 0,NtoOne =  1 ,OneToOne = 2 };// serve per definire la relazione tra le tabelle.
enum QTkey {NormalKey = 0,KeyPrimary = 1,KeyForeign = 2 ,KeyIndex = 3,KeyPrimaryForeign = 4 , KeyPrimaryIndex = 5,KeyForeignIndex  = 6};
const int MAXNUMBEROFKEY = 6;
const int LOWNUMBEROFKEY = 0;
const int attribute_height = 100;




#endif // DEFINITION_H
