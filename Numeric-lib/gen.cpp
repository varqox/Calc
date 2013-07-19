#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <fstream>

using namespace std;

template<typename type>
type abs(type a)
{
	if(a<0) return -a;
return a;
}

int rd()
{
return abs(rand());
}

string to_string(int a)
{
	stack<char> st;
	while(a>0)
	{
		st.push('0'+a%10);
		a/=10;
	}
	string w;
	while(!st.empty())
	{
		w+=st.top();
		st.pop();
	}
	if(w.empty()) w="0";
return w;
}

int main()
{
	srand(time(NULL));
	int t;
	cin >> t;
	fstream test;
	{int ___e=system("mkdir -p tests/num-lib/ && rm -f tests/num-lib/*");}
	for(int q=1; q<=t; ++q)
	{
		string in, in1, in2, in3, out, spr, test_name;
		test_name="tests/num-lib/"+to_string(q);
		in+=static_cast<char>(rd()%9+'1');
		for(int i=rd()%10; i>=0; --i)
		{
			in+=static_cast<char>(rd()%10+'0');
		}
		in1+=static_cast<char>(rd()%9+'1');
		for(int i=rd()%10; i>=0; --i)
		{
			in1+=static_cast<char>(rd()%10+'0');
		}
		in2+=static_cast<char>(rd()%9+'1');
		for(int i=rd()%3; i>=0; --i)
		{
			in2+=static_cast<char>(rd()%10+'0');
		}
		in3+=static_cast<char>(rd()%9+'1');
		for(int i=rd()%3; i>=0; --i)
		{
			in3+=static_cast<char>(rd()%10+'0');
		}
		in3="1";
		bool z1=rd()%2, z2=rd()%2;
		test.open((test_name+".in").c_str(), ios_base::out);
		test << (z1 ? "(-":"(") << in << "/" << in1 << ")^(" << (z2 ? "-":"") << in2 << "/" << in3 << ")\nexit\n";
		test.close();
		int ___e=system((".././Calc -w < "+test_name+".in > "+test_name+".out").c_str());
		test.open((test_name+".in").c_str(), ios_base::out);
		test << (z1 ? "-":"") << in << " " << in1 << " " << (z2 ? "-":"") << in2 << " " << in3 << endl;
		test.close();
		cout << q << ": generated!\n";
	}
return 0;
}