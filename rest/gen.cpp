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
	{int ___e=system("mkdir -p tests/Calc/ && rm -f tests/Calc/*");}
	for(int q=1; q<=t; ++q)
	{
		string in, in1, in2, in3, out, spr, test_name;
		test_name="tests/Calc/"+to_string(q);
		in+=static_cast<char>(rd()%9+'1');
		for(int i=rd()%100000; i>=0; --i)
		{
			in+=static_cast<char>(rd()%10+'0');
		}
		in1+=static_cast<char>(rd()%9+'1');
		for(int i=rd()%100000; i>=0; --i)
		{
			in1+=static_cast<char>(rd()%10+'0');
		}
		/*in2+=static_cast<char>(rd()%9+'1');
		for(int i=rd()%10; i>=0; --i)
		{
			in2+=static_cast<char>(rd()%10+'0');
		}
		in3+=static_cast<char>(rd()%9+'1');
		for(int i=rd()%10; i>=0; --i)
		{
			in3+=static_cast<char>(rd()%10+'0');
		}
		char oper;
		switch(rd()%5)
		{
			case 0: oper='+';break;
			case 1: oper='-';break;
			case 2: oper='*';break;
			case 3: oper='/';break;
			case 4: oper='%';break;
			case 5: oper='^';break;
		}*/
		test.open((test_name+".in").c_str(), ios_base::out);
		//test << (rd()%2 ? "(-":"(") << in << "/" << in1 << ")" << oper << "(" << (rd()%2 ? "-":"") << in2 << "/" << in3 << ")\nexit\n";
		test << (rd()%2 ? "-":"") << in << "*" << (rd()%2 ? "-":"") << in1 << endl;
		test.close();
		int ___e=system(("Calc -w < "+test_name+".in > "+test_name+".out").c_str());
		cout << q << ": generated!\n";
	}
return 0;
}