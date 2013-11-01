#include <cstring>
#include <iostream>
#include <stack>
#include "../Main/main.hpp"
#include "num.hpp"
#include "num_core.hpp"

namespace errors
{
	bool is_any_error=false,
	division_by_0=false,
	no_integer_modulo=false,
	no_integer_power=false,
	no_integer_factorial=false;
	bool are_not_errors()
	{
		bool ret=is_any_error;
		if(division_by_0)
			cout << "Cannot divide by zero!" << endl;
		if(no_integer_modulo)
			cout << "Modulus division is only defined for integers!" << endl;
		if(no_integer_power)
			cout << "In this version (" VERSION ") power is only defined for integers!" << endl;
		if(no_integer_factorial)
			cout << "Factorial is only defined for non-negative integers!" << endl;
		is_any_error=division_by_0=no_integer_modulo=no_integer_power=no_integer_factorial=false;
	return !ret;
	}
}

namespace numeric_lib
{
	/*---------------- num ----------------*/
	std::string to_string(lli a)
	{
		std::stack<char> st;
		while(a>0)
		{
			st.push('0'+a%10);
			a/=10;
		}
		std::string w;
		while(!st.empty())
		{
			w+=st.top();
			st.pop();
		}
		if(w.empty()) w="0";
	return w;
	}

	num::num(): z(true), l(new nat(0)), m(new nat(1))
	{}

	num::~num()
	{delete l;delete m;}

	num::num(lli k): z(true), l(new nat), m(new nat(1))
	{
		if(k<0)
		{
			this->z=false;
			k=-k;
		}
		lli f=k/BASE;
		if(f>0) this->l->w.push_back(f);
		this->l->w[0]=k-f*BASE;
	}

	num::num(const char* cstr): l(new nat), m(new nat)
	{num(cstr,0,strlen(cstr)).swap(*this);}

	num::num(const char* cstr, unsigned int first, unsigned int least): z(true), l(new nat), m(new nat(1))
	{
		int begin=first, idx=0, point_idx=least;
		lli k;
		if(cstr[first]=='-'){this->z=false;++begin;}
		this->l->w.resize(1+(least-begin)/LEN);
		for(int i=least-1; i>=begin; i-=LEN, ++idx)
		{
			k=0;
			for(int j=std::max(i-LEN+1,begin); j<=i; ++j)
			{
				if(cstr[j]=='.')
				{
					point_idx=++j;
					k=0;
					for(int q=std::max(i-LEN,begin); q<=i; ++q)
						if(cstr[q]!='.')
						{
							k*=10;
							k+=cstr[q]-'0';
						}
					j=--i;
				}
				else
				{
					k*=10;
					k+=cstr[j]-'0';
				}
			}
			this->l->w[idx]=k;
		}
		this->l->kas0();
		if(this->l->w.size()==1 && this->l->w[0]==0) this->z=true;
		std::vector<lli>(1,10).swap(this->m->w);
		this->m->pow(least-point_idx);
		this->cut();
	}

	num::num(const std::string& _str): l(new nat), m(new nat)
	{num(_str,0,_str.size()).swap(*this);}

	num::num(const std::string& _str, unsigned int first, unsigned int least): z(true), l(new nat), m(new nat(1))
	{
		int begin=first, idx=0, point_idx=least;
		lli k;
		if(_str[first]=='-'){this->z=false;++begin;}
		this->l->w.resize(1+(least-begin)/LEN);
		for(int i=least-1; i>=begin; i-=LEN, ++idx)
		{
			k=0;
			for(int j=std::max(i-LEN+1,begin); j<=i; ++j)
			{
				if(_str[j]=='.')
				{
					point_idx=++j;
					k=0;
					for(int q=std::max(i-LEN,begin); q<=i; ++q)
						if(_str[q]!='.')
						{
							k*=10;
							k+=_str[q]-'0';
						}
					j=--i;
				}
				else
				{
					k*=10;
					k+=_str[j]-'0';
				}
			}
			this->l->w[idx]=k;
		}
		this->l->kas0();
		if(this->l->w.size()==1 && this->l->w[0]==0) this->z=true;
		std::vector<lli>(1,10).swap(this->m->w);
		this->m->pow(least-point_idx);
		this->cut();
	}

	num::num(const num& uli): z(uli.z), l(new nat(*uli.l)), m(new nat(*uli.m))
	{}

	num& num::operator=(const num& a)
	{
		this->z=a.z;
		delete this->l;
		delete this->m;
		this->l=new nat(*a.l);
		this->m=new nat(*a.m);
	return *this;
	}

	void num::swap(num& uli)
	{
		bool k;
		k=this->z;
		this->z=uli.z;
		uli.z=k;
		this->l->swap(*uli.l);
		this->m->swap(*uli.m);
	}

	std::string num::str() const
	{
		lli k;
		bool begin=this->z ? false:true;
		std::string str(this->l->size()+begin, '0');
		if(begin) str[0]='-';
		for(int idx=0, j, i=str.size()-1; i>=begin; i-=LEN, ++idx)
		{
			j=i;
			k=this->l->w[idx];
			while(k>0)
			{
				str[j]+=k%10;
				k/=10;
				--j;
			}
		}
	return str;
	}

	num& num::opp()
	{
		if(!(this->l->w.size()==1 && this->l->w[0]==0)) this->z=!this->z;
	return *this;
	}

	void num::spwd(const num& _n2, nat& l3)
	{
		nat NWD(*this->m);
		NWD.nwd(*_n2.m);
		this->m->operator/=(NWD);
		l3=*_n2.m;
		l3/=NWD;
		this->l->operator*=(l3);
		l3=*_n2.l;
		l3*=*this->m;
		this->m->operator*=(*_n2.m);
	}

	void num::cut()
	{
		if(*this->l==0)
		{
			std::vector<lli>(1,1).swap(this->m->w);
			return;
		}
		else if(*this->l==1 || *this->m==1) return;
		nat NWD(*this->l);
		NWD.nwd(*this->m);
		this->l->operator/=(NWD);
		this->m->operator/=(NWD);
	}

	num& num::operator+=(const num& _n)
	{
		nat trol;
		this->spwd(_n,trol);
		if(this->z==_n.z) this->l->operator+=(trol);
		else
		{
			if(this->l->operator>(trol))
				this->l->operator-=(trol);
			else
			{
				nat emp(trol);
				emp-=*this->l;
				this->l->swap(emp);
				if(this->l->w.size()==1 && this->l->w[0]==0) this->z=true;
				else this->z=!this->z;
			}
		}
		this->cut();
	return *this;
	}

	num& num::operator-=(const num& _n)
	{
		nat trol;
		this->spwd(_n,trol);
		if(this->z!=_n.z) this->l->operator+=(trol);
		else
		{
			if(this->l->operator>(trol))
				this->l->operator-=(trol);
			else
			{
				nat emp(trol);
				emp-=*this->l;
				this->l->swap(emp);
				if(this->l->w.size()==1 && this->l->w[0]==0) this->z=true;
				else this->z=!this->z;
			}
		}
		this->cut();
	return *this;
	}

	num& num::operator*=(const num& _n)
	{
		if(this->z==_n.z) this->z=true;
		else this->z=false;
		this->l->operator*=(*_n.l);
		this->m->operator*=(*_n.m);
		if(*this->l==0) this->z=true;
		this->cut();
	return *this;
	}

	num& num::operator/=(const num& _n)
	{
		if(*_n.l==0)
		{
			errors::is_any_error=errors::division_by_0=true;
			return *this;
		}
		if(this->z==_n.z) this->z=true;
		else this->z=false;
		this->l->operator*=(*_n.m);
		this->m->operator*=(*_n.l);
		if(*this->l==0) this->z=true;
		this->cut();
	return *this;
	}

	num& num::operator%=(const num& _n)
	{
		if(*_n.l==0)
		{
			errors::is_any_error=errors::division_by_0=true;
			return *this;
		}
		else if(*_n.m!=1 || *this->m!=1)
		{
			errors::is_any_error=errors::no_integer_modulo=true;
			return *this;
		}
		this->l->operator%=(*_n.l);
		if(!this->z && !(this->l->w.size()==1 && this->l->w[0]==0)) this->operator+=(_n<0LL ? -_n:_n);
	return *this;
	}

	bool num::operator>(const num& _n) const
	{
		if(this->z!=_n.z) return this->z;
		nat l1(*this->l), l2(*_n.l);
		l1*=*_n.m;
		l2*=*this->m;
		if(this->z) return l1>l2;
	return l1<l2;
	}

	bool num::operator<(const num& _n) const
	{return _n>*this;}

	bool num::operator>=(const num& _n) const
	{return !this->operator<(_n);}

	bool num::operator<=(const num& _n) const
	{return !this->operator>(_n);}

	bool num::operator==(const num& _n) const
	{
		if(this->z==_n.z && this->l->operator==(*_n.l) && this->m->operator==(*_n.m)) return true;
	return false;
	}

	bool num::operator!=(const num& _n) const
	{
		if(this->z==_n.z && this->l->operator==(*_n.l) && this->m->operator==(*_n.m)) return false;
	return true;
	}

	num& num::pow(const num& _n)
	{
		if(*_n.m!=1)
		{
			errors::is_any_error=errors::no_integer_power=true;
			return *this;
		}
		else if(*this->l==0 && (!_n.z || *_n.l==0))
		{
			errors::is_any_error=errors::division_by_0=true;
			return *this;
		}
		if(*_n.l==0)
		{
			this->operator=(1);
			return *this;
		}
		else if(*this->l==1 && *this->m==1)
		{
			if(!this->z && __builtin_ctz(_n.l->w[0])) this->z=true;
			return *this;
		}
		if(!this->z && __builtin_ctz(_n.l->w[0])) this->z=true;
		if(!_n.z) std::swap(this->l, this->m);
		this->l->pow(*_n.l);
		this->m->pow(*_n.l);
	return *this;
	}

	num& num::factorial()
	{
		if(!this->z || *this->m!=1)
		{
			errors::is_any_error=errors::no_integer_factorial=true;
			return *this;
		}
		nat mx(1), i(2);
		std::vector<nat> lst(1, nat(1));
		this->l->swap(mx);
		while(i<=mx)
		{
			lst.push_back(i);
			while(lst.size()>1 && (--lst.end())->w.size()>=(lst.end()-2)->w.size())
			{
				(lst.end()-2)->operator*=(*(--lst.end()));
				lst.pop_back();
			}
			++i;
		}
		while(lst.size()>1)
		{
			(lst.end()-2)->operator*=(*(--lst.end()));
			lst.pop_back();
		}
		this->l->swap(lst[0]);
		this->z=true;
	return *this;
	}

	void num::output(const bool* output)
	{
		nat g, wyk(*this->l);
		// vector<int> g(1), wyk=this->l;
		if(output[0])
		{
			if(!this->z)
			{
				mcol(_yellow);
				cout << "-";
				mcol(_blue);
			}
			cout << this->l;
			if(*this->m!=1)
			{
				mcol(_red);
				cout << "/";
				mcol(_blue);
				cout << this->m;
			}
		}
		if(output[1])
		{
			if(this->l->operator>(*this->m))
			{
				g=*this->l;
				g/=*this->m;
				this->l->operator-=(nat(g)*=*this->m);
				if(output[0] && *this->l!=0)
				{
					mcol(_yellow);
					cout << " = ";
					if(!this->z) cout << "-(";
					mcol(_blue);
					cout << &g;
					mcol(_yellow);
					cout << " + ";
					mcol(_blue);
					cout << this->l;
					mcol(_red);
					cout << "/";
					mcol(_blue);
					cout << this->m;
					if(!this->z)
					{
						mcol(_yellow);
						cout << ")";
						mcol(_blue);
					}
				}
				else if(!output[0])
				{
					mcol(_yellow);
					if(*this->l==0)
					{
						if(!this->z) cout << "-";
						mcol(_blue);
						cout << &g;
					}
					else
					{
						if(!this->z) cout << "-(";
						mcol(_blue);
						cout << &g;
						mcol(_yellow);
						cout << " + ";
						mcol(_blue);
						cout << this->l;
						mcol(_red);
						cout << "/";
						mcol(_blue);
						cout << this->m;
						if(!this->z)
						{
							mcol(_yellow);
							cout << ")";
							mcol(_blue);
						}
					}
				}

			}
			else if(!output[0])
			{
				if(!this->z)
				{
					mcol(_yellow);
					cout << "-";
					mcol(_blue);
				}
				cout << this->l;
				if(*this->m!=1)
				{
					mcol(_red);
					cout << "/";
					mcol(_blue);
					cout << this->m;
				}
				g=*this->l;
				g/=*this->m;
				this->l->operator-=(nat(g)*=*this->m);
			}
			else
			{
				g=*this->l;
				g/=*this->m;
				this->l->operator-=(nat(g)*=*this->m);
			}
		}
		if(output[2])
		{
			if(!output[1])
			{
				if(*this->m==1)
				{
					g.swap(*this->l);
					vector<lli>(1,0).swap(this->l->w);
				}
				else
				{
					g=*this->l;
					g/=*this->m;
					this->l->operator-=(nat(g)*=*this->m);
				}
			}
			if((output[0] || output[1]) && *this->l!=0)
			{
				mcol(_yellow);
				cout << " = ";
				if(!this->z) cout << "-";
				mcol(_blue);
				cout << &g;
			}
			else if(!output[0] && !output[1])
			{
				mcol(_yellow);
				if(!this->z) cout << "-";
				mcol(_blue);
				cout << &g;
			}
			if(*this->l!=0)
			{
				this->l->w.insert(this->l->w.begin(), 3, 0);
				this->l->operator/=(*this->m);
				string s, tos;
				for(int i=54-this->l->size(); i>0; --i)
					s+="0";
				s+=to_string(this->l->w[this->l->w.size()-1]);
				for(int i=this->l->w.size()-2; i>0; --i)
				{
					tos=to_string(this->l->w[i]);
					for(int j=tos.size(); j<LEN; ++j)
						s+="0";
					s+=tos;
				}
				//zaokrąglanie
				if(this->l->w[0]>(BASE>>1)-1)
				{
					for(int i=s.size()-1; i>=0; ++i)
					{
						++s[i];
						if(s[i]>58){s[i]-=10;}
						else break;
					}
				}
				//usuwanie końcowych zer
				for(int i=s.size()-1; i>=0 && s[i]=='0'; --i)
					s.erase(i, 1);
				if(!s.empty())
				{
					mcol(_red);
					cout << ".";
					mcol(_blue);
					cout << s;
				}
			}
		}
		if(output[3])
		{
			if(output[0] || output[1] || output[2])
			{
				mcol(_yellow);
				cout << " = ";
				mcol(_blue);
			}
			if(wyk.w.size()==0 || (wyk==0))
				cout << "0";
			else
			{
				if(!this->z)
				{
					mcol(_yellow);
					cout << "-";
					mcol(_blue);
				}
				int lg=wyk.w.size()-this->m->w.size()-3;
				string s, k;
				if(lg>0) wyk.w.erase(wyk.w.begin(), wyk.w.begin()+lg);
				else wyk.w.insert(wyk.w.begin(), -lg, 0);
				lg*=LEN;
				wyk/=*this->m;
				s+=to_string(wyk.w[wyk.w.size()-1]);
				for(int i=wyk.w.size()-2; i>=0; --i)
				{
					k=to_string(wyk.w[i]);
					for(int j=LEN-k.size(); j>0; --j)
						s+='0';
					s+=k;
				}
				lg+=s.size()-1;
				s.erase(11,s.size()-11);
				for(int i=s.size()-1; i>0 && s[i]=='0'; --i)
					s.erase(i, 1);
				cout << s[0];
				if(s.size()>1)
				{
					mcol(_red);
					cout << ".";
					mcol(_blue);
				}
				for(unsigned int i=1; i<s.size(); ++i)
					cout << s[i];
				mcol(_yellow);
				cout << "*";
				mcol(_blue);
				cout << "10";
				mcol(_red);
				cout << "^";
				if(lg<0){cout << "-";lg=-lg;}
				mcol(_blue);
				cout << lg;
			}
		}
	}

	num operator+(const num& a)
	{return num(a);}

	num operator-(const num& a)
	{
		num k(a);
		k.z=!k.z;
	return k;
	}

	num pow(const num& a, const num& b)
	{
		num w(a);
		w.pow(b);
	return w;
	}

	num factorial(const num& a)
	{
		num w(a);
		w.factorial();
	return w;
	}
}