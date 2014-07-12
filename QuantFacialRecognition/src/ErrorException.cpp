#include "ErrorException.h"

ErrorException::ErrorException(QString& cause, int errorCode)
{
    this->cause = cause;
    this->errorCode = errorCode;
}

QString ErrorException::getCause()
{
    return cause;
}

int ErrorException::getErrorCode()
{
    return errorCode;
}

QString ErrorException::toString()
{
    QString returnString;
    QTextStream(&returnString) << 'E' << errorCode << ": " << cause;
    return returnString;
}
