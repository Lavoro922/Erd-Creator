#ifndef LISTISEMPTY_H
#define LISTISEMPTY_H
#include<exception>
using namespace std;

class ListIsEmpty:public exception{
private:
    const char* mess;
public:
    virtual const  char* what() const throw(){return mess;}
    ListIsEmpty(const char* pmess):exception(){ mess = pmess;}
};


#endif // LISTISEMPTY_H
