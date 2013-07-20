#ifndef spis_hpp
#define spis_hpp
/*
__builtin_ctz - podaje numer najmłodszego zapalonego bitu (skrót od count trailing zeros)

__builtin_clz - podaje ilość zer wiodących, co po odjęciu od długości reprezentacji (32 lub 64 bity), daje nam pozycję najstarszego zapalonego bitu (skrót od count leading zeros)

__builtin_popcount - podaje ilość zapalonych bitów liczby
*/

#include <vector>
#include <iostream>

const int BASE=1000000000, L=9;

enum color{_yellow, _blue, _red, _green, _default};

using namespace std;

#ifdef WIN32

#include <windows.h>

#define color_yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define color_blue SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define color_red SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY)
#define color_green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define color_default SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED)
inline void hide_file()
{system("attrib +h .kalk_config.cfg");}
inline void nhide_file()
{system("attrib -h .kalk_config.cfg");}

#else

#define color_yellow cout << "\033[01;33m"
#define color_blue cout << "\033[01;34m"
#define color_red cout << "\033[01;31m"
#define color_green cout << "\033[01;32m"
#define color_default cout << "\033[00m"
inline void hide_file()
{;}
inline void nhide_file()
{;}

//main.cpp
int getch();

#endif

//funkcje-v.cpp
//void czytaj(vector<int> &a);
void wypisz(vector<int> a);
void kas0(vector<int> &a);
vector<int> operator+(vector<int> a, vector<int> b);
void operator+=(vector<int> &a, vector<int> b);
vector<int> operator-(vector<int> a, vector<int> b);
void operator-=(vector<int> &a, vector<int> b);
vector<int> operator*(vector<int> a, int b);
void operator*=(vector<int> &a, int b);
vector<int> operator*(vector<int> a, vector<int> b);
void operator*=(vector<int> &a, vector<int> b);
vector<int> operator/(vector<int> a, vector<int> b);
void operator/=(vector<int> &a, vector<int> b);
vector<int> operator%(vector<int> a, vector<int> b);
void operator%=(vector<int> &a, vector<int> b);
vector<int> operator^(vector<int> a, vector<int> b);
void operator^=(vector<int> &a, vector<int> b);
bool operator<(vector<int> a, vector<int> b);
bool operator>(vector<int> a, vector<int> b);
bool operator==(vector<int> a, vector<int> b);
bool operator>=(vector<int> a, vector<int> b);
bool operator<=(vector<int> a, vector<int> b);
bool operator!=(vector<int> a, vector<int> b);
vector<int> nwd(vector<int> a, vector<int> b);
void nwdp(vector<int> a, vector<int> b, vector<int> &k);
int logcal(vector<int> a);

//funkcje-d.cpp
struct dn
{
	vector<int> l, m;
	bool z;//true - dodatnia
	~dn(){vector<int>().swap(l);vector<int>().swap(m);}
};
//void czytaj(dn &a);
void wypisz(dn a, bool *outp);
dn operator+(dn a, dn b);
void operator+=(dn &a, dn b);
dn operator-(dn a, dn b);
void operator-=(dn &a, dn b);
dn operator*(dn a, dn b);
void operator*=(dn &a, dn b);
void fft_fast(vector<int> &a, vector<int> &b);
dn operator/(dn a, dn b);
void operator/=(dn &a, dn b);
dn operator%(dn a, dn b);
void operator%=(dn &a, dn b);
dn operator^(dn a, dn b);
void operator^=(dn &a, dn b);
bool operator>(dn a, dn b);
bool operator<(dn a, dn b);
bool operator==(dn a, dn b);
bool operator>=(dn a, dn b);
bool operator<=(dn a, dn b);
bool operator!=(dn a, dn b);
dn logc(dn a);
void factorial(dn &a);
bool isnERR();

//funkcje-k.cpp
void opp(dn &a);
bool don(string &s, int begin, int end);
dn zmien(string &s, int lp, int lk);
int pri(char a);
void dzial(vector<dn> &a, vector<bool> &mi, vector<char> &z, int &in, char znak);
string f_pos_to_str(int p, int k, string &s);
bool oper(string s, int start, int end);

//main.cpp
string to_string(int a);
void mcol(color c);
void help();
void scol();
void settings();
void buffer(string &w);
void convert(string &w);
bool identyfity(string &s);

#endif // spis_hpp

#ifndef var_base_hpp
#define var_base_hpp

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


namespace var_base
{
	ver::ver(): is(false)
	{
		for(short int i=0; i<256; i++)
			t[i]=0;
	}
	vector<ver> _v(1);
	queue<int> _free;
	bool is_there;

	void add_var(string s, dn w)
	{
		ver x;
		int k=0, sl=s.size();
		for(int i=0; i<sl; i++)
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
		vector<int>().swap(_v[k].w.l);
		vector<int>().swap(_v[k].w.m);
		_v[k].w.l.swap(w.l);
		_v[k].w.m.swap(w.m);
		_v[k].w.z=w.z;
	}

	bool remove_var(string s)
	{
		int k=0, sl=s.size();
		stack<int> grt;
		grt.push(0);
		for(int i=0; i<sl; i++)
		{
			if(_v[k].t[static_cast<int>(s[i])]==0) return 0;
			else
			{
				k=_v[k].t[static_cast<int>(s[i])];
				grt.push(k);
			}
		}
		if(!_v[k].is) return 0;
		_v[k].is=false;
		while(grt.size()>1)
		{
			sl--;
			for(short int i=0; i<256; i++)
				if(_v[k].t[i]!=0) return 1;
			grt.pop();
			_free.push(k);
			k=grt.top();
			_v[k].t[static_cast<int>(s[sl])]=0;
		}
	return 1;
	}

	bool read_var(string s, dn &w)
	{
		int k=0, sl=s.size();
		for(int i=0; i<sl; i++)
		{
			if(_v[k].t[static_cast<int>(s[i])]==0) return 0;
			else k=_v[k].t[static_cast<int>(s[i])];
		}
		if(!_v[k].is) return 0;
		w=_v[k].w;
	return 1;
	}
}

#include <fstream>

bool _color=1, output[]={0,0,1,1};

string to_string(int a)
{
	string c, b;
	if(a<0){a=-a;b+='-';}
	while(a>0)
	{
		c+=a%10+48;
		a/=10;
	}
	for(int i=c.size()-1; i>=0; i--)
		b+=c[i];
	if(b.size()==0) b="0";
return b;
}

void mcol(color c)
{
	if(!_color) return;
	if(c==_yellow) color_yellow;
	else if(c==_blue) color_blue;
	else if(c==_red) color_red;
	else if(c==_green) color_green;
	else if(c==_default) color_default;
}

void help()
{
	mcol(_default);
	cout << "----------------------------------------------\nCommand list:\ncol-off - switch off synax highlighting\ncol-on - switch on synax highlighting\nexit - quit\nhelp - this\nsettings - outputing settings\n----------------------------------------------\n";
}

void scol()
{
	fstream kalk_conf_file;
	nhide_file();
	kalk_conf_file.open(".kalk_config.cfg", ios::out);
	if(kalk_conf_file.good()) kalk_conf_file << output[0] << output[1] << output[2] << output[3] << _color;
	kalk_conf_file.close();
	hide_file();
}

//___________________________________________________
#ifdef WIN32

#include <conio.h>

void settings()
{
	mcol(_default);
	cout << "----------------------------------------------\n";
	cout << "1. Writing: Fraction (improper):  " << (output[0]?'Y':'N') << "\n";
	cout << "2. Writing: Mixed numeral:        " << (output[1]?'Y':'N') << "\n";
	cout << "3. Writing: Repeating decimal:    " << (output[2]?'Y':'N') << "\n";
	cout << "4. Writing: Scientific notation:  " << (output[3]?'Y':'N') << "\n";
	cout << "5. Writing: Synax highlighting:   " << (_color?'Y':'N') << "\n";
	cout << "Edyting option: put number (r - return): ";
	char z=getch();
	while(z!='r')
	{
		if(z<49 || z>53){cout << "\nWrong number!";getch();}
		else
		{
			cout << "\nNew value (y - yes, n - no): ";
			char o=getch();
			if(o=='y' || o=='Y')
			{
				if(z=='5') _color=1;
				else output[z-49]=1;
			}
			else if(o=='n' || o=='N')
			{
				if(z=='5') _color=0;
				else output[z-49]=0;
			}
		}
		cout << "\n----------------------------------------------\n";
		cout << "1. Writing: Fraction (improper):  " << (output[0]?'Y':'N') << "\n";
		cout << "2. Writing: Mixed numeral:        " << (output[1]?'Y':'N') << "\n";
		cout << "3. Writing: Repeating decimal:    " << (output[2]?'Y':'N') << "\n";
		cout << "4. Writing: Scientific notation:  " << (output[3]?'Y':'N') << "\n";
		cout << "5. Writing: Synax highlighting:   " << (_color?'Y':'N') << "\n";
		cout << "Edyting option: put number (r - return): ";
		z=getch();
	}
	cout << "\n----------------------------------------------\n";
	fstream kalk_conf_file;
	nhide_file();
	kalk_conf_file.open(".kalk_config.cfg", ios::out);
	if(kalk_conf_file.good()) kalk_conf_file << output[0] << output[1] << output[2] << output[3] << _color;
	kalk_conf_file.close();
	hide_file();
}

void buffer(string &w)
{
	w="";
	char z=cin.get();
	while(z!=10)
	{
		w+=z;
		z=cin.get();
	}
}

#else

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

void settings()
{
	mcol(_default);
	cout << "----------------------------------------------\n";
	cout << "1. Writing: Fraction (improper):  " << (output[0]?'Y':'N') << "\n";
	cout << "2. Writing: Mixed numeral:        " << (output[1]?'Y':'N') << "\n";
	cout << "3. Writing: Repeating decimal:    " << (output[2]?'Y':'N') << "\n";
	cout << "4. Writing: Scientific notation:  " << (output[3]?'Y':'N') << "\n";
	cout << "5. Writing: Synax highlighting:   " << (_color?'Y':'N') << "\n";
	cout << "Edyting option: put number (r - return): ";
	char z=getch();
	while(z!='r')
	{
		if(z<49 || z>53){cout << "\033[G\033[2KWrong number!";getch();}
		else
		{
			cout << "\033[G\033[2KNew value (y - yes, n - no): ";
			char o=getch();
			if(o=='y' || o=='Y')
			{
				if(z=='5') _color=1;
				else output[z-49]=1;
			}
			else if(o=='n' || o=='N')
			{
				if(z=='5') _color=0;
				else output[z-49]=0;
			}
		}
		cout << "\033[2K\033[F\033[2K\033[F\033[2K\033[F\033[2K\033[F\033[2K\033[F\033[2K\033[F";
		cout << "----------------------------------------------\n";
		cout << "1. Writing: Fraction (improper):  " << (output[0]?'Y':'N') << "\n";
		cout << "2. Writing: Mixed numeral:        " << (output[1]?'Y':'N') << "\n";
		cout << "3. Writing: Repeating decimal:    " << (output[2]?'Y':'N') << "\n";
		cout << "4. Writing: Scientific notation:  " << (output[3]?'Y':'N') << "\n";
		cout << "5. Writing: Synax highlighting:   " << (_color?'Y':'N') << "\n";
		cout << "Edyting option: put number (r - return): ";
		z=getch();
	}
	cout << "\033[G\033[2K----------------------------------------------\n";
	fstream kalk_conf_file;
	nhide_file();
	kalk_conf_file.open(".kalk_config.cfg", ios::out);
	if(kalk_conf_file.good()) kalk_conf_file << output[0] << output[1] << output[2] << output[3] << _color;
	kalk_conf_file.close();
	hide_file();
}

int kbhit(void)
{
	struct termios term, oterm;
	int fd=0;
	int c=0;
	tcgetattr(fd, &oterm);
	memcpy(&term, &oterm, sizeof(term));
	term.c_lflag=term.c_lflag & (!ICANON);
	term.c_cc[VMIN]=0;
	tcsetattr(fd, TCSANOW, &term);
	c=getchar();
	tcsetattr(fd, TCSANOW, &oterm);
	if(c!=-1)
	ungetc(c, stdin);
return ((c!=-1) ? 1:0);
}

int getch()
{
	static int ch = -1, fd = 0;
	struct termios neu, alt;
	fd = fileno(stdin);
	tcgetattr(fd, &alt);
	neu = alt;
	neu.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(fd, TCSANOW, &neu);
	ch = getchar();
	tcsetattr(fd, TCSANOW, &alt);
	return ch;
}

int getmaxx()
{
	int x=0;
	#ifdef TIOCGSIZE
	struct ttysize ts;
	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
	x=ts.ts_cols;
	#elif defined(TIOCGWINSZ)
	struct winsize ts;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
	x=ts.ws_col;
	#endif /* TIOCGSIZE */
return x;
}

int getmaxy()
{
	int y=0;
	#ifdef TIOCGSIZE
	struct ttysize ts;
	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
	y=ts.ts_lines;
	#elif defined(TIOCGWINSZ)
	struct winsize ts;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
	y=ts.ws_row;
	#endif /* TIOCGSIZE */
return y;
}

vector<string> name_base;

void buffer(string &w)
{
	vector<string> v=name_base;
	int poz=0, qy=name_base.size();
	string k;
	name_base.push_back(k);
	char KEY_UP[]={27,91,65,'\0'}, KEY_DOWN[]={27,91,66,'\0'}, KEY_LEFT[]={27,91,68,'\0'}, KEY_RIGHT[]={27,91,67,'\0'}, DELETE[]={27,91,51,126,'\0'}, BACKSPACE[]={127,'\0'};
	int width=getmaxx();
	char z=getch();
	while(1)
	{
		k="";
		k+=z;
		while(kbhit())
		{
			z=getch();
			k+=z;
		}
		if(k==BACKSPACE)
		{
			if(poz>0)
			{
				name_base[qy].erase(poz-1,1);
				/******* KEY_LEFT *******/
				if(poz%width==0)
				{
					cout << KEY_UP;
					for(int i=0; i<width; i++)
					{
						cout << KEY_RIGHT;
					}
				}
				else cout << KEY_LEFT;
				poz--;
				/******* END *******/
				int r=poz;
				for(; r<signed(name_base[qy].size()); r++)
					cout << name_base[qy][r];
				r++;
				cout << " ";
				if(r%width==0) cout << "\033[E";
				for(; r>poz; r--)
				{
					if(r%width==0)
					{
						cout << KEY_UP;
						for(int i=0; i<width; i++)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
				}
			}
		}
		else if(k==DELETE)
		{
			if(poz<signed(name_base[qy].size()))
			{
				name_base[qy].erase(poz,1);
				int r=poz;
				for(; r<signed(name_base[qy].size()); r++)
					cout << name_base[qy][r];
				r++;
				cout << " ";
				if(r%width==0) cout << "\033[E";
				for(; r>poz; r--)
				{
					if(r%width==0)
					{
						cout << KEY_UP;
						for(int i=0; i<width; i++)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
				}
			}
		}
		else if(k==KEY_UP)
		{
			if(qy>0)
			{
				qy--;
				while(poz>0)
				{
					cout << " ";
					if(poz+1%width==0)
					{
						cout << " \033[D";
						cout << KEY_UP;
						for(int i=0; i<width; i++)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
					if(poz%width==0)
					{
						cout << KEY_UP;
						for(int i=0; i<width; i++)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
					poz--;
				}
				poz=name_base[qy].size();
				cout << name_base[qy];
				if(poz%width==0) cout << " \033[D";
			}
		}
		else if(k==KEY_DOWN)
		{
			if(qy<signed(name_base.size())-1)
			{
				qy++;
				while(poz>0)
				{
					cout << " ";
					if(poz+1%width==0)
					{
						cout << " \033[D";
						cout << KEY_UP;
						for(int i=0; i<width; i++)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
					if(poz%width==0)
					{
						cout << KEY_UP;
						for(int i=0; i<width; i++)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
					poz--;
				}
				poz=name_base[qy].size();
				cout << name_base[qy];
				if(poz%width==0) cout << " \033[D";
			}
		}
		else if(k==KEY_LEFT)
		{
			if(poz>0)
			{
				if(poz%width==0)
				{
					cout << KEY_UP;
					for(int i=0; i<width; i++)
					{
						cout << KEY_RIGHT;
					}
				}
				else cout << KEY_LEFT;
				poz--;
			}
		}
		else if(k==KEY_RIGHT)
		{
			if(poz<signed(name_base[qy].size()))
			{
				if(poz%width-width==-1) cout << "\033[E";
				else cout << KEY_RIGHT;
				poz++;
			}
		}
		else
		{
			if(k[k.size()-1]==10)
			{
				k.erase(k.size()-1, 1);
				name_base[qy].insert(poz,k);
				break;
			}
			int r=poz;
			name_base[qy].insert(poz,k);
			for(; r<signed(name_base[qy].size()); r++)
				cout << name_base[qy][r];
			if(r%width==0) cout << " \033[D";
			for(; r>signed(k.size())+poz; r--)
			{
				if(r%width==0)
				{
					cout << KEY_UP;
					for(int i=0; i<width; i++)
					{
						cout << KEY_RIGHT;
					}
				}
				else cout << KEY_LEFT;
			}
			poz+=k.size();
			//cout << k;
		}
		z=getch();
	}
	while(poz<signed(name_base[qy].size()))
	{
		if(poz%width-width==-1) cout << "\033[E";
		else cout << KEY_RIGHT;
		poz++;
	}
	cout << endl;
	if(qy<signed(name_base.size())-1) name_base.pop_back();
	w=name_base[qy];
	v.push_back(w);
	name_base.swap(v);
}

#endif
//___________________________________________________

const bool zn[]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		  var[]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void convert(string &w)
{
	string k="";
	k.swap(w);
	if(k.size()>0)
	{
		unsigned int beg=1;
		w+=k[0];
		if(w[0]==',') w[0]='.';
		else if(w[0]==' ')
		{
			while(k[beg]==' ' && beg<k.size())
				beg++;
			if(beg<k.size()) w[0]=k[beg];
			else w="";
			beg++;
		}
		for(unsigned int i=beg; i<k.size(); i++)
		{
			if(k[i]==' ') continue;
			if(k[i]==',') k[i]='.';
			else if(w[w.size()-1]!='.' && k[i]!='.'
			        && ((w[w.size()-1]=='!' && !zn[static_cast<int>(k[i])] && k[i]!=')')
					|| (w[w.size()-1]==')' && !zn[static_cast<int>(k[i])] && k[i]!=')')
					|| (k[i]=='(' && w[w.size()-1]!='(' && !zn[static_cast<int>(w[w.size()-1])])
					|| (!var[static_cast<int>(w[w.size()-1])] && k[i]>47 && k[i]<58)
					|| (w[w.size()-1]>47 && w[w.size()-1]<58 && !var[static_cast<int>(k[i])]))) w+='*';
			w+=k[i];
		}
	}
}

bool identyfity(string &s)
{
	if(s.size()==0) return 0;
	string k;
	for(int i=0; i<static_cast<int>(s.size()); i++)
	{
		if(s[i]=='=') break;
		else k+=s[i];
	}
	if(k.size()==s.size()) k="";
	else
	{
		for(int i=0; i<static_cast<int>(k.size()); i++)
			if(var[static_cast<int>(s[i])] || s[i]=='.' || s[i]==',')
			{
				cout << "Wrong variable name!\n";
				return 0;
			}
	}
	if(!don(s,(k.size()==0 ? 0:k.size()+1),s.size())) return 0;
	if(!oper(s,(k.size()==0 ? 0:k.size()+1),s.size())) return 0;
	bool erro=isnERR();
	if(k.size()>0 && erro)
	{
		dn var;
		var_base::read_var("A", var);
		var_base::add_var(k, var);
		mcol(_blue);
		cout << k;
		mcol(_yellow);
		cout << " = ";
		return 1;
	}
return erro;
}

int main(int avg, char **arg)
{
	//ios::sync_with_stdio(0);
	bool arg1[]={1,1};
	for(int i=1; i<avg; i++)
	{
		if(arg[i][0]=='-' && arg[i][1]=='-' && arg[i][2]=='h' && arg[i][3]=='e' && arg[i][4]=='l' && arg[i][5]=='p'){cout << "Usage: Calc [options]\nOptions:\n  --help     Display this information\n  --version  Dispaly Calc version\n  -c         Run without synax highlighting\n  -w         Run in mode: using `-c' and don't display start information, it's make to read from file\n";return 0;}
		else if(arg[i][0]=='-' && arg[i][1]=='-' && arg[i][2]=='v' && arg[i][3]=='e' && arg[i][4]=='r' && arg[i][5]=='s' && arg[i][6]=='i' && arg[i][7]=='o' && arg[i][8]=='n'){cout << "Calc version 2.4\n";return 0;}
		else if(arg1[0] && arg[i][0]=='-' && arg[i][1]=='c' && arg[i][2]=='\0'){_color=0;arg1[0]=0;}
		else if(arg1[1] && arg[i][0]=='-' && arg[i][1]=='w' && arg[i][2]=='\0')
		{
			arg[0]=0;
			_color=0;
			output[3]=1;
			char znak=cin.get();
			while(znak!=EOF)
			{
				string s;
				while(znak!=10)
				{
					if(znak!=32)
					{
						s+=znak;
					}
					znak=cin.get();
				}
				if(s=="exit"){mcol(_default);return 0;}
				else if(s=="col-on"){_color=1;scol();}
				else if(s=="col-off"){_color=0;scol();color_default;}
				else if(s=="help") help();
				else if(s=="settings") settings();
				else
				{
					convert(s);
					if(identyfity(s))
					{
						dn a;
						var_base::read_var("A", a);
						wypisz(a, output);
						cout << "\n";
					}
				}
				znak=cin.get();
			}
			return 0;
		}
		else{cout << "Calc: unrecognized option `" << arg[i] << "\n";return 0;}
	}
	fstream kalk_conf_file;
	kalk_conf_file.open(".kalk_config.cfg", ios::in);
	char buff[]={'0','0','1','1','1','\0'};
	bool ey=0;
	if(kalk_conf_file.good())
	{
		kalk_conf_file.read(buff, 5);
		kalk_conf_file.close();
	}
	else ey=1;
	if(ey || kalk_conf_file.gcount()<5)
	{
		if(!ey) nhide_file();
		kalk_conf_file.open(".kalk_config.cfg", ios::out);
		if(kalk_conf_file.good()) kalk_conf_file << "00111";
		kalk_conf_file.close();
		hide_file();
	}
	output[0]=buff[0]-48;
	output[1]=buff[1]-48;
	output[2]=buff[2]-48;
	output[3]=buff[3]-48;
	_color=buff[4]-48;
	mcol(_blue);
	cout << "To quit write: exit\n";
	mcol(_green);
	/******* ADD 'A' TO VARIaBLES *******/
	var_base::_v.resize(2);
	var_base::_v[0].t['A']=1;
	var_base::_v[1].is=1;
	var_base::_v[1].w.l.push_back(0);
	var_base::_v[1].w.m.push_back(1);
	var_base::_v[1].w.z=1;
	/******* END *******/
	while(1)
	{
		string s;
		buffer(s);
		if(s=="exit"){mcol(_default);return 0;}
		else if(s=="col-on"){_color=1;scol();}
		else if(s=="col-off"){_color=0;scol();color_default;}
		else if(s=="help") help();
		else if(s=="settings") settings();
		else
		{
			convert(s);
			mcol(_red);
			if(identyfity(s))
			{
				dn a;
				var_base::read_var("A", a);
				mcol(_blue);
				wypisz(a, output);
				cout << "\n";
			}
		}
		mcol(_green);
	}
return 0;
}

#include <complex>

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
/*
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
*/
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

vector<int> /*fft*/operator*(vector<int> a, vector<int> b)
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

void /*fft*/operator*=(vector<int> &a, vector<int> b)
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
		fft_fast(a,a);
		if(bin[i]) fft_fast(a,w);
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
		fft_fast(a,a);
		if(bin[i]) fft_fast(a,w);
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
	fft_fast(a.l,h);
	h=a.m;h/=p;
	fft_fast(b.l,h);
	w.m=h;
	fft_fast(w.m,a.m);
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
	fft_fast(b.l,h);
	h=b.m;h/=p;
	fft_fast(a.l,h);
	fft_fast(a.m,h);
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
	fft_fast(a.l,h);
	h=a.m;h/=p;
	fft_fast(b.l,h);
	w.m=h;
	fft_fast(w.m,a.m);
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
	fft_fast(b.l,h);
	h=b.m;h/=p;
	fft_fast(a.l,h);
	fft_fast(a.m,h);
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
	fft_fast(w.l,b.l);
	w.m=a.m;
	fft_fast(w.m,b.m);
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
	fft_fast(a.l,b.l);
	fft_fast(a.m,b.m);
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
	fft_fast(w.l,b.l);
	w.m=a.l;
	fft_fast(w.m,b.m);
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
	fft_fast(a.l,b.m);
	fft_fast(a.m,b.l);
	vector<int> p;
	nwdp(a.l, a.m, p);
	a.l/=p;
	a.m/=p;
}

dn operator%(dn a, dn b)
{
	dn w;
	if(!(a.m.size()==1 && a.m[0]==1) || !(b.m.size()==1 && b.m[0]==1))
	{Error1=1;return w;}
	w.z=1;
	w.l=a.l%b.l;
	if((a.z==0 && b.z==1) || (a.z==b.z && b.z==0)){if(!(w.l.size()==1 && w.l[0]==0)){w.l=b.l-w.l;}}
return w;
}

void operator%=(dn &a, dn b)
{
	if(!(a.m.size()==1 && a.m[0]==1) || !(b.m.size()==1 && b.m[0]==1))
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
		fft_fast(a.l,d);
		d+=c;
	}
}

bool isnERR()
{
	if(Error0){cout << "Cannot divide by zero!\n";Error0=0;Error1=0;Error2=0;Error3=0;return 0;}
	if(Error1){cout << "Modulus division is only defined for integers\n";Error0=0;Error1=0;Error2=0;Error3=0;return 0;}
	if(Error2){cout << "In this version (2.4) power is only defined for integers!\n";Error0=0;Error1=0;Error2=0;Error3=0;return 0;}
	if(Error3){cout << "Factorial is only defined for natural numbers!\n";Error0=0;Error1=0;Error2=0;Error3=0;return 0;}
return 1;
}