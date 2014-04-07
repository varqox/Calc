#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("Usage: jjj <file1> <file2>\n");
		return 1;
	}
	fstream file1(argv[1], ios_base::in), file2(argv[2], ios_base::in);
	if(!file1.good()) cout << "Cannot open file: " << argv[1] << endl;
	else if(!file2.good()) cout << "Cannot open file: " << argv[2] << endl;
	else
	{
		string s1, s2;
		while(file1.good() && file2.good())
		{
			getline(file1,s1);
			getline(file2,s2);
			if(s1!=s2 || (file1.good()^file2.good()))
			{
				cout << "Files don't match!\n";
				return 0;
			}
		}
		cout << "Files match!\n";
	}
return 0;
}