#include "ConnectionFileReader.h"

#include <iostream>
using namespace std;

ConnectionFileReader::ConnectionFileReader(QString filename)
{
    ifstream inputFile(filename.toStdString().c_str());
    if (inputFile.is_open())
    {
        string line;
        string input;
        while (inputFile >> line)
        {
            input += line;
        }

        tokenise(input);
        parse();
    }
    else
    {
        QString casue("Cannot open file");
        throw ErrorException(casue, 0);
    }
}

DatabaseConnection *ConnectionFileReader::getDatabaseConnection()
{
    return connection;
}

void ConnectionFileReader::parse()
{
    consumeToken("type");
    consumeToken("=");
    consumeToken("\"");
    QString type(tokens.front().c_str());
    tokens.pop();
    consumeToken("\"");
    consumeToken(";");

    consumeToken("host");
    consumeToken("=");
    consumeToken("\"");
    QString host(tokens.front().c_str());
    tokens.pop();
    consumeToken("\"");
    consumeToken(";");

    consumeToken("name");
    consumeToken("=");
    consumeToken("\"");
    QString name(tokens.front().c_str());
    tokens.pop();
    consumeToken("\"");
    consumeToken(";");

    consumeToken("username");
    consumeToken("=");
    consumeToken("\"");
    QString username(tokens.front().c_str());;
    tokens.pop();
    consumeToken("\"");
    consumeToken(";");

    consumeToken("password");
    consumeToken("=");
    consumeToken("\"");
    QString password(tokens.front().c_str());
    tokens.pop();
    consumeToken("\"");
    consumeToken(";");

    consumeToken("port");
    consumeToken("=");
    QString portToken(tokens.front().c_str());
    tokens.pop();
    int port;
    stringstream(portToken.toStdString()) >> port;
    consumeToken(";");

    connection = new DatabaseConnection(type, host, name, username, password, port);

}

void ConnectionFileReader::consumeToken(string expected)
{
    string token = tokens.front();
    tokens.pop();
    if (token != expected)
    {
        QString cause;
        cause.append(expected.c_str());
        cause.append(" expected, but ");
        cause.append(token.c_str());
        cause.append(" found.");
        throw ErrorException(cause, 1);
    }
}

void ConnectionFileReader::tokenise(string input)
{
    string token = "";

    for (unsigned int i = 0; i < input.length(); i++)
    {
        char c = input[i];
        if (c == '[' || c == ']' || c == ';' || c == '=' || c == '\"')
        {
            stringstream ss;
            ss << c;
            string charConvert;
            ss >> charConvert;
            if (token != "")
            {
                tokens.push(token);
                tokens.push(charConvert);
                token = "";
            }
            else
            {
                tokens.push(charConvert);
            }
        }
        else
        {
            token += c;
        }
    }
}
