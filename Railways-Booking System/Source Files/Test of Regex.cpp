#include<regex>
#include<iostream>
#include<string>

using namespace::std;

int main() 
{
	string str = "receipt freind theif receive!";
	string pattern("[^c]ei");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	
	regex r(pattern);
	smatch results;

	if (regex_search(str, results, r))
	{
		cout << results.str() << endl;
	}

	return 0;
}