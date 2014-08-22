#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
 
int main ()
{
	const string ENV[ 24 ] = {                 
		"COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",   
		"HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",             
		"HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",         
		"HTTP_HOST", "HTTP_USER_AGENT", "PATH",            
		"QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",      
		"REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
		"SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",      
		"SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",     
		"SERVER_SIGNATURE","SERVER_SOFTWARE" }; 
	//USE REMOTE_ADDR to check ip address of client eg. getenv(ENV[11].c_str());
	cout << "Content-Type: text/html\n\n";
	cout << "<!DOCTYPE>\n";
	cout << "<html>\n";
	cout << "<head><title>Welcome message</title></head>\n";
	cout << "<body>\n";
	cout << "<h1>Greetings!</h1>\n";
	char query[1024];
	int len, startNumberLocation, endNumberLocation;
	string data;
	char strnum[20];
	if(getenv("CONTENT_LENGTH"))
	{
		len = atoi(getenv("CONTENT_LENGTH"));
		cin.read(query, len);
		data = query;
		startNumberLocation = data.find("number")+6;
		endNumberLocation = data.find("&button");
		cout << "<p>Welcome '" << (data.substr(startNumberLocation, endNumberLocation-startNumberLocation)) << "</p>\n";			
	}
	else
	{
		cout << "<form method='post' action='/cgi-bin/execute.cgi'>";
		cout << "<p>Enter your name</p>";
		cout << "<input type='text' name='name'/>";
		cout << "<input type='submit' name='button'/>";
		cout << "</form>\n";
			
	}
	cout << "<image src='/cgi-bin/geti.cgi?image=Desert.jpg'>\n";
	cout << "</body>\n";
	cout << "</html>";
	/*
	cout << 'Content-type:text/html\r\n\r\n';
	cout << "<html>\n';
	cout << "<head>\n';
	cout << "<title>QFRSS/title>\n';
	cout << "</head>\n';
	cout << "<body>\n';
	cout << "<h2>Output can be in json string as well</h2>\n';
	//http://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm
	cout << "</body>\n';
	cout << "</html>\n';*/

	return 0;
}