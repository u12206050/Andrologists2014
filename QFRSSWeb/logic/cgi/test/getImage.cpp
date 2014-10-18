#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#if _WIN32
#include <fcntl.h>
#include <io.h>

#define strcasecmp stricmp
#endif

using namespace std;

void cgiError()
{
	// Most simple error handling
	cout << "Error occured" << endl;
	exit(0);
}


void dumpFile(const char* filename)
{
	// Get the image type and send the headers
	const char* imgtype = "gif"; // assume gif by default
	char* ptr = strrchr(filename, '.');
	if (ptr && (strcasecmp(ptr, ".jpg") == 0 || strcasecmp(ptr, ".jpeg") == 0))
	{
	    imgtype = "jpeg";
	}

	cout << "Content-Type: " << "image/" << imgtype << endl;
	cout << endl;

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


int main()
{
	#if _WIN32
	// Standard I/O is in text mode by default; since we intend
	// to send binary image data to standard output, we have to
	// set it to binary mode.
	// Error handling is tricky to say the least, so we have none.
	_fmode = _O_BINARY;
	if (_setmode(_fileno(stdin), _fmode) == -1) {}
	if (_setmode(_fileno(stdout), _fmode) == -1) {}
	#endif
	// Set the path where your images are located. NOTE: Not a url.
	char path[] = "../htdocs/QFRSSWeb/";
	// First, we get the filename of the image to send
	char* querystr = getenv("QUERY_STRING");
	char* imgparm  = querystr ? strstr(querystr, "image=") : 0;
	char imagename[81];
	if (!imgparm || 1 != sscanf(imgparm, "image=%80[^&]", imagename))
	{
	    cgiError();
	}
	if (imagename[0] != '#')
	{		

		strcat(path,imagename);
		// Send the image
		cout << path;
		dumpFile(path);
	}
	else
	{
		//get from database.
	}
	return 0;
}