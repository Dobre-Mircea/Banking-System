#include <iostream>
#include <string>
using namespace std;

string hashing(string passwd)
{
	char aux;
	for(int i = 0; i < passwd.length() / 2 - 1; i++)
	{
		aux = passwd[passwd.length() - i - 1];
		passwd[passwd.length() - i] = passwd[i];
		passwd[i] = aux;
	}

	for(int i = 0; i < passwd.length(); i++)
		if(i % 2 == 0)
			passwd[i]--;
		else passwd[i]++;

	return passwd;
}


int main()
{
	string s = "muiepsd";
	cout << hashing(s);
	

	return 0;
}
