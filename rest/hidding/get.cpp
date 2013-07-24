#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	fstream plik;
	plik.open("hide.txt", ios::in);
	while(!plik.eof())
	{
		cout << (char)plik.get();
	}
return 0;
}