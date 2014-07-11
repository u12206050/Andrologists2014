#include "Exception.h"

Exception::Exception(QString& cause, int errorCode)
{
    this->cause = cause;
    this->errorCode = errorCode;
}

QString Exception::getCause()
{
    return cause;
}

int Exception::getErrorCode()
{
    return errorCode;
}

QString Exception::toString()
{
    QString returnString;
    QTextStream(&returnString) << 'E' << errorCode << ": " << cause;
    return returnString;
}
