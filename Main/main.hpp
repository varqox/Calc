#ifndef __Main_hpp
#define __Main_hpp
/*
__builtin_ctz - podaje numer najmłodszego zapalonego bitu (skrót od count trailing zeros)

__builtin_clz - podaje ilość zer wiodących, co po odjęciu od długości reprezentacji (32 lub 64 bity), daje nam pozycję najstarszego zapalonego bitu (skrót od count leading zeros)

__builtin_popcount - podaje ilość zapalonych bitów liczby

inline unsigned long int CeilToPowerOf2(unsigned long int x)
{return (x&x-1 ? 1ul<<(sizeof(unsigned long)*8-__builtin_clzl(x)):x);}
*/

#include <vector>
#include <iostream>

#define VERSION "2.7.2"
enum color{_yellow, _blue, _red, _green, _default};

using namespace std;

#ifdef WIN32

#include <windows.h>

#define color_yellow SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define color_blue SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define color_red SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY)
#define color_green SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define color_default SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED)

#else

#define color_yellow cout << "\033[01;33m"
#define color_blue cout << "\033[01;34m"
#define color_red cout << "\033[01;31m"
#define color_green cout << "\033[01;32m"
#define color_default cout << "\033[00m"

//main.cpp
int getch();

#endif

//main.cpp
string to_string(int a);
void mcol(color c);
void help();
void scol();
void settings();
void buffer(string&);
void convert(string&);
bool identyfity(string&);

//numeric-lib: errors
namespace errors
{
	extern bool is_any_error;
	bool are_not_errors();
}

#endif // __Main_hpp
