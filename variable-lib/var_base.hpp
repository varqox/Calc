#ifndef var_base_hpp
#define var_base_hpp

#include "spis.hpp"
#include <vector>
#include <queue>
#include <string>
#include <stack>

using namespace std;

namespace var_base
{
	struct ver
	{
		int t[256];
		dn w;
		bool is;
		ver();
		~ver(){};
	};
	extern vector<ver> _v;
	extern queue<int> _free;
	extern bool is_there;
	void add_var(string s, dn w);
	bool remove_var(string s);
	bool read_var(string s, dn &w);
}

#endif // var_base_hpp
