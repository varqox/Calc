#include "var_base.hpp"

namespace var_base
{
	ver::ver(): is(false)
	{
		for(short int i=0; i<256; ++i)
			t[i]=0;
	}
	vector<ver> _v(1);
	queue<int> _free;
	bool is_there;

	void swap_var(const string& s, num& w)
	{
		ver x;
		int k=0, sl=s.size();
		for(int i=0; i<sl; ++i)
		{
			if(_v[k].t[static_cast<int>(s[i])]==0)
			{
				if(_free.empty())
				{
					_v[k].t[static_cast<int>(s[i])]=_v.size();
					k=_v.size();
					_v.push_back(x);
				}
				else
				{
					_v[k].t[static_cast<int>(s[i])]=_free.front();
					k=_free.front();
					_v[k]=x;
					_free.pop();
				}
			}
			else k=_v[k].t[static_cast<int>(s[i])];
		}
		_v[k].is=true;
		_v[k].w.swap(w);
	}

	bool remove_var(const string& s)
	{
		int k=0, sl=s.size();
		stack<int> grt;
		grt.push(0);
		for(int i=0; i<sl; ++i)
		{
			if(_v[k].t[static_cast<int>(s[i])]==0) return false;
			else
			{
				k=_v[k].t[static_cast<int>(s[i])];
				grt.push(k);
			}
		}
		if(!_v[k].is) return false;
		_v[k].is=false;
		while(grt.size()>1)
		{
			--sl;
			for(short int i=0; i<256; ++i)
				if(_v[k].t[i]!=0) return true;
			grt.pop();
			_free.push(k);
			k=grt.top();
			_v[k].t[static_cast<int>(s[sl])]=0;
		}
	return true;
	}

	bool read_var(const string& s, num& w)
	{
		int k=0, sl=s.size();
		for(int i=0; i<sl; ++i)
		{
			if(_v[k].t[static_cast<int>(s[i])]==0) return false;
			else k=_v[k].t[static_cast<int>(s[i])];
		}
		if(!_v[k].is) return false;
		w=_v[k].w;
	return true;
	}
}