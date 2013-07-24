#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <set>

using namespace std;

namespace hoffman_coding
{
	vector<bool> pref[256];

	struct node
	{
		const node *left, *right;
		unsigned char c;
		int val;
		node(): left(NULL), right(NULL){}
		//node(char z): left(NULL), right(NULL), c(z){}
		node(char z, int v): left(NULL), right(NULL), c(z), val(v){}
		node(const node* l, const node* r, int v): left(l), right(r), val(v){}
		~node(){}
		const node* get() const
		{return this;}
	};

	struct my_it
	{
		const node* wsk;
		my_it(const node* k): wsk(k){}
		~my_it(){}
		bool operator<(const my_it& _it) const
		{
			// if(this->wsk->val==_it.wsk->val) return this->wsk->get()<_it.wsk->get();
		return this->wsk->val<_it.wsk->val;
		}
	};

	unsigned int max_depth_id;

	void DFS(vector<bool> k, const node* x)
	{
		if(x->left==NULL)
		{
			static unsigned int max_depth=0;
			if(k.size()>max_depth)
			{
				max_depth=k.size();
				max_depth_id=x->c;
			}
			pref[static_cast<int>(x->c)].swap(k);
		}
		else
		{
			k.push_back(false);
			DFS(k,x->left);
			*(--k.end())=true;
			DFS(k,x->right);
		}
	}

	void output(fstream& file, const vector<bool>& vb)
	{
		static int out=0, l=0;
		if(vb.empty() && l>0)
		{
			for(int i=0; l<8; ++i)
			{
				out<<=1;
				++l;
				if(pref[max_depth_id][i]) ++out;
			}
			file.put(static_cast<unsigned char>(out));
			out=l=0;
		}
		for(int s=vb.size(), i=0; i<s; ++i)
		{
			out<<=1;
			++l;
			if(vb[i]) ++out;
			if(l==8)
			{
				file.put(static_cast<unsigned char>(out));
				out=l=0;
			}
		}
	}

	int main(string arg1, string file_name, string out_name="")
	{
		fstream file, out;
		const node *root, *actual;
		if(arg1=="a")
		{
			file.open(file_name.c_str(), ios_base::in);
			out.open((file_name+"~").c_str(), ios_base::out);
			if(!file.good()) cout << "Cannot open file!\n";
			else
			{
				file.seekg(0,file.end);
				int arr[256]={}, file_size=file.tellg();
				file.seekg(0,file.beg);
				for(int i=0; i<file_size; ++i)
					arr[file.get()]++;
				for(int i=0; i<256; ++i)
				{
					int x=arr[i];
					out << static_cast<unsigned char>(x>>24) << static_cast<unsigned char>(x>>16) << static_cast<unsigned char>(x>>8) << static_cast<unsigned char>(x);
				}
				multiset<my_it> my_multiset;
				multiset<my_it>::iterator it;
				for(int i=0; i<256; ++i)
					my_multiset.insert(my_it(new node(static_cast<char>(i), arr[i])));
				it=my_multiset.begin();
				while(my_multiset.size()>1)
				{
					it=my_multiset.begin();
					root=it->wsk;
					actual=(++it)->wsk;

					my_multiset.insert(my_it(new node(root,actual,actual->val+root->val)));
					my_multiset.erase(my_multiset.begin());
					my_multiset.erase(my_multiset.begin());
				}
				root=my_multiset.begin()->wsk;
				DFS(vector<bool>(),root);
				file.seekg(0,file.beg);
				for(int i=0; i<file_size; ++i)
				{
					unsigned char z=file.get();
					output(out,pref[static_cast<int>(z)]);
				}
				file.close();
				output(out,vector<bool>()); // flush output
				out.close();
			}
		}
		else if(arg1=="x")
		{
			file.open(file_name.c_str(), ios_base::in);
			out.open((out_name).c_str(), ios_base::out);
			if(!file.good()) cout << "Cannot open file!\n";
			else
			{
				file.seekg(0,file.end);
				int arr[256]={}, file_size=file.tellg();
				if(file_size<1024)
				{
					cout << "File is not compressed with this program!\n";
					return 1;
				}
				file.seekg(0,file.beg);
				for(int i=0; i<256; ++i)
				{
					int Stack[4]={file.get(),file.get(),file.get(),file.get()};
					arr[i]=Stack[3]+(Stack[2]<<8)+(Stack[1]<<16)+(Stack[0]<<24);
				}
				multiset<my_it> my_multiset;
				multiset<my_it>::iterator it;
				for(int i=0; i<256; ++i)
					my_multiset.insert(my_it(new node(static_cast<char>(i), arr[i])));
				it=my_multiset.begin();
				while(my_multiset.size()>1)
				{
					it=my_multiset.begin();
					root=it->wsk;
					actual=(++it)->wsk;
					my_multiset.insert(my_it(new node(root,actual,actual->val+root->val)));
					my_multiset.erase(my_multiset.begin());
					my_multiset.erase(my_multiset.begin());
				}
				root=my_multiset.begin()->wsk;
				unsigned char c=0;
				char l=-1;
				actual=root;
				for(int i=file.tellg();;l--)
				{
					if(l<0)
					{
						if(i==file_size) break;
						l=7;
						c=file.get();
						++i;
					}
					if(!__builtin_ctz(2+(c>>l))) // l bit is 0, +2 because if c>>7==0 then __builtin_ctz(c>>7) will be 0 (not 8)
						actual=actual->right;
					else
						actual=actual->left;
					if(actual->left==NULL)
					{
						out.put(actual->c);
						actual=root;
					}
				}
				file.close();
				out.close();
			}
		}
	return 0;
	}
}

int main()
{
	string key, file, target, rozsz;
	bool have_rozsz=false;
	fstream plik, targ, key_file;
	cout << "Write:\nKey-file: ";
	cin >> key;
	cout << "File-name: ";
	cin >> file;
	for(int i=file.size()-1; i>=0; i--)
	{
		if(file[i]=='.')
		{
			file.erase(i, file.size()-i);
			have_rozsz=true;
			break;
		}
		else rozsz=file[i]+rozsz;
	}
	if(have_rozsz) rozsz="."+rozsz;
	else string().swap(rozsz);
	int k[256], w[256], s, qy=0;
	key_file.open((key+".key").c_str(), ios::in);
	for(int i=0; i<256; i++)
			k[i]=key_file.get();
	key_file.close();
	if(rozsz==".hsx")
	{
		for(int i=0; i<256; i++)
			w[k[i]]=i;
		plik.open((file+".hsx").c_str(), ios::in);
		targ.open((file+"~").c_str(), ios::out);
		if(!plik.good()){cout << "Error: Cannot open file!\n";return 0;}
		s=plik.get();
		while(!plik.eof())
		{
			targ.put((w[s]-qy+256)%256);
			qy++;
			qy%=256;
			s=plik.get();
		}
		plik.close();
		targ.close();

		//compression
		hoffman_coding::main("x",file+"~",file+".txt");
		//clean after compression
		{system(("rm -f "+file+"~").c_str());}
	}
	else
	{

		//compression
		hoffman_coding::main("a",file+rozsz);

		plik.open((file+rozsz+"~").c_str(), ios::in);
		targ.open((file+rozsz+".hsx").c_str(), ios::out);
		if(!plik.good()){cout << "Error: Cannot open file!\n";return 0;}
		s=plik.get();
		while(!plik.eof())
		{
			targ.put(k[(s+qy)%256]);
			qy++;
			qy%=256;
			s=plik.get();
		}
		plik.close();
		targ.close();
		//clean after compression
		{system(("rm -f "+file+rozsz+"~").c_str());}
	}
return 0;
}
