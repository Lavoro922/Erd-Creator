#ifndef FILENOTFOUND_H
#define FILENOTFOUND_H
#include<exception>
using namespace std;

class FileNotFound:public exception{
private:
    const char* mess;
public:
    virtual const  char* what() const throw(){return mess;}
    FileNotFound(const char* pmess):exception(){ mess = pmess;}
};


#endif // FILENOTFOUND_H
