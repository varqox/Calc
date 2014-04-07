#include "num.hpp"
#include "num_core.hpp"
#include <iostream>
#include <stack>
//for FFT
#include <cmath>
#include <complex>

namespace numeric_lib
{
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
		lli out=(w.size()-1)*LEN, end=w[w.size()-1];
		if(end<1000000000LL)
		{
			if(end<10000LL)
			{
				if(end<100LL)
				{
					if(end<10LL) ++out;
					else out+=2;
				}
				else
				{
					if(end<1000LL) out+=3;
					else out+=4;
				}
			}
			else
			{
				if(end<1000000LL)
				{
					if(end<100000LL) out+=5;
					else out+=6;
				}
				else
				{
					if(end<100000000LL)
					{
						if(end<10000000LL) out+=7;
						else out+=8;
					}
					else out+=9;
				}
			}
		}
		else
		{
			if(end<10000000000000LL)
			{
				if(end<100000000000LL)
				{
					if(end<10000000000LL) out+=10;
					else out+=11;
				}
				else
				{
					if(end<1000000000000LL) out+=12;
					else out+=13;
				}
			}
			else
			{
				if(end<1000000000000000LL)
				{
					if(end<100000000000000LL) out+=14;
					else out+=15;
				}
				else
				{
					if(end<100000000000000000LL)
					{
						if(end<10000000000000000LL) out+=16;
						else out+=17;
					}
					else out+=18;
				}
			}
		}
	return out;
	}

	void num::nat::kas0()
	{
		std::vector<lli>::iterator i=w.end()-1;
		while(i!=w.begin() && *i==0) --i;
		++i;
		w.erase(i, w.end());
	}

	num::nat& num::nat::operator++()
	{
		std::vector<lli>::iterator i=w.begin();
		while(i!=w.end())
		{
			++*i;
			if(*i<BASE) return *this;
			*i-=BASE;
			++i;
		}
		w.push_back(1);
	return *this;
	}

	num::nat& num::nat::operator--()
	{
		std::vector<lli>::iterator i=w.begin();
		while(i!=w.end())
		{
			--*i;
			if(*i>=0) break;
			*i+=BASE;
			++i;
		}
		kas0();
	return *this;
	}

	num::nat& num::nat::operator+=(const nat& _n)
	{
		unsigned int s=_n.w.size(), i=0;
		if(s>w.size()) w.resize(s);
		bool add=false;
		for(; i<s; ++i)
		{
			w[i]+=_n.w[i];
			if(add) ++w[i];
			if(w[i]>=BASE)
			{
				w[i]-=BASE;
				add=true;
			}
			else add=false;
		}
		if(add)
		{
			if(i==w.size()) w.push_back(add);
			else
			{
				for(;i<w.size(); ++i)
				{
					++w[i];
					if(w[i]<BASE) break;
					w[i]-=BASE;
				}
				if(i==w.size()) w.push_back(add);
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
			w[i]-=_n.w[i];
			if(add) --w[i];
			if(w[i]<0)
			{
				w[i]+=BASE;
				add=true;
			}
			else add=false;
		}
		if(add)
		{
			s=w.size();
			for(;i<s; ++i)
			{
				--w[i];
				if(w[i]>=0) break;
				w[i]+=BASE;
			}
		}
		kas0();
	return *this;
	}

	num::nat& num::nat::operator*=(const lli& _lcb)
	{
		if(_lcb==0){std::vector<lli>(1).swap(w);return *this;}
		lli p1=_lcb/BS2, p2=_lcb-p1*BS2, add=0, pom1, pom2, pom3, add1;
		for(std::vector<lli>::iterator i=w.begin(); i!=w.end(); ++i)
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
		if(add) w.push_back(add);
	return *this;
	}

	void num::nat::gen_mod(std::vector<nat::fmod>& _k) const
	{
		int wl=w.size();
		_k.resize(wl);
		for(int i=0; i<wl; ++i)
		{
			_k[i].pom1=w[i]/BS2;
			_k[i].pom2=w[i]-_k[i].pom1*BS2;
		}
	}

	num::nat& num::nat::mult(const lli& _lcb, const std::vector<nat::fmod>& _t)
	{
		if(_lcb==0){std::vector<lli>(1).swap(w);return *this;}
		int tl=_t.size();
		w.resize(tl);
		lli p1=_lcb/BS2, p2=_lcb-p1*BS2, add=0, pom3, add1;
		for(int i=0; i<tl; ++i)
		{
			w[i]=add+p2*_t[i].pom2;
			add1=add=0;
			if(w[i]>=BASE){++add;w[i]-=BASE;}
			add1=_t[i].pom1*p2+_t[i].pom2*p1;
			pom3=add1/BS2;
			w[i]+=(add1-pom3*BS2)*BS2;
			while(w[i]>=BASE)
			{
				++add;
				w[i]-=BASE;
			}
			add+=pom3+_t[i].pom1*p1;
		}
		if(add) w.push_back(add);
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
		int wl=w.size();
		_n.resize(wl<<1);
		for(int i=0; i<wl; ++i)
		{
			_n[(i<<1)+1]=w[i]/BS2;
			_n[(i<<1)]=w[i]-_n[(i<<1)+1]*BS2;
		}
		old_kas0(_n);
	}

	num::nat& num::nat::from_old_type(std::vector<int>& _n)
	{
		int nl=_n.size();
		w.resize((nl+1)>>1);
		for(int i=0; i<nl; i+=2)
			w[i>>1]=_n[i];
		for(int i=1; i<nl; i+=2)
			w[i>>1]+=_n[i]*BS2;
	return *this;
	}

	class num::nat::FFT
	{
	public:
		static inline lli div_mod(lli& a, const lli& m)
		{lli tmp=a;a/=m;return tmp-m*a;}

		typedef double D;

		static void omega(std::complex<D>* w, const int& n, bool t)
		{
			int to=n>>1;
			double constant = 2*M_PI/n;
			if(t)
				for(int i=0; i<to; ++i)
				{
					w[i]=std::complex<D>(cos(constant*i),sin(constant*i));
					w[i+to]=std::complex<D>(-w[i].real(),-w[i].imag());
				}
			else
				for(int i=0; i<to; ++i)
				{
					w[i]=std::complex<D>(cos(constant*i),sin(-constant*i));
					w[i+to]=std::complex<D>(-w[i].real(),-w[i].imag());
				}
		}

		static uint rev(uint x, uint l)
		{
			uint left = 1 << (l-1), right = 1, res = 0;
			do
			{
				if(x & left)
					res |= right;
				left >>= 1;
				right <<= 1;
			}
			while(left);
			return res;
		}

		static void DFT(std::complex<D>* A, std::complex<D>* w, const uint& size)
		{
			uint l = sizeof(size)*8 - 1 - __builtin_clz(size); // lg n
			for(uint i = 0, x; i < size; ++i)
			{
				x = rev(i, l);
				if(x > i)
					std::swap(A[i], A[x]);
			}
			for(uint m = 2, www = size >> 1; m <= size; m <<= 1, www >>= 1)
				for(uint k = 0; k < size; k += m)
					for(uint j = 0, m2 = m >> 1; j < m2; ++j)
					{
						std::complex<D> t = w[j * www] * A[k + j + m2], u = A[k + j];
						A[k + j] = u + t;
						A[k + j + m2] = u - t;
					}
		}

		static void fft(nat& a, const nat& b)
		{
			std::complex<D> *l1, *l2, *w;
			static const int FFT_BASE=10000;
			int d1, d2, t1, t2, FFT_base=4;
			t1=a.size();
			d1=t1/FFT_base;
			if(t1%FFT_base!=0) ++d1;
			t2=b.size();
			d2=t2/FFT_base;
			if(t2%FFT_base!=0) ++d2;
			uint d= (d1+d2) & (d1+d2-1) ? 1<<(32-__builtin_clz(d1+d2)) : (d1+d2);

			l1 = new std::complex<D> [d];
			l2 = new std::complex<D> [d];
			w = new std::complex<D> [d];

			for(uint i=0; i<d; ++i)
				l1[i]=l2[i]=std::complex<D> (0.0,0.0);
			{
				bool is_rest=false;
				unsigned int i=0, j=0;
				lli rest=0;
				for(; i<a.w.size()-1; ++i, ++j)
				{
					lli k=a.w[i];
					if(is_rest)
					{
						is_rest=false;
						l1[j]=rest+100*div_mod(k, 100);
						l1[++j]=div_mod(k, FFT_BASE);
						l1[++j]=div_mod(k, FFT_BASE);
						l1[++j]=div_mod(k, FFT_BASE);
						l1[++j]=div_mod(k, FFT_BASE);
					}
					else
					{
						is_rest=true;
						l1[j]=div_mod(k, FFT_BASE);
						l1[++j]=div_mod(k, FFT_BASE);
						l1[++j]=div_mod(k, FFT_BASE);
						l1[++j]=div_mod(k, FFT_BASE);
						rest=k;
					}
				}
				lli k=*--a.w.end();
				--j;
				if(is_rest) l1[++j]=rest+100*div_mod(k, 100);
				while(k>0)
					l1[++j]=div_mod(k, FFT_BASE);
			}
			{
				bool is_rest=false;
				unsigned int i=0, j=0;
				lli rest=0;
				for(; i<b.w.size()-1; ++i, ++j)
				{
					lli k=b.w[i];
					if(is_rest)
					{
						is_rest=false;
						l2[j]=rest+100*div_mod(k, 100);
						l2[++j]=div_mod(k, FFT_BASE);
						l2[++j]=div_mod(k, FFT_BASE);
						l2[++j]=div_mod(k, FFT_BASE);
						l2[++j]=div_mod(k, FFT_BASE);
					}
					else
					{
						is_rest=true;
						l2[j]=div_mod(k, FFT_BASE);
						l2[++j]=div_mod(k, FFT_BASE);
						l2[++j]=div_mod(k, FFT_BASE);
						l2[++j]=div_mod(k, FFT_BASE);
						rest=k;
					}
				}
				lli k=*--b.w.end();
				--j;
				if(is_rest) l2[++j]=rest+100*div_mod(k, 100);
				while(k>0)
					l2[++j]=div_mod(k, FFT_BASE);
			}
			omega(w, d, true);
			DFT(l1, w, d);
			DFT(l2, w, d);
			for(uint i=0; i<d; ++i)
				l1[i]*=l2[i];
			delete[] l2;

			omega(w, d, false);
			DFT(l1, w, d);
			delete[] w;

			D s=1.0/d;
			a.w.resize(d*2/9+1);
			int j=0, idx=0;
			const lli pow[9]={1LL, 10000LL, 100000000LL, 1000000000000LL, 10000000000000000LL, 100LL, 1000000LL, 10000000000LL, 100000000000000LL}, unpow[9]={1000000000000000000LL, 100000000000000LL, 10000000000LL, 1000000LL, 100LL, 10000000000000000LL, 1000000000000LL, 100000000LL, 10000LL};
			lli add=0;
			a.w[0]=0;
			for(uint i=0; i<d; ++i, ++idx)
			{
				if(idx==5)
				{
					++j;
					a.w[j]=add;
					add=0;
				}
				if(idx==9)
				{
					++j;
					a.w[j]=add;
					idx=add=0;
				}
				lli k=round(l1[i].real()*s);
				a.w[j]+=pow[idx]*div_mod(k,unpow[idx]);
				while(a.w[j]>=1000000000000000000LL)
				{
					++add;
					a.w[j]-=1000000000000000000LL;
				}
				add+=k;
			}
			a.kas0();
			delete[] l1;
		}
	};

	num::nat& num::nat::operator*=(const nat& b)
	{
		if(b==1) return *this;
		FFT::fft(*this, b);
		/*nat lol=0, _n;
		std::vector<nat::fmod> t;
		b.gen_mod(t);
		for(unsigned int q=0; q<w.size(); ++q)
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
		swap(lol);
		kas0();*/
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
						for(int i=0; i<gl; ++i)
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
						for(int i=0; i<gl; ++i)
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
		to_old_type(a);
		_n.to_old_type(b);
		div(a,b);
		from_old_type(a);
	return *this;
	}

	num::nat& num::nat::operator%=(const nat& _n)
	{
		if(_n==1)
		{
			std::vector<lli>(1,0).swap(w);
			return *this;
		}
		std::vector<int> a,b;
		to_old_type(a);
		_n.to_old_type(b);
		mod(a,b);
		from_old_type(a);
	return *this;
	}

	num::nat& num::nat::nwd(const nat& _n)
	{
		std::vector<int> a, b, c;
		to_old_type(a);
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
		from_old_type(a);
	return *this;
	}

	num::nat& num::nat::pow(const nat& _n)
	{
		if(_n.w.size()==1 && _n.w[0]==0)
		{
			std::vector<lli>(1,1).swap(w);
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
			operator*=(*this);
			if(bin.top()) operator*=(pow1);
			bin.pop();
		}
	return *this;
	}

	bool num::nat::operator<(const nat& _n) const
	{
		int i=w.size();
		if(static_cast<unsigned int>(i)<_n.w.size()) return true;
		else if(static_cast<unsigned int>(i)>_n.w.size()) return false;
		--i;
		while(i>=0 && w[i]==_n.w[i])
			--i;
		if(i<0) return false;
		if(w[i]>_n.w[i]) return false;
	return true;
	}

	bool num::nat::operator>(const nat& _n) const
	{return _n<*this;}

	bool num::nat::operator<=(const nat& _n) const
	{return !(_n<*this);}

	bool num::nat::operator>=(const nat& _n) const
	{return !operator<(_n);}

	bool num::nat::operator==(const nat& _n) const
	{
		int i=w.size();
		if(static_cast<unsigned int>(i)!=_n.w.size()) return false;
		--i;
		while(i>=0 && w[i]==_n.w[i])
			--i;
		if(i<0) return true;
	return false;
	}

	bool num::nat::operator!=(const nat& _n) const
	{return !operator==(_n);}
}