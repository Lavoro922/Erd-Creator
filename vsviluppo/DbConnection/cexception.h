#ifndef DLLEXCEPTION_H
#define DLLEXCEPTION_H
#include<exception>
using namespace std;

class CException:public exception{
private:
    const char* mess;
public:
    virtual const  char* what() const throw(){return mess;}
    CException(const char* pmess):exception(){ mess = pmess;}
};

class DllException : public CException{
public:
    DllException(const char* pmess):CException(pmess){}
};

class DllExceptionLoader: public DllException{
public :
    DllExceptionLoader(const char* pmess):DllException(pmess){}
};
class DllExceptionExecute: public DllException{
public :DllExceptionExecute(const char* pmess):DllException(pmess){}
};
class DllExceptionConnectionExists: public  DllException{
public :DllExceptionConnectionExists(const char* pmess):DllException(pmess){}
};

class SCException : public CException{public :SCException(const char* pmess):CException(pmess){}};



class SCExceptionInvalidDbType : public CException{
public :
    SCExceptionInvalidDbType(const char* pmess):CException(pmess){}
};
class SCExceptionExecQuery: public SCException{
public :
    SCExceptionExecQuery(const char* pmess):SCException(pmess){}

};
class SCExceptionClose: public SCException{
public :
    SCExceptionClose(const char* pmess):SCException(pmess){}
};
class SCExceptionConnectionExists: public  DllException{
public :
    SCExceptionConnectionExists(const char* pmess):DllException(pmess){}
};

#endif // DLLEXCEPTION_H
