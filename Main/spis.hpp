#ifndef spis_hpp
#define spis_hpp
/*
__builtin_ctz - podaje numer najmłodszego zapalonego bitu (skrót od count trailing zeros)

__builtin_clz - podaje ilość zer wiodących, co po odjęciu od długości reprezentacji (32 lub 64 bity), daje nam pozycję najstarszego zapalonego bitu (skrót od count leading zeros)

__builtin_popcount - podaje ilość zapalonych bitów liczby
*/

#include <vector>
#include <iostream>

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
void buffer(string &w);
void convert(string &w);
bool identyfity(string &s);

//numeric-lib: errors
namespace errors
{
	bool are_not_errors();
}

#endif // spis_hpp
