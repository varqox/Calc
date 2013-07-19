#include "spis.hpp"

bool Error0=0, Error1=0, Error2=0, Error3=0;

/*void czytaj(dn &a)
{
	a.l.resize(1,1);
	string s;
	char z=getchar();
	if(z==10 || z==32){a.l.resize(1);a.l[0]=0;a.z=1;return;}
	if(z=='-'){a.z=0;}
	else{a.z=1;s+=z;}
	z=getchar();
	while(z!=10 && z!=32)
	{
		s+=z;
		z=getchar();
	}
	if(s=="0"){a.l.resize(1);a.l[0]=0;a.z=1;return;}
	int j=s.size()-1, i=0;
	while(j>=0)
	{
		a.l.push_back(0);
		for(int k=max(0,j-L+1); k<=j; k++)
		{
			a.l[i]=10*a.l[i]+(s[k]-'0');
		}
		j-=L;
		i++;
	 }
}*/

void wypisz(dn a, bool *output)
{
	vector<int> g(1), wyk=a.l;
	if(output[0])
	{
		if(a.z==0){mcol(_yellow);cout << "-";mcol(_blue);}
		wypisz(a.l);
		if(!(a.m.size()==1 && a.m[0]==1))
		{
			mcol(_red);
			cout << "/";
			mcol(_blue);
			wypisz(a.m);
		}
	}
	if(output[1])
	{
		if(a.l>a.m)
		{
			g=a.l/a.m;
			a.l-=g*a.m;
			if(output[0] && !(a.l.size()==1 && a.l[0]==0))
			{
				mcol(_yellow);
				cout << " = ";
				if(!a.z) cout << "-(";
				mcol(_blue);
				wypisz(g);
				mcol(_yellow);
				cout << " + ";
				mcol(_blue);
				wypisz(a.l);
				mcol(_red);
				cout << "/";
				mcol(_blue);
				wypisz(a.m);
				if(!a.z){mcol(_yellow);cout << ")";mcol(_blue);}
			}
			else if(!output[0])
			{
				mcol(_yellow);
				if(a.l.size()==1 && a.l[0]==0)
				{
					if(!a.z) cout << "-";
					mcol(_blue);
					wypisz(g);
				}
				else
				{
					if(!a.z) cout << "-(";
					mcol(_blue);
					wypisz(g);
					mcol(_yellow);
					cout << " + ";
					mcol(_blue);
					wypisz(a.l);
					mcol(_red);
					cout << "/";
					mcol(_blue);
					wypisz(a.m);
					if(!a.z){mcol(_yellow);cout << ")";mcol(_blue);}
				}
			}

		}
		else if(!output[0])
		{
			if(a.z==0){mcol(_yellow);cout << "-";mcol(_blue);}
			wypisz(a.l);
			if(!(a.m.size()==1 && a.m[0]==1))
			{
				mcol(_red);
				cout << "/";
				mcol(_blue);
				wypisz(a.m);
			}
			g=a.l;
			g/=a.m;
			a.l-=g*a.m;
		}
		else
		{
			g=a.l;
			g/=a.m;
			a.l-=g*a.m;
		}
	}
	if(output[2])
	{
		if(!output[1])
		{
			if(a.m.size()==1 && a.m[0]==1)
			{
				g.swap(a.l);
				vector<int>(1,0).swap(a.l);
			}
			else
			{
				g=a.l;
				g/=a.m;
				a.l-=a.m*g;
			}
		}
		if((output[0] || output[1]) && !(a.l.size()==1 && a.l[0]==0))
		{
			mcol(_yellow);
			cout << " = ";
			if(!a.z) cout << "-";
			mcol(_blue);
			wypisz(g);
		}
		else if(!output[0] && !output[1])
		{
			mcol(_yellow);
			if(!a.z) cout << "-";
			mcol(_blue);
			wypisz(g);
		}
		if(!(a.l.size()==1 && a.l[0]==0))
		{
			a.l.insert(a.l.begin(), 5, 0);
			a.l/=a.m;
			string s, tos;
			for(int i=45-logcal(a.l); i>0; i--)
				s+="0";
			s+=to_string(a.l[a.l.size()-1]);
			for(int i=a.l.size()-2; i>0; i--)
			{
				tos=to_string(a.l[i]);
				for(int j=tos.size(); j<9; j++)
					s+="0";
				s+=tos;
			}
			//zaokrąglanie
			if(a.l[0]>499999999)
			{
				for(int i=s.size()-1; i>=0; i++)
				{
					s[i]++;
					if(s[i]>58){s[i]-=10;}
					else break;
				}
			}
			//usuwanie końcowych zer
			for(int i=s.size()-1; i>=0 && s[i]==48; i--)
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
		if(wyk.size()==0 || (wyk.size()==1 && wyk[0]==0))
		{
			cout << "0";
		}
		else
		{
			if(!a.z)
			{
				mcol(_yellow);
				cout << "-";
				mcol(_blue);
			}
			int lg=wyk.size()-a.m.size()-3;
			string s, k;
			if(lg>0) wyk.erase(wyk.begin(), wyk.begin()+lg);
			else wyk.insert(wyk.begin(), -lg, 0);
			lg*=9;
			wyk/=a.m;
			s+=to_string(wyk[wyk.size()-1]);
			for(int i=wyk.size()-2; i>=0; i--)
			{
				k=to_string(wyk[i]);
				for(int j=9-k.size(); j>0; j--)
					s+='0';
				s+=k;
			}
			lg+=s.size()-1;
			s.erase(11,s.size()-11);
			for(int i=s.size()-1; i>0 && s[i]==48; i--)
				s.erase(i, 1);
			cout << s[0];
			if(s.size()>1)
			{
				mcol(_red);
				cout << ".";
				mcol(_blue);
			}
			for(unsigned int i=1; i<s.size(); i++)
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

dn operator+(dn a, dn b)
{
	dn w;
	vector<int> p, h=b.m;
	nwdp(a.m, b.m, p);
	h/=p;
	a.l*=h;//fft_fast(a.l,h);
	h=a.m;h/=p;
	b.l*=h;//fft_fast(b.l,h);
	w.m=h;
	w.m*=a.m;//fft_fast(w.m,a.m);
	if(a.z==b.z)
	{
		w.z=a.z;
		w.l=a.l;w.l+=b.l;
	}
	else
	{
		if(a.l>b.l)
		{
			w.l=a.l;w.l-=b.l;
			if(a.z){w.z=1;}
			else{w.z=0;}
		}
		else
		{
			w.l=b.l;w.l-=a.l;
			if(w.l.size()==1 && w.l[0]==0){w.z=1;}
			else if(a.z){w.z=0;}
			else{w.z=1;}
		}
	}
	p=nwd(w.l, w.m);
	w.l/=p;
	w.m/=p;
return w;
}

void operator+=(dn &a, dn b)
{
	vector<int> p, h=a.m;
	nwdp(a.m, b.m, p);
	h/=p;
	b.l*=h;//fft_fast(b.l,h);
	h=b.m;h/=p;
	a.l*=h;//fft_fast(a.l,h);
	a.m*=h;//fft_fast(a.m,h);
	if(a.z==b.z){a.l+=b.l;}
	else
	{
		if(a.l>b.l)
		{
			a.l-=b.l;
			if(b.z){a.z=0;}
			else{a.z=1;}
		}
		else
		{
			a.l=b.l-a.l;
			if(a.l.size()==1 && a.l[0]==0){a.z=1;}
			else if(a.z){a.z=0;}
			else{a.z=1;}
		}
	}
	p=nwd(a.l, a.m);
	a.l/=p;
	a.m/=p;
}

dn operator-(dn a, dn b)
{
	if(!b.z){b.z=1;return a+b;}
	dn w;
	vector<int> p, h=b.m;
	nwdp(a.m, b.m, p);
	h/=p;
	a.l*=h;//fft_fast(a.l,h);
	h=a.m;h/=p;
	b.l*=h;//fft_fast(b.l,h);
	w.m=h;
	w.m*=a.m;//fft_fast(w.m,a.m);
	if(a.l<b.l)
	{
		if(a.z){w.l=b.l-a.l;}
		else{w.l=a.l+b.l;}
		w.z=0;
	}
	else
	{
		if(a.z){w.z=1;w.l=a.l-b.l;}
		else{w.z=0;w.l=a.l+b.l;}
	}
	nwdp(w.l, w.m, p);
	w.l/=p;
	w.m/=p;
return w;
}

void operator-=(dn &a, dn b)
{
	if(!b.z){b.z=1;a+=b;return;}
	vector<int> p, h=a.m;
	nwdp(a.m, b.m, p);
	h/=p;
	b.l*=h;//fft_fast(b.l,h);
	h=b.m;h/=p;
	a.l*=h;//fft_fast(a.l,h);
	a.m*=h;//fft_fast(a.m,h);
	if(a.l<b.l)
	{
		if(a.z){a.l=b.l-a.l;}
		else{a.l+=b.l;}
		a.z=0;
	}
	else
	{
		if(a.z){a.z=1;a.l-=b.l;}
		else{a.z=0;a.l+=b.l;}
	}
	nwdp(a.l, a.m, p);
	a.l/=p;
	a.m/=p;
}

dn operator*(dn a, dn b)
{
	dn w;
	if(a.z==b.z){w.z=1;}
	else{w.z=0;}
	w.l=a.l;
	w.l*=b.l;//fft_fast(w.l,b.l);
	w.m=a.m;
	w.m*=b.m;//fft_fast(w.m,b.m);
	vector<int> p;
	nwdp(w.l, w.m, p);
	w.l/=p;
	w.m/=p;
return w;
}

void operator*=(dn &a, dn b)
{
	if(a.z==b.z){a.z=1;}
	else{a.z=0;}
	a.l*=b.l;//fft_fast(a.l,b.l);
	a.m*=b.m;//fft_fast(a.m,b.m);
	vector<int> p;
	nwdp(a.l, a.m, p);
	a.l/=p;
	a.m/=p;
	if(a.l.size()==1 && a.l[0]==0) a.z=1;
}

dn operator/(dn a, dn b)
{
	dn w;
	if(b.l.size()==1 && b.l[0]==0){Error0=1;return a;}
	if(a.z==b.z){w.z=1;}
	else{w.z=0;}
	w.l=a.m;
	w.l*=b.l;//fft_fast(w.l,b.l);
	w.m=a.l;
	w.m*=b.m;//fft_fast(w.m,b.m);
	vector<int> p;
	nwdp(w.l, w.m, p);
	w.l/=p;
	w.m/=p;
return w;
}

void operator/=(dn &a, dn b)
{
	if(b.l.size()==1 && b.l[0]==0){Error0=1;return;}
	if(a.z==b.z){a.z=1;}
	else{a.z=0;}
	a.l*=b.m;//fft_fast(a.l,b.m);
	a.m*=b.l;//fft_fast(a.m,b.l);
	vector<int> p;
	nwdp(a.l, a.m, p);
	a.l/=p;
	a.m/=p;
}

dn operator%(dn a, dn b)
{
	dn w;
	if(b.l.size()==1 && b.l[0]==0){Error0=1;return a;}
	else if(!(a.m.size()==1 && a.m[0]==1) || !(b.m.size()==1 && b.m[0]==1))
	{Error1=1;return w;}
	w.z=1;
	w.l=a.l%b.l;
	if((a.z==0 && b.z==1) || (a.z==b.z && b.z==0)){if(!(w.l.size()==1 && w.l[0]==0)){w.l=b.l-w.l;}}
return w;
}

void operator%=(dn &a, dn b)
{
	if(b.l.size()==1 && b.l[0]==0){Error0=1;return;}
	else if(!(a.m.size()==1 && a.m[0]==1) || !(b.m.size()==1 && b.m[0]==1))
	{Error1=1;return;}
	a.l%=b.l;
	if((a.z==0 && b.z==1) || (a.z==b.z && b.z==0)){if(!(a.l.size()==1 && a.l[0]==0)){a.l=b.l-a.l;}}
	a.z=1;
}

dn operator^(dn a, dn b)
{
	dn w;
	if(!(b.m.size()==1 && b.m[0]==1)){Error2=1;}
	if(!a.z && b.l[0]%2==1){a.z=0;}
	else{a.z=1;}
	w.l=a.l^b.l;
	w.l=a.m^b.l;
	if(!b.z){w.l.swap(w.m);}
return w;
}

void operator^=(dn &a, dn b)
{
	if(!b.z){a.l.swap(a.m);}
	if(!(b.m.size()==1 && b.m[0]==1)){Error2=1;}
	if(!a.z && b.l[0]%2==1){a.z=0;}
	else{a.z=1;}
	a.l^=b.l;
	a.m^=b.l;
}

bool operator>(dn a, dn b)
{
	if(a.z==0 && b.z==1){return 0;}
	if(a.z==1 && b.z==0){return 1;}
	if(a.z==0 && b.z==0){return a.l<b.l;}
return a.l>b.l;
}

bool operator<(dn a, dn b)
{
	return b>a;
}

bool operator==(dn a, dn b)
{
	if(a.z==b.z){return a.l==b.l;}
return 0;
}

bool operator>=(dn a, dn b)
{
	return !(b>a);
}

bool operator<=(dn a, dn b)
{
	return !(a>b);
}

bool operator!=(dn a, dn b)
{
	return !(a==b);
}

dn logc(dn a)
{
	dn w;
	w.l.resize(1, 0);
	w.l[0]=logcal(w.l);
	w.z=a.z;
return w;
}

void factorial(dn &a)
{
	vector<int> w=a.l, d(1), c(1);
	if(a.z==0 || !(a.m.size()==1 && a.m[0]==1)){Error3=1;return;}
	a.l.resize(1,0);
	a.l[0]=1;
	c[0]=1;
	d[0]=1;
	while(d<=w)
	{
		a.l*=d;//fft_fast(a.l,d);
		d+=c;
	}
}

bool isnERR()
{
	if(Error0){cout << "Cannot divide by zero!\n";Error0=0;Error1=0;Error2=0;Error3=0;return 0;}
	if(Error1){cout << "Modulus division is only defined for integers!\n";Error0=0;Error1=0;Error2=0;Error3=0;return 0;}
	if(Error2){cout << "In this version (2.4.1) power is only defined for integers!\n";Error0=0;Error1=0;Error2=0;Error3=0;return 0;}
	if(Error3){cout << "Factorial is only defined for natural numbers!\n";Error0=0;Error1=0;Error2=0;Error3=0;return 0;}
return 1;
}

