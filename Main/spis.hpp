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
void czytaj(vector<int> &a);
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
	~dn(){}
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
