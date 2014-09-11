#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;
 
void dumpFile(const char* filename)
{
	ifstream file(filename, ios::in | ios::binary);

	if (file)
	{
	    while (!file.eof())
	    {
		char buf[1024];

		file.read(buf, sizeof(buf));
		int count = file.gcount();
		if (count)
		{
		    cout.write(buf, count);
		} else {
		    break;
		}
	    }

	    cout.flush();
	}
} 
 
int main ()
{	
	cout << "Content-type:text/html\r\n\r\n";
	cout << "<html>\n";
	cout << "<head>\n";
	cout << "<title>QFRSS</title>\n";
	cout << "</head>\n";
	cout << "<body>\n";
	cout << "<h2>Output can be in json string as well</h2>\n";
	cout << "<image src='/cgi-bin/geti.cgi?image=Desert.jpg'>";
	//http://www.tutorialspoint.com/cplusplus/cpp_web_programming.htm
	cout << "</body>\n";
	cout << "</html>\n";

	return 0;
}