#include "spis.hpp"
#include <complex>
#include <stack>

/*void czytaj(vector<int> &a)
{
	string s;
	char k=cin.get();
	while(k!=10 && k!=32)
	{
		s+=k;
		k=cin.get();
	}
	int j=s.size()-1, i=0;
	while(j>=0)
	{
		a.push_back(0);
		for(int k=max(0,j-L+1); k<=j; k++)
		{
			a[i]=10*a[i]+(s[k]-'0');
		}
		j-=L;
		i++;
	 }
}*/

void wypisz(vector<int> a)
{
	int k=a.size()-1;
	cout << a[k];
	for(int i=k-1; i>=0; i--)
	{
		cout.width(L);
		cout.fill('0');
		cout << a[i];
	}
}

void kas0(vector<int> &a)
{
	int o=0, i=a.size()-1;
	while(i>0 && a[i]==0)
	{
		o++;
		i--;
	}
	a.erase(a.end()-o, a.end());
}

vector<int> operator+(vector<int> a, vector<int> b)
{
	int al=a.size(), bl=b.size(), p=0;
	vector<int> w(max(bl,al));
	if(al<bl){a.swap(b);swap(al,bl);}
	else
	{
		for(int i=0; i<bl; i++)
		{
			w[i]=a[i]+b[i]+p;
			if(w[i]>=BASE){w[i]-=BASE;p=1;}
			else{p=0;}
		}
		for(int i=bl; i<al; i++)
		{
			w[i]=a[i]+p;
			if(w[i]>=BASE){w[i]-=BASE;p=1;}
			else{p=0;}
		}
		if(p>0)
		{
			w.push_back(p);
		}
	}
return w;
}

void operator+=(vector<int> &a, vector<int> b)
{
	int al=a.size(), bl=b.size(), p=0;
	if(al<bl){a.insert(a.end(), bl-al, 0);al=a.size();}
	for(int i=0; i<bl; i++)
	{
		a[i]+=b[i]+p;
		if(a[i]>=BASE){a[i]-=BASE;p=1;}
		else{p=0;}
	}
	for(int i=bl; i<al; i++)
	{
		a[i]+=p;
		if(a[i]>=BASE){a[i]-=BASE;p=1;}
		else{p=0;break;}
	}
	if(p>0)
	{
		a.push_back(p);
	}
}

vector<int> operator-(vector<int> a, vector<int> b)
{
	int al=a.size(), bl=b.size(), p=0;
	vector<int> w(al);
	for(int i=0; i<bl; i++)
	{
		w[i]=a[i]-b[i]-p;
		if(w[i]<0){w[i]+=BASE;p=1;}
		else{p=0;}
	}
	for(int i=bl; i<al; i++)
	{
		w[i]=a[i]-p;
		if(w[i]<0){w[i]+=BASE;p=1;}
		else{p=0;}
	}
	kas0(w);
return w;
}

void operator-=(vector<int> &a, vector<int> b)
{
	int al=a.size(), bl=b.size(), p=0;
	for(int i=0; i<bl; i++)
	{
		a[i]-=b[i]+p;
		if(a[i]<0){a[i]+=BASE;p=1;}
		else{p=0;}
	}
	for(int i=bl; i<al; i++)
	{
		a[i]-=p;
		if(a[i]<0){a[i]+=BASE;p=1;}
		else{break;}
	}
	kas0(a);
}

vector<int> operator*(vector<int> a, int b)
{
	int al=a.size();
	long long int g, p=0;
	vector<int> w(al);
	for(int i=0; i<al; i++)
	{
		g=(long long int)(a[i])*b+p;
		p=g/BASE;
		w[i]=g-p*BASE;
	}
	if(p>0){w.push_back(p);}
	kas0(w);
return w;
}

void operator*=(vector<int> &a, int b)
{
	int al=a.size();
	long long int g, p=0;
	for(int i=0; i<al; i++)
	{
		g=(long long int)(a[i])*b+p;
		p=g/BASE;
		a[i]=g-p*BASE;
	}
	if(p>0){a.push_back(p);}
	kas0(a);
}
// Old O(n^2) algorithm
vector<int> operator*(vector<int> a, vector<int> b)
{
	int al=a.size(), bl=b.size(), od=0;
	long long int g, p;
	vector<int> w(1), k;
	for(int i=0; i<bl; i++)
	{
		p=0;
		k.resize(al);
		for(int j=0; j<al; j++)
		{
			g=(long long int)(a[j])*b[i]+p;
			p=g/BASE;
			k[j]=g-p*BASE;
		}
		if(p>0){k.push_back(p);}
		kas0(k);
		int wl=w.size()-od, kl=k.size(), p=0;
		if(wl<kl){w.insert(w.end(), kl-wl, 0);wl=w.size()-od;}
		for(int j=0; j<kl; j++)
		{
			w[j+od]+=k[j]+p;
			if(w[j+od]>=BASE){w[j+od]-=BASE;p=1;}
			else{p=0;}
		}
		for(int j=kl; j<wl; j++)
		{
			w[j+od]+=p;
			if(w[j+od]>=BASE){w[j+od]-=BASE;p=1;}
			else{p=0;break;}
		}
		if(p>0)
		{
			w.push_back(p);
		}
		od++;
	}
	kas0(w);
return w;
}

void operator*=(vector<int> &a, vector<int> b)
{
	int al=a.size(), bl=b.size(), od=0;
	long long int g, p;
	vector<int> w(1), k;
	for(int i=0; i<bl; i++)
	{
		p=0;
		k.resize(al);
		for(int j=0; j<al; j++)
		{
			g=(long long int)(a[j])*b[i]+p;
			p=g/BASE;
			k[j]=g-p*BASE;
		}
		if(p>0){k.push_back(p);}
		kas0(k);
		int wl=w.size()-od, kl=k.size(), p=0;
		if(wl<kl){w.insert(w.end(), kl-wl, 0);wl=w.size()-od;}
		for(int j=0; j<kl; j++)
		{
			w[j+od]+=k[j]+p;
			if(w[j+od]>=BASE){w[j+od]-=BASE;p=1;}
			else{p=0;}
		}
		for(int j=kl; j<wl; j++)
		{
			w[j+od]+=p;
			if(w[j+od]>=BASE){w[j+od]-=BASE;p=1;}
			else{p=0;break;}
		}
		if(p>0)
		{
			w.push_back(p);
		}
		od++;
	}
	kas0(w);
	a.swap(w);
}
/* BUG in FFT implementation
#define cpx complex<double>

void DFT(vector<cpx> &omega, int pw, vector<short int> &a, vector<cpx> &b)
{
	if(a.size()==1){b[0]=cpx(static_cast<long double>(a[0]),0.0);return;}
	int n=a.size()>>1;
	vector<short int> t0(n), t1(n);
	for(unsigned int i=0; i<a.size(); i+=2)
	{
		t0[i>>1]=a[i];
		t1[i>>1]=a[i+1];
	}
	vector<short int>().swap(a);
	vector<cpx> y0(n), y1(n);
	DFT(omega, pw<<1, t0, y0);
	DFT(omega, pw<<1, t1, y1);
	int nr=0;
	for(int i=0; i<n; ++i)
	{
		cpx k=omega[nr]*y1[i];
		b[i]=y0[i]+k;
		b[i+n]=y0[i]-k;
		nr+=pw;
	}
}

void IDFT(vector<cpx> &omega, int pw, vector<cpx> &a)
{
	if(a.size()==1) return;
	int n=a.size()>>1;
	vector<cpx> t0(n), t1(n);
	for(unsigned int i=0; i<a.size(); i+=2)
	{
		t0[i>>1]=a[i];
		t1[i>>1]=a[i+1];
	}
	IDFT(omega, pw<<1, t0);
	IDFT(omega, pw<<1, t1);
	int nr=0;
	for(int i=0; i<n; ++i)
	{
		cpx k=omega[nr]*t1[i];
		a[i]=t0[i]+k;
		a[i+n]=t0[i]-k;
		nr+=pw;
	}
}

vector<int> /*fft*//*operator*(vector<int> a, vector<int> b)
{
	vector<short int> a1, b1;
	stack<char> st;
	int al=a.size(), bl=b.size();
	for(int i=0; i<al; ++i)
	{
		int lol=a[i];
		for(int j=0; j<9; ++j)
		{
			st.push(lol%10);
			lol/=10;
			if(st.size()==4)
			{
				short int u=0;
				while(!st.empty())
				{
					u*=10;
					u+=st.top();
					st.pop();
				}
				a1.push_back(u);
			}
		}
	}
	if(!st.empty())
	{
		short int u=0;
		while(!st.empty())
		{
			u*=10;
			u+=st.top();
			st.pop();
		}
		a1.push_back(u);
	}
	for(int i=0; i<bl; ++i)
	{
		int lol=b[i];
		for(int j=0; j<9; ++j)
		{
			st.push(lol%10);
			lol/=10;
			if(st.size()==4)
			{
				short int u=0;
				while(!st.empty())
				{
					u*=10;
					u+=st.top();
					st.pop();
				}
				b1.push_back(u);
			}
		}
	}
	if(!st.empty())
	{
		short int u=0;
		while(!st.empty())
		{
			u*=10;
			u+=st.top();
			st.pop();
		}
		b1.push_back(u);
	}
	vector<int>().swap(a);
	vector<int>().swap(b);
	int o=0, qw=a1.size()-1;
	while(qw>0 && a1[qw]==0)
	{
		++o;
		--qw;
	}
	a1.erase(a1.end()-o, a1.end());
	o=0;
	qw=b1.size()-1;
	while(qw>0 && b1[qw]==0)
	{
		++o;
		--qw;
	}
	b1.erase(b1.end()-o, b1.end());
	int p2=a1.size()+b1.size();
	if(__builtin_popcount(p2)>1) // ilość zapalonych bitów
	{
		p2=1<<(32-__builtin_clz(p2)); // pozycja najstarszego zapalonego bitu
	}
	a1.resize(p2);
	b1.resize(p2);
	int p1=p2>>1;
	vector<cpx> w(p2), w2(p2), omega(p1);
	cpx trol0=cpx(cos(M_PI/p1),sin(M_PI/p1)), trol1=cpx(1.0,0.0);
	for(int i=0; i<p1; ++i)
	{
		omega[i]=cpx(cos(M_PI*i/p1),sin(M_PI*i/p1));
	}
	DFT(omega, 1, a1, w);
	DFT(omega, 1, b1, w2);
	for(int i=0; i<p2; ++i)
	{
		w[i]*=w2[i];
	}
	vector<cpx>().swap(w2);
	trol0=cpx(1.0,0.0)/cpx(cos(M_PI/p1),sin(M_PI/p1));
	trol1=cpx(1.0,0.0);
	for(int i=0; i<p1; ++i)
	{
		omega[i]=cpx(1.0,0.0)/cpx(cos(M_PI*i/p1),sin(M_PI*i/p1));
	}
	IDFT(omega, 1, w);
	vector<short int> res(p2);
	unsigned int q=0;
	for(int i=0; i<p2; ++i)
	{
		q+=static_cast<unsigned int>(round(w[i].real()/p2));
		res[i]=q%10000;
		q/=10000;
	}
	o=0;
	qw=p2-1;
	while(qw>0 && res[qw]==0)
	{
		++o;
		--qw;
	}
	res.erase(res.end()-o, res.end());
	qw=res.size();
	for(int i=0; i<qw; ++i)
	{
		int lol=res[i];
		for(int j=0; j<4; ++j)
		{
			st.push(lol%10);
			lol/=10;
			if(st.size()==9)
			{
				int u=0;
				while(!st.empty())
				{
					u*=10;
					u+=st.top();
					st.pop();
				}
				a.push_back(u);
			}
		}
	}
	if(!st.empty())
	{
		int u=0;
		while(!st.empty())
		{
			u*=10;
			u+=st.top();
			st.pop();
		}
		a.push_back(u);
	}
	o=0;
	qw=a.size()-1;
	while(qw>0 && a[qw]==0)
	{
		++o;
		--qw;
	}
	a.erase(a.end()-o, a.end());
return a;
}

void /*fft*//*operator*=(vector<int> &a, vector<int> b)
{
	vector<short int> a1, b1;
	stack<char> st;
	int al=a.size(), bl=b.size();
	for(int i=0; i<al; ++i)
	{
		int lol=a[i];
		for(int j=0; j<9; ++j)
		{
			st.push(lol%10);
			lol/=10;
			if(st.size()==4)
			{
				short int u=0;
				while(!st.empty())
				{
					u*=10;
					u+=st.top();
					st.pop();
				}
				a1.push_back(u);
			}
		}
	}
	if(!st.empty())
	{
		short int u=0;
		while(!st.empty())
		{
			u*=10;
			u+=st.top();
			st.pop();
		}
		a1.push_back(u);
	}
	for(int i=0; i<bl; ++i)
	{
		int lol=b[i];
		for(int j=0; j<9; ++j)
		{
			st.push(lol%10);
			lol/=10;
			if(st.size()==4)
			{
				short int u=0;
				while(!st.empty())
				{
					u*=10;
					u+=st.top();
					st.pop();
				}
				b1.push_back(u);
			}
		}
	}
	if(!st.empty())
	{
		short int u=0;
		while(!st.empty())
		{
			u*=10;
			u+=st.top();
			st.pop();
		}
		b1.push_back(u);
	}
	vector<int>().swap(a);
	vector<int>().swap(b);
	int o=0, qw=a1.size()-1;
	while(qw>0 && a1[qw]==0)
	{
		++o;
		--qw;
	}
	a1.erase(a1.end()-o, a1.end());
	o=0;
	qw=b1.size()-1;
	while(qw>0 && b1[qw]==0)
	{
		++o;
		--qw;
	}
	b1.erase(b1.end()-o, b1.end());
	int p2=a1.size()+b1.size();
	if(__builtin_popcount(p2)>1) // ilość zapalonych bitów
	{
		p2=1<<(32-__builtin_clz(p2)); // pozycja najstarszego zapalonego bitu
	}
	a1.resize(p2);
	b1.resize(p2);
	int p1=p2>>1;
	vector<cpx> w(p2), w2(p2), omega(p1);
	cpx trol0=cpx(cos(M_PI/p1),sin(M_PI/p1)), trol1=cpx(1.0,0.0);
	for(int i=0; i<p1; ++i)
	{
		omega[i]=cpx(cos(M_PI*i/p1),sin(M_PI*i/p1));
	}
	DFT(omega, 1, a1, w);
	DFT(omega, 1, b1, w2);
	for(int i=0; i<p2; ++i)
	{
		w[i]*=w2[i];
	}
	vector<cpx>().swap(w2);
	trol0=cpx(1.0,0.0)/cpx(cos(M_PI/p1),sin(M_PI/p1));
	trol1=cpx(1.0,0.0);
	for(int i=0; i<p1; ++i)
	{
		omega[i]=cpx(1.0,0.0)/cpx(cos(M_PI*i/p1),sin(M_PI*i/p1));
	}
	IDFT(omega, 1, w);
	vector<short int> res(p2);
	unsigned int q=0;
	for(int i=0; i<p2; ++i)
	{
		q+=static_cast<unsigned int>(round(w[i].real()/p2));
		res[i]=q%10000;
		q/=10000;
	}
	o=0;
	qw=p2-1;
	while(qw>0 && res[qw]==0)
	{
		++o;
		--qw;
	}
	res.erase(res.end()-o, res.end());
	qw=res.size();
	for(int i=0; i<qw; ++i)
	{
		int lol=res[i];
		for(int j=0; j<4; ++j)
		{
			st.push(lol%10);
			lol/=10;
			if(st.size()==9)
			{
				int u=0;
				while(!st.empty())
				{
					u*=10;
					u+=st.top();
					st.pop();
				}
				a.push_back(u);
			}
		}
	}
	if(!st.empty())
	{
		int u=0;
		while(!st.empty())
		{
			u*=10;
			u+=st.top();
			st.pop();
		}
		a.push_back(u);
	}
	o=0;
	qw=a.size()-1;
	while(qw>0 && a[qw]==0)
	{
		++o;
		--qw;
	}
	a.erase(a.end()-o, a.end());
}

void fft_fast(vector<int> &a, vector<int> &b)
{
	vector<short int> a1, b1;
	stack<char> st;
	int al=a.size(), bl=b.size();
	for(int i=0; i<al; ++i)
	{
		int lol=a[i];
		for(int j=0; j<9; ++j)
		{
			st.push(lol%10);
			lol/=10;
			if(st.size()==4)
			{
				short int u=0;
				while(!st.empty())
				{
					u*=10;
					u+=st.top();
					st.pop();
				}
				a1.push_back(u);
			}
		}
	}
	if(!st.empty())
	{
		short int u=0;
		while(!st.empty())
		{
			u*=10;
			u+=st.top();
			st.pop();
		}
		a1.push_back(u);
	}
	for(int i=0; i<bl; ++i)
	{
		int lol=b[i];
		for(int j=0; j<9; ++j)
		{
			st.push(lol%10);
			lol/=10;
			if(st.size()==4)
			{
				short int u=0;
				while(!st.empty())
				{
					u*=10;
					u+=st.top();
					st.pop();
				}
				b1.push_back(u);
			}
		}
	}
	if(!st.empty())
	{
		short int u=0;
		while(!st.empty())
		{
			u*=10;
			u+=st.top();
			st.pop();
		}
		b1.push_back(u);
	}
	vector<int>().swap(a);
	int o=0, qw=a1.size()-1;
	while(qw>0 && a1[qw]==0)
	{
		++o;
		--qw;
	}
	a1.erase(a1.end()-o, a1.end());
	o=0;
	qw=b1.size()-1;
	while(qw>0 && b1[qw]==0)
	{
		++o;
		--qw;
	}
	b1.erase(b1.end()-o, b1.end());
	int p2=a1.size()+b1.size();
	if(__builtin_popcount(p2)>1) // ilość zapalonych bitów
	{
		p2=1<<(32-__builtin_clz(p2)); // pozycja najstarszego zapalonego bitu
	}
	a1.resize(p2);
	b1.resize(p2);
	int p1=p2>>1;
	vector<cpx> w(p2), w2(p2), omega(p1);
	cpx trol0=cpx(cos(M_PI/p1),sin(M_PI/p1)), trol1=cpx(1.0,0.0);
	for(int i=0; i<p1; ++i)
	{
		omega[i]=cpx(cos(M_PI*i/p1),sin(M_PI*i/p1));
	}
	DFT(omega, 1, a1, w);
	DFT(omega, 1, b1, w2);
	for(int i=0; i<p2; ++i)
	{
		w[i]*=w2[i];
	}
	vector<cpx>().swap(w2);
	trol0=cpx(1.0,0.0)/cpx(cos(M_PI/p1),sin(M_PI/p1));
	trol1=cpx(1.0,0.0);
	for(int i=0; i<p1; ++i)
	{
		omega[i]=cpx(1.0,0.0)/cpx(cos(M_PI*i/p1),sin(M_PI*i/p1));
	}
	IDFT(omega, 1, w);
	vector<short int> res(p2);
	unsigned int q=0;
	for(int i=0; i<p2; ++i)
	{
		q+=static_cast<unsigned int>(round(w[i].real()/p2));
		res[i]=q%10000;
		q/=10000;
	}
	o=0;
	qw=p2-1;
	while(qw>0 && res[qw]==0)
	{
		++o;
		--qw;
	}
	res.erase(res.end()-o, res.end());
	qw=res.size();
	for(int i=0; i<qw; ++i)
	{
		int lol=res[i];
		for(int j=0; j<4; ++j)
		{
			st.push(lol%10);
			lol/=10;
			if(st.size()==9)
			{
				int u=0;
				while(!st.empty())
				{
					u*=10;
					u+=st.top();
					st.pop();
				}
				a.push_back(u);
			}
		}
	}
	if(!st.empty())
	{
		int u=0;
		while(!st.empty())
		{
			u*=10;
			u+=st.top();
			st.pop();
		}
		a.push_back(u);
	}
	o=0;
	qw=a.size()-1;
	while(qw>0 && a[qw]==0)
	{
		++o;
		--qw;
	}
	a.erase(a.end()-o, a.end());
}

#undef cpx
*/
vector<int> operator/(vector<int> a, vector<int> b)
{
	if(a<b){vector<int> w(1);return w;}
	else if(b.size()==1 && b[0]==1) return a;
	int al=a.size(), bl=b.size(), iws=al-bl;
	vector<int> w(iws+1), g;
	while(iws>=0)
	{
		bool wr;
		if(al-iws<bl) wr=0;
		else if(al-iws>bl) wr=1;
		else
		{
			int i=bl-1;
			while(i>=0 && a[i+iws]==b[i])
			{
				i--;
			}
			if(i<0) wr=1;
			else if(a[i+iws]>b[i]) wr=1;
			else wr=0;
		}
		if(wr)
		{
			int p=0, k=999999999, c;
			while(p<k)
			{
				c=(p+k)/2+1;
				g=b;
				g*=c;
				int gl=g.size();
				if(al-iws<gl) wr=1;
				else if(al-iws>gl) wr=0;
				else
				{
					int i=gl-1;
					while(i>=0 && a[i+iws]==g[i])
					{
						i--;
					}
					if(i<0) wr=0;
					else if(g[i]>a[i+iws]) wr=1;
					else wr=0;
				}
				if(wr) k=c-1;
				else p=c;
			}
			g=b;
			g*=p;
			int gl=g.size(), prz=0;
			for(int i=0; i<gl; i++)
			{
				a[i+iws]-=g[i]+prz;
				if(a[i+iws]<0){a[i+iws]+=BASE;prz=1;}
				else{prz=0;}
			}
			for(int i=gl+iws; i<al; i++)
			{
				a[i]-=prz;
				if(a[i]<0){a[i]+=BASE;prz=1;}
				else{break;}
			}
			kas0(a);
			al=a.size();
			w[iws]=p;
		}
		iws--;
	}
	kas0(w);
return w;
}

void operator/=(vector<int> &a, vector<int> b)
{
	if(a<b){a.resize(1);a[0]=0;return;}
	else if(b.size()==1 && b[0]==1) return;
	int al=a.size(), bl=b.size(), iws=al-bl;
	vector<int> w(iws+1), g;
	while(iws>=0)
	{
		bool wr;
		if(al-iws<bl) wr=0;
		else if(al-iws>bl) wr=1;
		else
		{
			int i=bl-1;
			while(i>=0 && a[i+iws]==b[i])
			{
				i--;
			}
			if(i<0) wr=1;
			else if(a[i+iws]>b[i]) wr=1;
			else wr=0;
		}
		if(wr)
		{
			int p=0, k=999999999, c;
			while(p<k)
			{
				c=(p+k)/2+1;
				g=b;
				g*=c;
				int gl=g.size();
				if(al-iws<gl) wr=1;
				else if(al-iws>gl) wr=0;
				else
				{
					int i=gl-1;
					while(i>=0 && a[i+iws]==g[i])
					{
						i--;
					}
					if(i<0) wr=0;
					else if(g[i]>a[i+iws]) wr=1;
					else wr=0;
				}
				if(wr) k=c-1;
				else p=c;
			}
			g=b;
			g*=p;
			int gl=g.size(), prz=0;
			for(int i=0; i<gl; i++)
			{
				a[i+iws]-=g[i]+prz;
				if(a[i+iws]<0){a[i+iws]+=BASE;prz=1;}
				else{prz=0;}
			}
			for(int i=gl+iws; i<al; i++)
			{
				a[i]-=prz;
				if(a[i]<0){a[i]+=BASE;prz=1;}
				else{break;}
			}
			kas0(a);
			al=a.size();
			w[iws]=p;
		}
		iws--;
	}
	a.swap(w);
	kas0(a);
}

vector<int> operator%(vector<int> a, vector<int> b)
{
	int al=a.size(), bl=b.size(), iws=al-bl;
	vector<int> g;
	while(iws>=0)
	{
		bool wr;
		if(al-iws<bl) wr=0;
		else if(al-iws>bl) wr=1;
		else
		{
			int i=bl-1;
			while(i>=0 && a[i+iws]==b[i])
			{
				i--;
			}
			if(i<0) wr=1;
			else if(a[i+iws]>b[i]) wr=1;
			else wr=0;
		}
		if(wr)
		{
			int p=0, k=999999999, c;
			while(p<k)
			{
				c=(p+k)/2+1;
				g=b;
				g*=c;
				int gl=g.size();
				if(al-iws<gl) wr=1;
				else if(al-iws>gl) wr=0;
				else
				{
					int i=gl-1;
					while(i>=0 && a[i+iws]==g[i])
					{
						i--;
					}
					if(i<0) wr=0;
					else if(g[i]>a[i+iws]) wr=1;
					else wr=0;
				}
				if(wr) k=c-1;
				else p=c;
			}
			g=b;
			g*=p;
			int gl=g.size(), prz=0;
			for(int i=0; i<gl; i++)
			{
				a[i+iws]-=g[i]+prz;
				if(a[i+iws]<0){a[i+iws]+=BASE;prz=1;}
				else{prz=0;}
			}
			for(int i=gl+iws; i<al; i++)
			{
				a[i]-=prz;
				if(a[i]<0){a[i]+=BASE;prz=1;}
				else{break;}
			}
			kas0(a);
			al=a.size();
		}
		iws--;
	}
return a;
}

void operator%=(vector<int> &a, vector<int> b)
{
	int al=a.size(), bl=b.size(), iws=al-bl;
	vector<int> g;
	while(iws>=0)
	{
		bool wr;
		if(al-iws<bl) wr=0;
		else if(al-iws>bl) wr=1;
		else
		{
			int i=bl-1;
			while(i>=0 && a[i+iws]==b[i])
			{
				i--;
			}
			if(i<0) wr=1;
			else if(a[i+iws]>b[i]) wr=1;
			else wr=0;
		}
		if(wr)
		{
			int p=0, k=999999999, c;
			while(p<k)
			{
				c=(p+k)/2+1;
				g=b;
				g*=c;
				int gl=g.size();
				if(al-iws<gl) wr=1;
				else if(al-iws>gl) wr=0;
				else
				{
					int i=gl-1;
					while(i>=0 && a[i+iws]==g[i])
					{
						i--;
					}
					if(i<0) wr=0;
					else if(g[i]>a[i+iws]) wr=1;
					else wr=0;
				}
				if(wr) k=c-1;
				else p=c;
			}
			g=b;
			g*=p;
			int gl=g.size(), prz=0;
			for(int i=0; i<gl; i++)
			{
				a[i+iws]-=g[i]+prz;
				if(a[i+iws]<0){a[i+iws]+=BASE;prz=1;}
				else{prz=0;}
			}
			for(int i=gl+iws; i<al; i++)
			{
				a[i]-=prz;
				if(a[i]<0){a[i]+=BASE;prz=1;}
				else{break;}
			}
			kas0(a);
			al=a.size();
		}
		iws--;
	}
}

vector<int> operator^(vector<int> a, vector<int> b)
{
	vector<int> d(1), w;
	d[0]=1;
	if(b.size()==1 && b[0]==0){return d;}
	w=a;
	string bin;
	while(b>d)
	{
		if(__builtin_ctz(b[0])==0/*b[0]%2==1*/){bin='1'+bin;b[0]-=1;}
		else{bin='0'+bin;}
		int r=0, pom=0;
		for(int i=b.size()-1; i>=0; i--)
		{
			pom=b[i];
			{
				b[i]+=BASE*r;
				b[i]>>=1;
			}
			r=pom-(b[i]<<1);
		}
		if(b[b.size()-1]==0){b.pop_back();}
	}
	int bins=bin.size();
	for(int i=bins-1; i>=0; i++)
	{
		a*=a;//fft_fast(a,a);
		if(bin[i]) a*=w;//fft_fast(a,w);
	}
return w;
}

void operator^=(vector<int> &a, vector<int> b)
{
	if(b.size()==1 && b[0]==0){a.resize(1);a[0]=1;return;}
	vector<int> d(1), w=a;
	d[0]=1;
	vector<bool> bin;
	while(b>d)
	{
		if(__builtin_ctz(b[0])==0/*b[0]%2==1*/){bin.push_back(1);b[0]-=1;}
		else{bin.push_back(0);}
		int r=0, pom=0;
		for(int i=b.size()-1; i>=0; i--)
		{
			pom=b[i];
			{
				b[i]+=BASE*r;
				b[i]>>=1;
			}
			r=pom-(b[i]<<1);
		}
		if(b[b.size()-1]==0){b.pop_back();}
	}
	int bins=bin.size();
	for(int i=bins-1; i>=0; i--)
	{
		a*=a;//fft_fast(a,a);
		if(bin[i]) a*=w;//fft_fast(a,w);
	}
}

bool operator<(vector<int> a, vector<int> b)
{
	int al=a.size(), bl=b.size();
	if(bl<al) return 0;
	if(bl>al) return 1;
	int i=al-1;
	while(i>=0 && a[i]==b[i])
	{
		i--;
	}
	if(i<0 || a[i]>b[i]) return 0;
return 1;
}

bool operator>(vector<int> a, vector<int> b)
{
	int al=a.size(), bl=b.size();
	if(al<bl) return 0;
	if(al>bl) return 1;
	int i=al-1;
	while(i>=0 && a[i]==b[i])
	{
		i--;
	}
	if(i<0 || a[i]<b[i]) return 0;
return 1;
}

bool operator==(vector<int> a, vector<int> b)
{
	int al=a.size(), bl=b.size();
	if(al!=bl) return 0;
	int i=al-1;
	while(i>=0 && a[i]==b[i])
	{
		i--;
	}
	if(i<0) return 1;
return 0;
}

bool operator>=(vector<int> a, vector<int> b)
{
	int al=a.size(), bl=b.size();
	if(bl<al) return 1;
	if(bl>al) return 0;
	int i=al-1;
	while(i>=0 && a[i]==b[i])
	{
		i--;
	}
	if(i<0 || a[i]>b[i]) return 1;
return 0;
}

bool operator<=(vector<int> a, vector<int> b)
{
	int al=a.size(), bl=b.size();
	if(al<bl) return 1;
	if(al>bl) return 0;
	int i=al-1;
	while(i>=0 && a[i]==b[i])
	{
		i--;
	}
	if(i<0 || a[i]<b[i]) return 1;
return 0;
}

bool operator!=(vector<int> a, vector<int> b)
{
	int al=a.size(), bl=b.size();
	if(al!=bl) return 1;
	int i=al-1;
	while(i>=0 && a[i]==b[i])
	{
		i--;
	}
	if(i<0) return 0;
return 1;
}

vector<int> nwd(vector<int> a, vector<int> b)
{
	vector<int> d(1), c;
	while(b!=d)
	{
		c.swap(a);
		c%=b;
		a.swap(b);
		b.swap(c);
	}
return a;
}

void nwdp(vector<int> a, vector<int> b, vector<int> &k)
{
	vector<int> d(1), c;
	while(b!=d)
	{
		c.swap(a);
		c%=b;
		a.swap(b);
		b.swap(c);
	}
	k.swap(a);
}

int logcal(vector<int> a)
{
	int s=a.size(), w=L*(s-1), d;
	d=a[s-1];
	if(d<100000)
	{
		if(d<1000)
		{
			if(d<10){w+=1;}
			else if(d<100){w+=2;}
			else{w+=3;}
		}
		else
		{
			if(d<10000){w+=4;}
			else{w+=5;}
		}
	}
	else
	{
		if(d<10000000)
		{
			if(d<1000000){w+=6;}
			else{w+=7;}
		}
		else
		{
			if(d<100000000){w+=8;}
			else{w+=9;}
		}
	}
return w;
}
