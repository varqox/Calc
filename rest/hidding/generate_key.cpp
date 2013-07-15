#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

template<typename type>
inline type abs(type a)
{
	if(a<0) return -a;
return a;
}

inline int rd()
{
return abs(rand());
}

int main()
{
	srand(time(NULL));
	fstream key;
	string name;
	cout << "Write key-file name: ";
	cin >> name;
	key.open((name+".key").c_str(), ios::out);
	if(key.good())
	{
		bool is[256];
		for(int i=0; i<256; i++)
			is[i]=0;
		for(int i=0; i<256; i++)
		{
			int k=rd()%256;
			while(is[k])
				k=rd()%256;
			is[k]=1;
			key << char(k);
		}
		key.close();
	}
	else cout << "Error: Cannot create key file!\n";
return 0;
}