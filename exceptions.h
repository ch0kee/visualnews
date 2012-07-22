#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <QString>
#include <QTextStream>

enum eExceptionType { EET_IOERROR, EET_PARSEERROR, EET_NETWORKERROR };

class IException
{
public:
  virtual void print() = 0;
};

template<eExceptionType ExceptionType_>
class Exception : public IException
{
public:
  Exception(const QString& msg)
    : _msg(msg)
  {

  }



  virtual void  print()
  {
    endl(QTextStream(stdout) << "!! " << exceptionCategory() << " :: " << _msg);
  }

  /*virtual const char* what() const
  {
    return _msg.data();
  }*/
private:

  QString exceptionCategory()
  {
    switch(ExceptionType_)
    {
    case EET_IOERROR:
      return "IoError";
    case EET_PARSEERROR:
      return "ParseError";
    case EET_NETWORKERROR:
      return "NetworkError";
    default:
      return "GenericException";
    }
  }

  QString _msg;
};

#endif // EXCEPTIONS_H
