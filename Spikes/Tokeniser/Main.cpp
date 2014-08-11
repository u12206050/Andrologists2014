#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> tokenise(string input)
{
	string token = "";
	vector<string> tokens;
	
	for (unsigned int i = 0; i < input.length(); i++)
	{
		char c = input[i];
		if (c == '[' || c == ']' || c == ';' || c == '=')
		{
			if (token != "")
			{
				tokens.push_back(token);
				stringstream ss;
				ss << c;
				string charConvert;
				ss >> charConvert;
				tokens.push_back(charConvert);
				token = "";
			}
			else
			{
				tokens.push_back("[");
			}
		}
		else
		{
			token += c;
		}
	}
		
	return tokens;
}

int main()
{
	string name = "config.txt";
	ifstream input(name.c_str());
	if (input.is_open())
	{
		cout << "opened" << endl;
		string line;
		string out;
		while (input >> line)
		{
			out += line;
		}
		
		vector<string> tokens = tokenise(out);
		
		for (unsigned int i = 0; i < tokens.size(); i++)
		{
			cout << tokens[i] << endl;
		}
	}
	else
	{
		cout << "cant open" << endl;
	}
}
