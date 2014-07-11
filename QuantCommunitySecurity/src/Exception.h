#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <QTextStream>

class Exception
{
    public:
        Exception(QString& cause, int errorCode);
        QString getCause();
        int getErrorCode();
        QString toString();

    private:
        QString cause;
        int errorCode;
};

#endif // EXCEPTION_H
