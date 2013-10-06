#include "main.hpp"
#include "../Variable-lib/var_base.hpp"
#include "../Numeric-lib/num.hpp"
#include "../Calckit/calckit.hpp"
#include <fstream>

bool _color=true, output[]={false,false,true,true};
string directory;

string to_string(int a)
{
	string c, b;
	if(a<0){a=-a;b+='-';}
	while(a>0)
	{
		c+=a%10+48;
		a/=10;
	}
	for(int i=c.size()-1; i>=0; --i)
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

//___________________________________________________
#ifdef WIN32

inline void hide_file()
{system(("attrib +h "+directory+".Calc.cfg").c_str());}
inline void nhide_file()
{system(("attrib -h "+directory+".Calc.cfg").c_str());}

#include <conio.h>

void settings()
{
	mcol(_default);
	cout << "----------------------------------------------\n";
	cout << "1. Writing: Fraction (improper):  " << (output[0]?'Y':'N') << endl;
	cout << "2. Writing: Mixed numeral:        " << (output[1]?'Y':'N') << endl;
	cout << "3. Writing: Repeating decimal:    " << (output[2]?'Y':'N') << endl;
	cout << "4. Writing: Scientific notation:  " << (output[3]?'Y':'N') << endl;
	cout << "5. Writing: Synax highlighting:   " << (_color?'Y':'N') << endl;
	cout << "Edyting option: put number (r - return): ";
	cout.flush();
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
				if(z=='5') _color=true;
				else output[z-49]=true;
			}
			else if(o=='n' || o=='N')
			{
				if(z=='5') _color=false;
				else output[z-49]=false;
			}
		}
		cout << "\n----------------------------------------------" << endl;
		cout << "1. Writing: Fraction (improper):  " << (output[0]?'Y':'N') << endl;
		cout << "2. Writing: Mixed numeral:        " << (output[1]?'Y':'N') << endl;
		cout << "3. Writing: Repeating decimal:    " << (output[2]?'Y':'N') << endl;
		cout << "4. Writing: Scientific notation:  " << (output[3]?'Y':'N') << endl;
		cout << "5. Writing: Synax highlighting:   " << (_color?'Y':'N') << endl;
		cout << "Edyting option: put number (r - return): ";
		z=getch();
	}
	cout << "\n----------------------------------------------" << endl;
	fstream Calc_conf_file;
	nhide_file();
	Calc_conf_file.open((directory+".Calc.cfg").c_str(), ios::out);
	if(Calc_conf_file.good()) Calc_conf_file << output[0] << output[1] << output[2] << output[3] << _color;
	Calc_conf_file.close();
	ios_base::sync_with_stdio(!_color);
	hide_file();
}

void buffer(string &w)
{
	w="";
	char z=cin.get();
	while(z!='\n')
	{
		w+=z;
		z=cin.get();
	}
}

#else

inline void hide_file()
{;}
inline void nhide_file()
{;}

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void settings()
{
	mcol(_default);
	cout << "----------------------------------------------" << endl;
	cout << "1. Writing: Fraction (improper):  " << (output[0]?'Y':'N') << endl;
	cout << "2. Writing: Mixed numeral:        " << (output[1]?'Y':'N') << endl;
	cout << "3. Writing: Repeating decimal:    " << (output[2]?'Y':'N') << endl;
	cout << "4. Writing: Scientific notation:  " << (output[3]?'Y':'N') << endl;
	cout << "5. Writing: Synax highlighting:   " << (_color?'Y':'N') << endl;
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
				if(z=='5') _color=true;
				else output[z-49]=true;
			}
			else if(o=='n' || o=='N')
			{
				if(z=='5') _color=false;
				else output[z-49]=false;
			}
		}
		cout << "\033[2K\033[F\033[2K\033[F\033[2K\033[F\033[2K\033[F\033[2K\033[F\033[2K\033[F";
		cout << "----------------------------------------------\n";
		cout << "1. Writing: Fraction (improper):  " << (output[0]?'Y':'N') << endl;
		cout << "2. Writing: Mixed numeral:        " << (output[1]?'Y':'N') << endl;
		cout << "3. Writing: Repeating decimal:    " << (output[2]?'Y':'N') << endl;
		cout << "4. Writing: Scientific notation:  " << (output[3]?'Y':'N') << endl;
		cout << "5. Writing: Synax highlighting:   " << (_color?'Y':'N') << endl;
		cout << "Edyting option: put number (r - return): ";
		cout.flush();
		z=getch();
	}
	cout << "\033[G\033[2K----------------------------------------------" << endl;
	fstream Calc_conf_file;
	nhide_file();
	Calc_conf_file.open((directory+".Calc.cfg").c_str(), ios_base::out);
	if(Calc_conf_file.good()) Calc_conf_file << output[0] << output[1] << output[2] << output[3] << _color;
	Calc_conf_file.close();
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
	char KEY_UP[]={27, '[', 'A', '\0'}, KEY_DOWN[]={27, '[', 'B', '\0'}, KEY_RIGHT[]={27, '[', 'C', '\0'}, KEY_LEFT[]={27, '[', 'D', '\0'}, DELETE[]={27, '[', 51, 126, '\0'}, BACKSPACE[]={127, '\0'};
	int width=getmaxx();
	char z=getch();
	while(true)
	{
		k="";
		k+=z;
		while(kbhit())
		{
			if(z=='\n') break;
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
					for(int i=0; i<width; ++i)
					{
						cout << KEY_RIGHT;
					}
				}
				else cout << KEY_LEFT;
				--poz;
				/******* END *******/
				int r=poz;
				for(; r<signed(name_base[qy].size()); ++r)
					cout << name_base[qy][r];
				++r;
				cout << ' ';
				if(r%width==0) cout << "\033[E"; // move cursor 1 line down at begin
				for(; r>poz; --r)
				{
					if(r%width==0)
					{
						cout << KEY_UP;
						for(int i=0; i<width; ++i)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
				}
			}
			cout.flush();
		}
		else if(k==DELETE)
		{
			if(poz<signed(name_base[qy].size()))
			{
				name_base[qy].erase(poz,1);
				int r=poz;
				for(; r<signed(name_base[qy].size()); ++r)
					cout << name_base[qy][r];
				++r;
				cout << ' ';
				if(r%width==0){cout << "\033[E";cout.flush();} // move cursor 1 line down at begin
				for(; r>poz; --r)
				{
					if(r%width==0)
					{
						cout << KEY_UP;
						for(int i=0; i<width; ++i)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
				}
			}
			cout.flush();
		}
		else if(k==KEY_UP)
		{
			if(qy>0)
			{
				--qy;
				while(poz>0)
				{
					cout << ' ';
					if(poz+1%width==0)
					{
						cout << ' ' << KEY_LEFT;
						cout << KEY_UP;
						for(int i=0; i<width; ++i)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
					if(poz%width==0)
					{
						cout << KEY_UP;
						for(int i=0; i<width; ++i)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
					--poz;
				}
				poz=name_base[qy].size();
				cout << name_base[qy];
				if(poz%width==0) cout << ' ' << KEY_LEFT;
			}
			cout.flush();
		}
		else if(k==KEY_DOWN)
		{
			if(qy<signed(name_base.size())-1)
			{
				++qy;
				while(poz>0)
				{
					cout << ' ';
					if(poz+1%width==0)
					{
						cout << ' ' << KEY_LEFT;
						cout << KEY_UP;
						for(int i=0; i<width; ++i)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
					if(poz%width==0)
					{
						cout << KEY_UP;
						for(int i=0; i<width; ++i)
						{
							cout << KEY_RIGHT;
						}
					}
					else cout << KEY_LEFT;
					--poz;
				}
				poz=name_base[qy].size();
				cout << name_base[qy];
				if(poz%width==0) cout << ' ' << KEY_LEFT;
			}
			cout.flush();
		}
		else if(k==KEY_LEFT)
		{
			if(poz>0)
			{
				if(poz%width==0)
				{
					cout << KEY_UP;
					for(int i=0; i<width; ++i)
					{
						cout << KEY_RIGHT;
					}
				}
				else cout << KEY_LEFT;
				--poz;
			}
			cout.flush();
		}
		else if(k==KEY_RIGHT)
		{
			if(poz<signed(name_base[qy].size()))
			{
				if(poz%width-width==-1) cout << "\033[E"; // move cursor 1 line down at begin
				else cout << KEY_RIGHT;
				++poz;
			}
			cout.flush();
		}
		else
		{
			if(k[k.size()-1]=='\n')
			{
				k.erase(k.size()-1, 1);
				name_base[qy].insert(poz,k);
				break;
			}
			int r=poz;
			name_base[qy].insert(poz,k);
			for(; r<signed(name_base[qy].size()); ++r)
				cout << name_base[qy][r];
			if(r%width==0) cout << ' ' << KEY_LEFT;
			for(; r>signed(k.size())+poz; --r)
			{
				if(r%width==0)
				{
					cout << KEY_UP;
					for(int i=0; i<width; ++i)
					{
						cout << KEY_RIGHT;
					}
				}
				else cout << KEY_LEFT;
			}
			poz+=k.size();
			cout.flush();
			//cout << k;
		}
		z=getch();
	}
	while(poz<signed(name_base[qy].size()))
	{
		cout << name_base[qy][poz];
		// if(poz%width-width==-1) cout << "\033[E"; // move cursor 1 line down at begin
		// else cout << KEY_RIGHT;
		++poz;
	}
	cout << endl;
	if(qy<signed(name_base.size())-1) name_base.pop_back();
	w=name_base[qy];
	v.push_back(w);
	name_base.swap(v);
}

#endif
//___________________________________________________

void help()
{
	mcol(_default);
	cout << "----------------------------------------------\nCommand list:\ncol-off - switch off synax highlighting\ncol-on - switch on synax highlighting\nexit - quit\nhelp - this\nsettings - outputing settings\n----------------------------------------------" << endl;
}

void scol()
{
	fstream Calc_conf_file;
	nhide_file();
	Calc_conf_file.open((directory+".Calc.cfg").c_str(), ios_base::out);
	if(Calc_conf_file.good()) Calc_conf_file << output[0] << output[1] << output[2] << output[3] << _color;
	Calc_conf_file.close();
#ifdef WIN32
	ios_base::sync_with_stdio(!_color);
#endif
	hide_file();
}

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
				++beg;
			if(beg<k.size()) w[0]=k[beg];
			else w="";
			++beg;
		}
		for(unsigned int i=beg; i<k.size(); ++i)
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
	if(s.size()==0) return false;
	string k;
	for(int i=0; i<static_cast<int>(s.size()); ++i)
	{
		if(s[i]=='=') break;
		else k+=s[i];
	}
	if(k.size()==s.size()) k="";
	else
	{
		for(int i=0; i<static_cast<int>(k.size()); ++i)
			if(var[static_cast<int>(s[i])] || s[i]=='.' || s[i]==',')
			{
				cout << "Wrong variable name!" << endl;
				return false;
			}
	}
	if(!Calckit::parser(s,(k.size()==0 ? 0:k.size()+1),s.size())) return false;
	if(!Calckit::core(s,(k.size()==0 ? 0:k.size()+1),s.size()))
	{
		errors::are_not_errors();
		return false;
	}
	if(k.size()>0)
	{
		num var;
		var_base::read_var("A", var);
		var_base::swap_var(k, var);
		mcol(_blue);
		cout << k;
		mcol(_yellow);
		cout << " = ";
	}
return true;
}
namespace numeric_lib{
extern int stat[40];}
int main(int avg, char **arg)
{

#ifndef WIN32
	ios_base::sync_with_stdio(false);
#endif
	directory=arg[0];
	{
		int y=0;
		for(int i=directory.size()-1; i>=0; --i, ++y)
		#ifdef WIN32
			if(directory[i]=='/' || directory[i]=='\\') break;
		#else
			if(directory[i]=='/') break;
		#endif
		directory.erase(directory.size()-y,y);
	}
	fstream Calc_conf_file;
	Calc_conf_file.open((directory+".Calc.cfg").c_str(), ios_base::in);
	char buff[]={'0','0','1','1','1','\0'};
	bool ey=false;
	if(Calc_conf_file.good())
	{
		Calc_conf_file.read(buff, 5);
		Calc_conf_file.close();
	}
	else ey=true;
	if(ey || Calc_conf_file.gcount()<5)
	{
		if(!ey) nhide_file();
		Calc_conf_file.open((directory+".Calc.cfg").c_str(), ios_base::out);
		if(Calc_conf_file.good()) Calc_conf_file << "00111";
		Calc_conf_file.close();
		hide_file();
	}
	output[0]=buff[0]-48;
	output[1]=buff[1]-48;
	output[2]=buff[2]-48;
	output[3]=buff[3]-48;
	_color=buff[4]-48;
#ifdef WIN32
	ios_base::sync_with_stdio(!_color);
#endif
	bool arg1[]={true,true};
	num Answer;
	for(int i=1; i<avg; ++i)
	{
		if(arg[i][0]=='-' && arg[i][1]=='-' && arg[i][2]=='h' && arg[i][3]=='e' && arg[i][4]=='l' && arg[i][5]=='p'){cout << "Usage: Calc [options]\nOptions:\n  --help     Display this information\n  --version  Display Calc version\n  -c         Run without synax highlighting\n  -w         Run in mode: using `-c' and don't display start information, it's make to works with files" << endl;return 0;}
		else if(arg[i][0]=='-' && arg[i][1]=='-' && arg[i][2]=='v' && arg[i][3]=='e' && arg[i][4]=='r' && arg[i][5]=='s' && arg[i][6]=='i' && arg[i][7]=='o' && arg[i][8]=='n'){cout << "Calc version "VERSION"\n";return 0;}
		else if(arg1[0] && arg[i][0]=='-' && arg[i][1]=='c' && arg[i][2]=='\0'){_color=false;arg1[0]=false;}
		else if(arg1[1] && arg[i][0]=='-' && arg[i][1]=='w' && arg[i][2]=='\0')
		{
			arg[0]=0;
			_color=0;
			char znak=cin.get();
			while(znak!=EOF)
			{
				string s;
				while(znak!=10 && znak!=EOF)
				{
					if(znak!=32)
					{
						s+=znak;
					}
					znak=cin.get();
				}
				if(s=="exit"){mcol(_default);for(int i=0; i<40; ++i)
				cerr << i << ": " << numeric_lib::stat[i] << endl;return 0;}
				else if(s=="col-on"){_color=true;scol();}
				else if(s=="col-off"){_color=false;scol();color_default;}
				else if(s=="help") help();
				else if(s=="settings") settings();
				else
				{
					convert(s);
					if(identyfity(s))
					{
						var_base::read_var("A", Answer);
						Answer.output(output);
						cout << endl;
					}
				}
				znak=cin.get();
			}
			for(int i=0; i<40; ++i)
				cerr << i << ": " << numeric_lib::stat[i] << endl;
			return 0;
		}
		else{cout << "Calc: unrecognized option `" << arg[i] << endl;return 0;}
	}
	mcol(_blue);
	cout << "To quit write: exit" << endl;
	mcol(_green);
	/******* ADD 'A' TO VARIaBLES *******/
	var_base::_v.resize(2);
	var_base::_v[0].t[static_cast<int>('A')]=true;
	var_base::_v[1].is=true;
	var_base::_v[1].w=0;
	/******* END *******/
	while(true)
	{
		string s;
		buffer(s);
		if(s=="exit"){mcol(_default);return 0;}
		else if(s=="col-on"){_color=true;scol();}
		else if(s=="col-off"){_color=false;scol();color_default;}
		else if(s=="help") help();
		else if(s=="settings") settings();
		else
		{
			convert(s);
			mcol(_red);
			if(identyfity(s))
			{
				var_base::read_var("A", Answer);
				mcol(_blue);
				Answer.output(output);
				cout << endl;
			}
		}
		mcol(_green);
	}
return 0;
}
