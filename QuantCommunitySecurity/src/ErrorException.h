#ifndef ERROR_EXCEPTION_H
#define ERROR_EXCEPTION_H

#include <QString>
#include <QTextStream>

class ErrorException
{
    public:
        ErrorException(QString& cause, int errorCode);
        QString getCause();
        int getErrorCode();
        QString toString();

    private:
        QString cause;
        int errorCode;
};

#endif
