#include "../Main/main.hpp"
#include "../Variable-lib/var_base.hpp"
#include "../Numeric-lib/num.hpp"

namespace Calckit
{
	bool parser(const string& _str, int begin, int end)
	{
		--end;
		int br=0, z=0, number=0, krp=0, m=0;
		bool var=false;
		if(_str[begin]=='!')
		{
			cout << "Wrong argument: '!'!" << endl;
			return false;
		}
		if(begin+1<end && (_str[begin]=='-' || _str[begin]=='+') && (_str[begin+1]=='-' || _str[begin+1]=='+'))
		{
			cout << "Wrong argument: '" << _str[begin+1] << "'!" << endl;
			return false;
		}
		for(int i=begin; i<=end; ++i)
		{
			if(_str[i]=='(')
			{
				++br;
				number=0;
				var=false;
				m=0;
				krp=0;
				z=0;
			}
			else if(_str[i]==')')
			{
				--br;
				if(br<0 || number==0)
				{
					cout << "Wrong parentheses layout!" << endl;
					return false;
				}
				z=0;
			}
			else if(_str[i]=='.')
			{
				if(number==0 || krp>0 || i==end || _str[i+1]<'0' || _str[i+1]>'9' || var)
				{
					cout << "Wrong number writing!" << endl;
					return false;
				}
				++krp;
			}
			else if(_str[i]=='+' || _str[i]=='-')
			{
				if(m==0 && !(i==end || _str[i+1]==')'))
				{
					if(z==0) ++z;
					else ++m;
				}
				else
				{
					cout << "Wrong argument: '" << _str[i] << "'!" << endl;
					return false;
				}
				number=0;
				var=false;
				krp=0;
			}
			else if(_str[i]=='*' || _str[i]=='/' || _str[i]=='%' || _str[i]=='^')
			{
				++z;
				if(z>1 || number==0 || i==end || _str[i+1]==')')
				{
					cout << "Wrong argument: '" << _str[i] << "'!" << endl;
					return false;
				}
				number=0;
				var=false;
				krp=0;
				m=0;
			}
			else if(_str[i]=='!')
			{
				z=0;
				m=0;
				number=1;
				krp=0;
				if(_str[i-1]=='+' || _str[i-1]=='-' || _str[i-1]=='*' || _str[i-1]=='/' || _str[i-1]=='%' || _str[i-1]=='^' || _str[i-1]=='(')
				{
					cout << "Wrong argument: '!'!" << endl;
					return false;
				}
			}
			else if(_str[i]>='0' && _str[i]<='9')
			{
				++number;
				z=0;
				m=0;
			}
			else
			{
				++number;
				z=0;
				m=0;
				var=true;
			}
		}
		if(br!=0)
		{
			cout << "Wrong parentheses layout!" << endl;
			return false;
		}
		if(z>0)
		{
			char t;
			if(m>0) t=_str[end-1];
			else t=_str[end];
			cout << z << " " << m << "Wrong argument: '" << t << "'!" << endl;
			return false;
		}
	return true;
	}

	inline int pri(char c)
	{
		if(c=='^') return 4;
		if(c=='*' || c=='/' || c=='%') return 3;
		if(c=='+' || c=='-') return 2;
		if(c=='(' || c==')') return 1;
	return 0;
	}

	bool work(vector<num> &base, vector<bool> &sign, vector<char> &operators, int &parenth_depth, char prior)
	{
		int bs=base.size()-1;
		if(prior==4 || bs<1) return true;
		while(bs>=1 && pri(operators[bs-1+parenth_depth])>prior)
		{
			if(sign[bs+parenth_depth])
			{
				base[bs].opp();
				sign[bs+parenth_depth]=false;
			}
			if(operators[bs-1+parenth_depth]=='^')
				base[bs-1].pow(base[bs]);
			else
			{
				if(sign[bs-1+parenth_depth])
				{
					base[bs-1].opp();
					sign[bs-1+parenth_depth]=false;
				}
				switch(operators[bs-1+parenth_depth])
				{
					case '+': base[bs-1]+=base[bs];break;
					case '-': base[bs-1]-=base[bs];break;
					case '*': base[bs-1]*=base[bs];break;
					case '/': base[bs-1]/=base[bs];break;
					case '%': base[bs-1]%=base[bs];break;
				}
			}
			if(errors::is_any_error) return false;
			base.pop_back();
			operators.pop_back();
			sign.pop_back();
			--bs;
		}
		if(bs>0 && prior!=1 && prior==pri(operators[bs-1+parenth_depth]))
		{
			if(sign[bs+parenth_depth])
			{
				base[bs].opp();
				sign[bs+parenth_depth]=false;
			}
			if(operators[bs-1+parenth_depth]=='^')
				base[bs-1].pow(base[bs]);
			else
			{
				if(sign[bs-1+parenth_depth])
				{
					base[bs-1].opp();
					sign[bs-1+parenth_depth]=false;
				}
				switch(operators[bs-1+parenth_depth])
				{
					case '+': base[bs-1]+=base[bs];break;
					case '-': base[bs-1]-=base[bs];break;
					case '*': base[bs-1]*=base[bs];break;
					case '/': base[bs-1]/=base[bs];break;
					case '%': base[bs-1]%=base[bs];break;
				}
			}
			if(errors::is_any_error) return false;
			base.pop_back();
			operators.pop_back();
			sign.pop_back();
			--bs;
		}
	return true;
	}

	string f_pos_to_str(int begin, int end, const string& _str)
	{
		string w;
		for(int i=begin; i<end; ++i)
			w+=_str[i];
	return w;
	}

	bool core(const string& _str, int begin, int end)
	{
		num emp;
		vector<num> base;
		vector<char> operators;
		vector<bool> sign;
		bool minus=false, var=false;
		int num_beg=begin, parenth_depth=0;
		for(int i=begin; i<end; ++i)
		{
			if(_str[i]=='!')
			{
				if(num_beg<i)
				{
					if(var)
					{
						if(var_base::read_var(f_pos_to_str(num_beg, i, _str), emp))
						{
							base.push_back(emp);
							sign.push_back(minus);
						}
						else
						{
							cout << "Unknown variable: " << f_pos_to_str(num_beg, i, _str) << endl;
							return false;
						}
					}
					else
					{
						base.push_back(num(_str, num_beg, i));
						sign.push_back(minus);
					}
					minus=false;
				}
				num_beg=i+1;
				base[base.size()-1].factorial();
				if(errors::is_any_error) return false;
			}
			else if(_str[i]=='-')
			{
				if(num_beg>=i)
				{
					if(i>0 && _str[i-1]=='!')
					{
						num_beg=i+1;
						operators.push_back(_str[i]);
					}
					else
					{
						minus=true;
						num_beg=i+1;
					}
				}
				else
				{
					if(var)
					{
						if(var_base::read_var(f_pos_to_str(num_beg, i, _str), emp)) base.push_back(emp);
						else
						{
							cout << "Unknown variable: " << f_pos_to_str(num_beg, i, _str) << endl;
							return false;
						}
					}
					else
						base.push_back(num(_str, num_beg, i));
					sign.push_back(minus);
					minus=false;
					if(!work(base, sign, operators, parenth_depth, pri(_str[i]))) return false;
					num_beg=i+1;
					operators.push_back(_str[i]);
				}
			}
			else if(_str[i]=='+' || _str[i]=='*' || _str[i]=='/' || _str[i]=='%' || _str[i]=='^')
			{
				if(num_beg<i)
				{
					if(var)
					{
						if(var_base::read_var(f_pos_to_str(num_beg, i, _str), emp)) base.push_back(emp);
						else
						{
							cout << "Unknown variable: " << f_pos_to_str(num_beg, i, _str) << endl;
							return false;
						}
					}
					else
						base.push_back(num(_str, num_beg, i));
					sign.push_back(minus);
					minus=false;
					if(!work(base, sign, operators, parenth_depth, pri(_str[i]))) return false;
					num_beg=i+1;
					operators.push_back(_str[i]);
				}
				else if(i>0 && _str[i-1]=='!')
				{
					num_beg=i+1;
					operators.push_back(_str[i]);
				}
				else num_beg=i+1;
			}
			else if(_str[i]=='(' || _str[i]==')')
			{
				if(_str[i]=='(')
				{
					operators.push_back('(');
					sign.push_back(minus);
					minus=false;
					++parenth_depth;
					num_beg=i+1;
				}
				else
				{
					if(var)
					{
						if(var_base::read_var(f_pos_to_str(num_beg, i, _str), emp))
						{
							base.push_back(emp);
							sign.push_back(minus);
						}
						else
						{
							cout << "Unknown variable: " << f_pos_to_str(num_beg, i, _str) << endl;
							return false;
						}
					}
					else
					{
						base.push_back(num(_str, num_beg, i));
						sign.push_back(minus);
					}
					minus=0;
					num_beg=i+1;
					if(!work(base, sign, operators, parenth_depth, pri(_str[i]))) return false;
					operators.pop_back();
					if(sign[sign.size()-1]) base[base.size()-1].opp();
					sign.pop_back();
					--parenth_depth;
					if(i<end-1 && _str[i+1]!=')' && _str[i+1]!='!')
					{
						if(!work(base, sign, operators, parenth_depth, pri(_str[i+1]))) return false;
						operators.push_back(_str[i+1]);
						++i;
						++num_beg;
					}
				}
			}
			else if(_str[i]>47 && _str[i]<58) var=false;
			else var=true;
		}
		if(num_beg<end)
		{
			if(var)
			{
				if(var_base::read_var(f_pos_to_str(num_beg, end, _str), emp))
				{
					base.push_back(emp);
					sign.push_back(minus);
				}
				else
				{
					cout << "Unknown variable: " << f_pos_to_str(num_beg, end, _str) << endl;
					return false;
				}
			}
			else
			{
				base.push_back(num(_str, num_beg, end));
				sign.push_back(minus);
			}
		}
		if(!work(base, sign, operators, parenth_depth, pri('0'))) return false;
		if(sign[0]) base[0].opp();
		var_base::swap_var("A", base[0]);
	return true;
	}
}