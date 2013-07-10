#include "spis.hpp"
#include "var_base.hpp"

bool przek=false;

void opp(dn &a)
{
	if(a.l.size()==1 && a.l[0]==0){a.z=1;return;}
	if(a.z==1) a.z=0;
	else a.z=1;
}

bool don(string &s, int begin, int end)
{
	end--;
	int br=0, z=0, num=0, krp=0, m=0;
	bool var=0;
	if(s[begin]=='!')
	{
		cout << "Wrong argument: '!'!\n";
		return false;
	}
	if(begin+1<end && (s[begin]=='-' || s[begin]=='+') && (s[begin+1]=='-' || s[begin+1]=='+'))
	{
		cout << "Wrong argument: '" << s[begin+1] << "'!\n";
		return false;
	}
	for(int i=begin; i<=end; i++)
	{
		if(s[i]=='(')
		{
			br++;
			num=0;
			var=false;
			m=0;
			krp=0;
			z=0;
		}
		else if(s[i]==')')
		{
			br--;
			if(br<0 || num==0)
			{
				cout << "Wrong parentheses layout!\n";
				return false;
			}
			z=0;
		}
		else if(s[i]=='.')
		{
			if(num==0 || krp>0 || i==end || s[i+1]<'0' || s[i+1]>'9' || var)
			{
				cout << "Wrong number writing!\n";
				return false;
			}
			krp++;
		}
		else if(s[i]=='+' || s[i]=='-')
		{
			if(m==0 && !(i==end || s[i+1]==')'))
			{
				if(z==0) z++;
				else m++;
			}
			else
			{
				cout << "Wrong argument: '" << s[i] << "'!\n";
				return false;
			}
			num=0;
			var=false;
			krp=0;
		}
		else if(s[i]=='*' || s[i]=='/' || s[i]=='%' || s[i]=='^')
		{
			z++;
			if(z>1 || num==0 || i==end || s[i+1]==')')
			{
				cout << "Wrong argument: '" << s[i] << "'!\n";
				return false;
			}
			num=0;
			var=false;
			krp=0;
			m=0;
		}
		else if(s[i]=='!')
		{
			z=0;
			m=0;
			num=1;
			krp=0;
			if(s[i-1]=='+' || s[i-1]=='-' || s[i-1]=='*' || s[i-1]=='/' || s[i-1]=='%' || s[i-1]=='^' || s[i-1]=='(')
			{
				cout << "Wrong argument: '!'!\n";
				return false;
			}
		}
		else if(s[i]>='0' && s[i]<='9')
		{
			num++;
			z=0;
			m=0;
		}
		else
		{
			num++;
			z=0;
			m=0;
			var=true;
		}
	}
	if(br!=0)
	{
		cout << "Wrong parentheses layout!\n";
		return false;
	}
	if(z>0)
	{
		char t;
		if(m>0) t=s[end-1];
		else t=s[end];
		cout << z << " " << m << "Wrong argument: '" << t << "'!\n";
		return false;
	}
return true;
}

dn zmien(string &s, int lp, int lk)
{
	dn a;
	a.m.push_back(10);
	a.z=1;
	int j=lk-1, i=0, m=lk;
	for(int y=lp; y<lk; y++)
	{
		if(s[y]=='.'){s.erase(y, 1);m=y;lk--;j--;przek=1;break;}
	}
	while(lp<lk-1 && s[lp]=='0')
		lp++;
	while(j>=lp)
	{
		a.l.push_back(0);
		for(int k=max(lp,j-L+1); k<=j; k++)
		{
			a.l[i]*=10;
			a.l[i]+=s[k]-'0';
		}
		j-=L;
		i++;
	}
	vector<int> ku(1);
	ku[0]=lk-m;
	a.m^=ku;
	nwdp(a.l, a.m, ku);
	a.l/=ku;
	a.m/=ku;
	return a;
}

int pri(char a)
{
	if(a=='^'){return 4;}
	if(a=='*' || a=='/' || a=='%'){return 3;}
	if(a=='+' || a=='-'){return 2;}
	if(a=='(' || a==')'){return 1;}
return 0;
}

void dzial(vector<dn> &a, vector<bool> &mi, vector<char> &z, int &in, char znak)
{
	int t=a.size()-1, f=pri(znak);
	if(f==4 || t<1) return;
	while(t>=1 && pri(z[t-1+in])>f)
	{
		if(mi[t+in]){opp(a[t]);mi[t+in]=0;}
		if(z[t-1+in]=='^'){a[t-1]^=a[t];}
		else
		{
			if(mi[t-1+in]){opp(a[t-1]);mi[t-1+in]=0;}
			if(z[t-1+in]=='+'){a[t-1]+=a[t];}
			else if(z[t-1+in]=='-'){a[t-1]-=a[t];}
			else if(z[t-1+in]=='*'){a[t-1]*=a[t];}
			else if(z[t-1+in]=='/'){a[t-1]/=a[t];}
			else if(z[t-1+in]=='%'){a[t-1]%=a[t];}
		}
		a.pop_back();
		z.pop_back();
		mi.pop_back();
		t--;
	}
	if(t>0 && f!=1 && f==pri(z[t-1+in]))
	{
		if(mi[t+in]){opp(a[t]);mi[t+in]=0;}
		if(z[t-1+in]=='^'){a[t-1]^=a[t];}
		else
		{
			if(mi[t-1+in]){opp(a[t-1]);mi[t-1+in]=0;}
			if(z[t-1+in]=='+'){a[t-1]+=a[t];}
			else if(z[t-1+in]=='-'){a[t-1]-=a[t];}
			else if(z[t-1+in]=='*'){a[t-1]*=a[t];}
			else if(z[t-1+in]=='/'){a[t-1]/=a[t];}
			else if(z[t-1+in]=='%'){a[t-1]%=a[t];}
		}
		a.pop_back();
		z.pop_back();
		mi.pop_back();
		t--;
	}
}

string f_pos_to_str(int p, int k, string &s)
{
	string w;
	for(int i=p; i<k; i++)
		w+=s[i];
return w;
}

bool oper(string s, int start, int end)
{
	dn emp;
	vector<dn> a;
	vector<char> z;
	vector<bool> mi;
	bool m=0, var=0;
	int t=start, in=0;
	for(int i=start; i<end; i++)
	{
		if(s[i]=='!')
		{
			if(t<i)
			{
				if(var)
				{
					if(var_base::read_var(f_pos_to_str(t, i, s), emp)){a.push_back(emp);mi.push_back(m);}
					else{cout << "Unknown variable: " << f_pos_to_str(t, i, s) << endl;return false;}
				}
				else
				{
					a.push_back(zmien(s, t, i));
					mi.push_back(m);
					if(przek){i--;end--;przek=false;}
				}
				m=0;
			}
			t=i+1;
			factorial(a[a.size()-1]);
		}
		else if(s[i]=='-')
		{
			if(t>=i)
			{
				if(i>0 && s[i-1]=='!')
				{
					t=i+1;
					z.push_back(s[i]);
				}
				else{m=1;t=i+1;}
			}
			else
			{
				if(var)
				{
					if(var_base::read_var(f_pos_to_str(t, i, s), emp)) a.push_back(emp);
					else{cout << "Unknown variable: " << f_pos_to_str(t, i, s) << endl;return false;}
				}
				else{a.push_back(zmien(s, t, i));if(przek){i--;end--;przek=0;}}
				mi.push_back(m);
				m=0;
				dzial(a, mi, z, in, s[i]);
				t=i+1;
				z.push_back(s[i]);
			}
		}
		else if(s[i]=='+' || s[i]=='*' || s[i]=='/' || s[i]=='%' || s[i]=='^')
		{
			if(t<i)
			{
				if(var)
				{
					if(var_base::read_var(f_pos_to_str(t, i, s), emp)) a.push_back(emp);
					else{cout << "Unknown variable: " << f_pos_to_str(t, i, s) << endl;return false;}
				}
				else
				{
					a.push_back(zmien(s, t, i));
					if(przek){i--;end--;przek=0;}
				}
				mi.push_back(m);
				m=0;
				dzial(a, mi, z, in, s[i]);
				t=i+1;
				z.push_back(s[i]);
			}
			else if(i>0 && s[i-1]=='!')
			{
				t=i+1;
				z.push_back(s[i]);
			}
			else t=i+1;
		}
		else if(s[i]=='(' || s[i]==')')
		{
			if(s[i]=='(')
			{
				z.push_back('(');
				mi.push_back(m);
				m=0;
				in++;
				t=i+1;
			}
			else
			{
				if(var)
				{
					if(var_base::read_var(f_pos_to_str(t, i, s), emp)){a.push_back(emp);mi.push_back(m);}
					else{cout << "Unknown variable: " << f_pos_to_str(t, i, s) << endl;return false;}
				}
				else
				{
					a.push_back(zmien(s, t, i));
					mi.push_back(m);
					if(przek) przek=0;
				}
				m=0;
				t=i+1;
				dzial(a, mi, z, in, s[i]);
				z.pop_back();
				if(mi[mi.size()-1]) opp(a[a.size()-1]);
				mi.pop_back();
				in--;
				if(i<end-1 && s[i+1]!=')' && s[i+1]!='!')
				{
					dzial(a, mi, z, in, s[i+1]);
					z.push_back(s[i+1]);
					i++;
					t++;
				}
			}
		}
		else if(s[i]>47 && s[i]<58) var=0;
		else var=1;
	}
	if(t<end)
	{
		if(var)
		{
			if(var_base::read_var(f_pos_to_str(t, end, s), emp)){a.push_back(emp);mi.push_back(m);}
			else{cout << "Unknown variable: " << f_pos_to_str(t, end, s) << endl;return false;}
		}
		else
		{
			a.push_back(zmien(s, t, end));
			mi.push_back(m);
			if(przek) przek=0;
		}
	}
	dzial(a, mi, z, in, '0');
	if(mi[0]) opp(a[0]);
	var_base::add_var("A", a[0]);
return true;
}
