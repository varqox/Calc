#include "num.hpp"
#include "../Main/spis.hpp"
#include <cstring>
#include <stack>
#include <iostream>

namespace errors
{
	bool division_by_0=false,
	no_integer_modulo=false,
	no_integer_power=false,
	no_integer_factorial=false;
	bool are_not_errors()
	{
		bool ret=division_by_0|no_integer_modulo|no_integer_power|no_integer_factorial;
		if(division_by_0)
			cout << "Cannot divide by zero!\n";
		if(no_integer_modulo)
			cout << "Modulus division is only defined for integers!\n";
		if(no_integer_power)
			cout << "In this version (2.6.0) power is only defined for integers!\n";
		if(no_integer_factorial)
			cout << "Factorial is only defined for natural numbers!\n";
		division_by_0=no_integer_modulo=no_integer_power=no_integer_factorial=false;
	return !ret;
	}
}

namespace numeric_lib
{
	typedef long long int lli;
	const lli BASE=1000000000000000000LL, BS2=1000000000;
	const char LEN=18;

	class num::nat
	{
	public:
		struct fmod
		{
			lli pom1, pom2;
			fmod(){}
			~fmod(){}
		};
		std::vector<lli> w;
		nat(): w(1,0){}
		~nat(){}
		nat(const lli& _x): w(1,_x){}
		nat(const nat& _n): w(_n.w){}
		lli size() const;
		void kas0();
		void swap(nat& _n){this->w.swap(_n.w);}
		nat& operator++();
		nat& operator--();
		nat& operator+=(const nat&);
		nat& operator-=(const nat&);
		nat& operator*=(const lli&);
		void gen_mod(std::vector<fmod>&) const;
		nat& mult(const lli&, const std::vector<fmod>&);
		void to_old_type(std::vector<int>&) const;
		nat& from_old_type(std::vector<int>&);
		nat& operator*=(const nat&);
		nat& operator/=(const nat&);
		nat& operator%=(const nat&);
		nat& nwd(const nat&);
		nat& pow(const nat&);
		bool operator<(const nat&) const;
		bool operator>(const nat&) const;
		bool operator<=(const nat&) const;
		bool operator>=(const nat&) const;
		bool operator==(const nat&) const;
		bool operator!=(const nat&) const;
	};

	std::ostream& operator<<(std::ostream& os, const num::nat* _n)
	{
		int nl=_n->w.size();
		os << _n->w[--nl];
		for(int i=--nl; i>=0; --i)
		{
			os.width(LEN);
			os.fill('0');
			os << _n->w[i];
		}
	return os;
	}

	lli num::nat::size() const
	{
		lli w=(this->w.size()-1)*LEN, end=this->w[this->w.size()-1];
		if(end<1000000000LL)
		{
			if(end<10000LL)
			{
				if(end<100LL)
				{
					if(end<10LL) ++w;
					else w+=2;
				}
				else
				{
					if(end<1000LL) w+=3;
					else w+=4;
				}
			}
			else
			{
				if(end<1000000LL)
				{
					if(end<100000LL) w+=5;
					else w+=6;
				}
				else
				{
					if(end<100000000LL)
					{
						if(end<10000000LL) w+=7;
						else w+=8;
					}
					else w+=9;
				}
			}
		}
		else
		{
			if(end<10000000000000LL)
			{
				if(end<100000000000LL)
				{
					if(end<10000000000LL) w+=10;
					else w+=11;
				}
				else
				{
					if(end<1000000000000LL) w+=12;
					else w+=13;
				}
			}
			else
			{
				if(end<1000000000000000LL)
				{
					if(end<100000000000000LL) w+=14;
					else w+=15;
				}
				else
				{
					if(end<100000000000000000LL)
					{
						if(end<10000000000000000LL) w+=16;
						else w+=17;
					}
					else w+=18;
				}
			}
		}
	return w;
	}

	void num::nat::kas0()
	{
		std::vector<lli>::iterator i=this->w.end()-1;
		while(i!=this->w.begin() && *i==0) --i;
		++i;
		this->w.erase(i, this->w.end());
	}

	num::nat& num::nat::operator++()
	{
		std::vector<lli>::iterator i=this->w.begin();
		while(i!=this->w.end())
		{
			++*i;
			if(*i<BASE) return *this;
			*i-=BASE;
			++i;
		}
		this->w.push_back(1);
	return *this;
	}

	num::nat& num::nat::operator--()
	{
		std::vector<lli>::iterator i=this->w.begin();
		while(i!=this->w.end())
		{
			--*i;
			if(*i>=0) break;
			*i+=BASE;
			++i;
		}
		this->kas0();
	return *this;
	}

	num::nat& num::nat::operator+=(const nat& _n)
	{
		unsigned int s=_n.w.size(), i=0;
		if(s>this->w.size()) this->w.resize(s);
		bool add=false;
		for(; i<s; ++i)
		{
			this->w[i]+=_n.w[i];
			if(add) ++this->w[i];
			if(this->w[i]>=BASE)
			{
				this->w[i]-=BASE;
				add=true;
			}
			else add=false;
		}
		if(add)
		{
			if(i==this->w.size()) this->w.push_back(add);
			else
			{
				for(;i<this->w.size(); ++i)
				{
					++this->w[i];
					if(this->w[i]<BASE) break;
					this->w[i]-=BASE;
				}
				if(i==this->w.size()) this->w.push_back(add);
			}
		}
	return *this;
	}

	num::nat& num::nat::operator-=(const nat& _n)
	{
		int s=_n.w.size(), i=0;
		bool add=false;
		for(; i<s; ++i)
		{
			this->w[i]-=_n.w[i];
			if(add) --this->w[i];
			if(this->w[i]<0)
			{
				this->w[i]+=BASE;
				add=true;
			}
			else add=false;
		}
		if(add)
		{
			s=this->w.size();
			for(;i<s; ++i)
			{
				--this->w[i];
				if(this->w[i]>=0) break;
				this->w[i]+=BASE;
			}
		}
		this->kas0();
	return *this;
	}

	num::nat& num::nat::operator*=(const lli& _lcb)
	{
		if(_lcb==0){std::vector<lli>(1).swap(this->w);return *this;}
		lli p1=_lcb/BS2, p2=_lcb-p1*BS2, add=0, pom1, pom2, pom3, add1;
		for(std::vector<lli>::iterator i=this->w.begin(); i!=this->w.end(); ++i)
		{
			pom1=*i/BS2;
			pom2=*i-pom1*BS2;
			*i=add+p2*pom2;
			add1=add=0;
			if(*i>=BASE){++add;*i-=BASE;}
			add1=pom1*p2+pom2*p1;
			pom3=add1/BS2;
			*i+=(add1-pom3*BS2)*BS2;
			while(*i>=BASE)
			{
				++add;
				*i-=BASE;
			}
			add+=pom3+pom1*p1;
		}
		if(add) this->w.push_back(add);
	return *this;
	}

	void num::nat::gen_mod(std::vector<nat::fmod>& _k) const
	{
		int wl=this->w.size();
		_k.resize(wl);
		for(int i=0; i<wl; ++i)
		{
			_k[i].pom1=this->w[i]/BS2;
			_k[i].pom2=this->w[i]-_k[i].pom1*BS2;
		}
	}

	num::nat& num::nat::mult(const lli& _lcb, const std::vector<nat::fmod>& _t)
	{
		if(_lcb==0){std::vector<lli>(1).swap(this->w);return *this;}
		int tl=_t.size();
		this->w.resize(tl);
		lli p1=_lcb/BS2, p2=_lcb-p1*BS2, add=0, pom3, add1;
		for(int i=0; i<tl; ++i)
		{
			this->w[i]=add+p2*_t[i].pom2;
			add1=add=0;
			if(this->w[i]>=BASE){++add;this->w[i]-=BASE;}
			add1=_t[i].pom1*p2+_t[i].pom2*p1;
			pom3=add1/BS2;
			this->w[i]+=(add1-pom3*BS2)*BS2;
			while(this->w[i]>=BASE)
			{
				++add;
				this->w[i]-=BASE;
			}
			add+=pom3+_t[i].pom1*p1;
		}
		if(add) this->w.push_back(add);
	return *this;
	}

	void old_kas0(std::vector<int>& _n)
	{
		std::vector<int>::iterator i=_n.end()-1;
		while(i!=_n.begin() && *i==0) --i;
		++i;
		_n.erase(i, _n.end());
	}

	void num::nat::to_old_type(std::vector<int>& _n) const
	{
		int wl=this->w.size();
		_n.resize(wl<<1);
		for(int i=0; i<wl; ++i)
		{
			_n[(i<<1)+1]=this->w[i]/BS2;
			_n[(i<<1)]=this->w[i]-_n[(i<<1)+1]*BS2;
		}
		old_kas0(_n);
	}

	num::nat& num::nat::from_old_type(std::vector<int>& _n)
	{
		int nl=_n.size();
		this->w.resize((nl+1)>>1);
		for(int i=0; i<nl; i+=2)
			w[i>>1]=_n[i];
		for(int i=1; i<nl; i+=2)
			w[i>>1]+=_n[i]*BS2;
	return *this;
	}

	num::nat& num::nat::operator*=(const nat& b)
	{
		if(b==1) return *this;
		nat lol=0, _n;
		std::vector<nat::fmod> t;
		b.gen_mod(t);
		for(unsigned int q=0; q<this->w.size(); ++q)
		{
			_n.mult(w[q], t);//k.w.insert(k.w.begin(),i,0);//lol+=k;
			unsigned int s=_n.w.size(), i=0;
			if(s+q>lol.w.size()) lol.w.resize(s+q);
			bool add=false;
			for(; i<s; ++i)
			{
				lol.w[i+q]+=_n.w[i];
				if(add) ++lol.w[i+q];
				if(lol.w[i+q]>=BASE)
				{
					lol.w[i+q]-=BASE;
					add=true;
				}
				else add=false;
			}
			if(add)
			{
				if(i==s) lol.w.push_back(add);
				else
				{
					for(;i<s; ++i)
					{
						++lol.w[i+q];
						if(lol.w[i+q]<BASE) break;
						lol.w[i+q]-=BASE;
					}
					if(i==s) lol.w.push_back(add);
				}
			}
		}
		this->swap(lol);
		this->kas0();
	return *this;
	}

	void div(std::vector<int>& a, std::vector<int>& b)
	{
		int al=a.size(), bl=b.size(), iws=al-bl;
		if(bl==1 && b[0]==1) return;
		else
		{
			bool is_grader;
			if(al<bl) is_grader=false;
			else if(al>bl) is_grader=true;
			else
			{
				int i=bl-1;
				while(i>=0 && a[i+iws]==b[i])
					--i;
				if(i<0 || a[i+iws]>b[i]) is_grader=true;
				else is_grader=false;
			}
			if(!is_grader)
			{
				std::vector<int>(1,0).swap(a);
				return;
			}
		}
		std::vector<int> w(iws+1), g;
		while(iws>=0)
		{
			bool is_grader;
			if(al-iws<bl) is_grader=false;
			else if(al-iws>bl) is_grader=true;
			else
			{
				int i=bl-1;
				while(i>=0 && a[i+iws]==b[i])
					--i;
				if(i<0 || a[i+iws]>b[i]) is_grader=true;
				else is_grader=false;
			}
			if(is_grader)
			{
				lli inter;
				int down, up=0;
				while(is_grader)
				{
					inter=a[bl+iws-1];
					if(al-iws>bl) inter+=static_cast<lli>(BS2)*a[bl+iws];
					down=std::max(1LL,inter/(b[bl-1]+1));
					up+=down;
					//g=b*down;
					{
						g.resize(bl);
						int gl=bl;
						lli tmp, add=0;
						for (int i=0; i<gl; ++i)
						{
							tmp=static_cast<lli>(b[i])*down+add;
							add=tmp/BS2;
							g[i]=tmp-add*BS2;
						}
						if(add>0) g.push_back(add);
						old_kas0(g);
					}
					int gl=g.size();
					bool add=false;
					for(int i=0; i<gl; ++i)
					{
						a[i+iws]-=g[i]+add;
						if(a[i+iws]<0)
						{
							a[i+iws]+=BS2;
							add=true;
						}
						else add=false;
					}
					for(int i=gl+iws; i<al; ++i)
					{
						--a[i];
						if(a[i]<0) a[i]+=BS2;
						else break;
					}
					old_kas0(a);
					al=a.size();
					//Is a>b?
					if(al-iws<bl) is_grader=false;
					else if(al-iws>bl) is_grader=true;
					else
					{
						int i=bl-1;
						while(i>=0 && a[i+iws]==b[i])
							--i;
						if(i<0 || a[i+iws]>b[i]) is_grader=true;
						else is_grader=false;
					}
				}
				w[iws]=up;
			}
			--iws;
		}
		a.swap(w);
		old_kas0(a);
	}

	void mod(std::vector<int>& a, std::vector<int>& b)
	{
		int al=a.size(), bl=b.size(), iws=al-bl;
		if(bl==1 && b[0]==1)
		{
			std::vector<int>(1,0).swap(a);
			return;
		}
		else
		{
			bool is_grader;
			if(al<bl) is_grader=false;
			else if(al>bl) is_grader=true;
			else
			{
				int i=bl-1;
				while(i>=0 && a[i+iws]==b[i])
					--i;
				if(i<0 || a[i+iws]>b[i]) is_grader=true;
				else is_grader=false;
			}
			if(!is_grader) return;
		}
		std::vector<int> g;
		while(iws>=0)
		{
			bool is_grader;
			if(al-iws<bl) is_grader=false;
			else if(al-iws>bl) is_grader=true;
			else
			{
				int i=bl-1;
				while(i>=0 && a[i+iws]==b[i])
					--i;
				if(i<0 || a[i+iws]>b[i]) is_grader=true;
				else is_grader=false;
			}
			if(is_grader)
			{
				lli inter;
				int down;
				while(is_grader)
				{
					inter=a[bl+iws-1];
					if(al-iws>bl) inter+=static_cast<lli>(BS2)*a[bl+iws];
					down=std::max(1LL,inter/(b[bl-1]+1));
					//g=b*down;
					{
						g.resize(bl);
						int gl=bl;
						lli tmp, add=0;
						for (int i=0; i<gl; ++i)
						{
							tmp=static_cast<lli>(b[i])*down+add;
							add=tmp/BS2;
							g[i]=tmp-add*BS2;
						}
						if(add>0) g.push_back(add);
						old_kas0(g);
					}
					int gl=g.size();
					bool add=false;
					for(int i=0; i<gl; ++i)
					{
						a[i+iws]-=g[i]+add;
						if(a[i+iws]<0)
						{
							a[i+iws]+=BS2;
							add=true;
						}
						else add=false;
					}
					for(int i=gl+iws; i<al; ++i)
					{
						--a[i];
						if(a[i]<0) a[i]+=BS2;
						else break;
					}
					old_kas0(a);
					al=a.size();
					//Is a>b?
					if(al-iws<bl) is_grader=false;
					else if(al-iws>bl) is_grader=true;
					else
					{
						int i=bl-1;
						while(i>=0 && a[i+iws]==b[i])
							--i;
						if(i<0 || a[i+iws]>b[i]) is_grader=true;
						else is_grader=false;
					}
				}
			}
			--iws;
		}
		old_kas0(a);
	}

	num::nat& num::nat::operator/=(const nat& _n)
	{
		if(_n==1) return *this;
		std::vector<int> a,b;
		this->to_old_type(a);
		_n.to_old_type(b);
		div(a,b);
		this->from_old_type(a);
	return *this;
	}

	num::nat& num::nat::operator%=(const nat& _n)
	{
		if(_n==1)
		{
			std::vector<lli>(1,0).swap(this->w);
			return *this;
		}
		std::vector<int> a,b;
		this->to_old_type(a);
		_n.to_old_type(b);
		mod(a,b);
		this->from_old_type(a);
	return *this;
	}

	num::nat& num::nat::nwd(const nat& _n)
	{
		std::vector<int> a, b, c;
		this->to_old_type(a);
		_n.to_old_type(b);
		while(!(b.size()==1 && b[0]==0))
		{
			c.swap(a);
			mod(c,b);
			a.swap(b);
			b.swap(c);
		}
		std::vector<int>().swap(b);
		std::vector<int>().swap(c);
		this->from_old_type(a);
	return *this;
	}

	num::nat& num::nat::pow(const nat& _n)
	{
		if(_n.w.size()==1 && _n.w[0]==0)
		{
			std::vector<lli>(1,1).swap(this->w);
			return *this;
		}
		std::vector<lli> k(_n.w);
		std::stack<bool> bin;
		nat pow1(*this);
		while(!(k.size()==1 && k[0]==1))
		{
			bin.push(!__builtin_ctz(k[0])); //last bit
			bool add=false;
			for(int i=k.size()-1; i>=0; --i)
			{
				if(add) k[i]+=BASE;
				if(!__builtin_ctz(k[i])) add=true; //if(__builtin_ctz(k[i])==0)
				else add=false;
				k[i]>>=1;
			}
			if(!k[k.size()-1]) k.pop_back(); //if(k[k.size()-1]==0)
		}
		while(!bin.empty())
		{
			this->operator*=(*this);
			if(bin.top()) this->operator*=(pow1);
			bin.pop();
		}
	return *this;
	}

	bool num::nat::operator<(const nat& _n) const
	{
		int i=this->w.size();
		if(static_cast<unsigned int>(i)<_n.w.size()) return true;
		else if(static_cast<unsigned int>(i)>_n.w.size()) return false;
		--i;
		while(i>=0 && this->w[i]==_n.w[i])
			--i;
		if(i<0) return false;
		if(this->w[i]>_n.w[i]) return false;
	return true;
	}

	bool num::nat::operator>(const nat& _n) const
	{
	return _n<*this;
	}

	bool num::nat::operator<=(const nat& _n) const
	{
	return !(_n<*this);
	}

	bool num::nat::operator>=(const nat& _n) const
	{
	return !this->operator<(_n);
	}

	bool num::nat::operator==(const nat& _n) const
	{
		int i=this->w.size();
		if(static_cast<unsigned int>(i)!=_n.w.size()) return false;
		--i;
		while(i>=0 && this->w[i]==_n.w[i])
			--i;
		if(i<0) return true;
	return false;
	}

	bool num::nat::operator!=(const nat& _n) const
	{
	return !this->operator==(_n);
	}

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
	/*---------------- num ----------------*/

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

	num num::operator+(const num& _n)
	{
		num k(*this);
		nat trol;
		k.spwd(_n,trol);
		if(k.z==_n.z) k.l->operator+=(trol);
		else
		{
			if(k.l->operator>(trol))
				k.l->operator-=(trol);
			else
			{
				nat emp(trol);
				emp-=*k.l;
				k.l->swap(emp);
				if(k.l->w.size()==1 && k.l->w[0]==0) k.z=true;
				else k.z=!k.z;
			}
		}
		k.cut();
	return k;
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

	num num::operator-(const num& _n)
	{
		num k(*this);
		nat trol;
		k.spwd(_n,trol);
		if(k.z!=_n.z) k.l->operator+=(trol);
		else
		{
			if(k.l->operator>(trol))
				k.l->operator-=(trol);
			else
			{
				nat emp(trol);
				emp-=*k.l;
				k.l->swap(emp);
				if(k.l->w.size()==1 && k.l->w[0]==0) k.z=true;
				else k.z=!k.z;
			}
		}
		k.cut();
	return k;
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

	num num::operator*(const num& _n)
	{
		num k(*this);
		if(k.z==_n.z) k.z=true;
		else k.z=false;
		k.l->operator*=(*_n.l);
		k.m->operator*=(*_n.m);
		if(*k.l==0) k.z=true;
		k.cut();
	return k;
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

	num num::operator/(const num& _n)
	{
		if(*_n.l==0) errors::division_by_0=true;
		num k(*this);
		if(k.z==_n.z) k.z=true;
		else k.z=false;
		k.l->operator*=(*_n.m);
		k.m->operator*=(*_n.l);
		if(*k.l==0) k.z=true;
		k.cut();
	return k;
	}

	num& num::operator/=(const num& _n)
	{
		if(*_n.l==0) errors::division_by_0=true;
		if(this->z==_n.z) this->z=true;
		else this->z=false;
		this->l->operator*=(*_n.m);
		this->m->operator*=(*_n.l);
		if(*this->l==0) this->z=true;
		this->cut();
	return *this;
	}

	num num::operator%(const num& _n)
	{
		if(*_n.l==0) errors::division_by_0=true;
		else if(*_n.m!=1 || *this->m!=1) errors::no_integer_modulo=true;
		num k(*this);
		k.l->operator%=(*_n.l);
		if(!k.z && !(k.l->w.size()==1 && k.l->w[0]==0)) k+=(_n<0LL ? -_n:_n);
	return k;
	}

	num& num::operator%=(const num& _n)
	{
		if(*_n.l==0) errors::division_by_0=true;
		else if(*_n.m!=1 || *this->m!=1) errors::no_integer_modulo=true;
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
		if(*_n.m!=1) errors::no_integer_power=true;
		else if(*this->l==0 && (!_n.z || *_n.l==0))
		{
			errors::division_by_0=true;
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
		if(*this->m!=1) errors::no_integer_factorial=true;
		nat mx(1), i(2);
		std::vector<nat> lst;
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