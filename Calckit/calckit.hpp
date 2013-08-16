#ifndef __Calckit_hpp
#define __Calckit_hpp

namespace Calckit
{
	bool parser(const string&, int, int);
	int pri(char);
	void work(vector<num>&, vector<bool>&, vector<char>&, int&, char);
	string f_pos_to_str(int, int, const string&);
	bool core(const string&, int, int);
}

#endif // __Calckit_hpp