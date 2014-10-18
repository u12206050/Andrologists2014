#ifndef CONNECTIONFILEREADER_H
#define CONNECTIONFILEREADER_H

#include <QString>
#include <string>
#include "DatabaseConnection.h"
#include <queue>
#include <ErrorException.h>
#include <fstream>
#include <sstream>

using namespace std;

class ConnectionFileReader
{
    public:
        ConnectionFileReader(QString filename);
        DatabaseConnection *getDatabaseConnection();

    private:
        void parse();
        void tokenise(string input);
        void consumeToken(string expected);

        queue<string> tokens;
        int currentToken;
        DatabaseConnection* connection;
};

#endif // CONNECTIONFILEREADER_H
