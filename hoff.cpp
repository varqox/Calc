#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

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
		if(this->wsk->val==_it.wsk->val) return this->wsk->c<_it.wsk->c;
	return this->wsk->val<_it.wsk->val;
	}
};

void DFS(vector<bool> k, const node* x)
{
	if(x->left==NULL)
	{
		//cout << x->c << " " << k.size() << endl;
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
		while(l<8)
		{
			++l;
			out<<=1;
			++out;
		}
		file << out;
		out=l=0;
	}
	for(int s=vb.size(), i=0; i<s; ++i)
	{
		out<<=1;
		++l;
		if(vb[i]) ++out;
		if(l==8)
		{
			file << static_cast<unsigned char>(out);
			out=l=0;
		}
	}
}

int main(int argc, char *argv[])
{
	if(argc!=3) return 1;
	string file_name=argv[2];
	fstream file, out;
	const node *root, *actual;
	if(argv[1][0]=='a' && argv[1][1]=='\0')
	{
		file.open(file_name.c_str(), ios_base::in);
		out.open((file_name+".hoff").c_str(), ios_base::out);
		if(!file.good()) cout << "Cannot open file!";
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
				//cout << x << " " << (int(Stack[3])+(int(Stack[2])<<8)+(int(Stack[1])<<16)+(int(Stack[0])<<24)) << endl;
			}
			set<my_it> my_set;
			set<my_it>::iterator it;
			for(int i=0; i<256; ++i)
				if(arr[i]>0) my_set.insert(my_it(new node(static_cast<char>(i), arr[i])));
			it=my_set.begin();
			/*while(it!=my_set.end())
			{
				cout << it->wsk->val << endl;
				++it;
			}*/
			while(my_set.size()>1)
			{
				it=my_set.begin();
				root=it->wsk;
				actual=(++it)->wsk;
				//cout << my_set.size() << " " << actual->val << " " << root->val << endl;
				my_set.insert(my_it(new node(root,actual,actual->val+root->val)));
				my_set.erase(my_set.begin());
				my_set.erase(my_set.begin());
			}
			root=my_set.begin()->wsk;
			DFS(vector<bool>(),root);
			if(root->left==NULL) vector<bool>(1,false).swap(pref[root->c]);
			//cout << int(root->left->c) << endl;
			file.seekg(0,file.beg);
			for(int i=0; i<file_size; ++i)
			{
				unsigned char z=file.get();
				//cout << z;
				output(out,pref[static_cast<int>(z)]);
			}
			//cout << endl;
			file.close();
			output(out,vector<bool>()); // flush output
			out.close();
		}
	}
	else if(argv[1][0]=='x' && argv[1][1]=='\0')
	{
		string out_name;
		cout << "Write out-file name: ";
		cin >> out_name;
		file.open(file_name.c_str(), ios_base::in);
		out.open(out_name.c_str(), ios_base::out);
		if(!file.good()) cout << "Cannot open file!";
		else
		{

			file.close();
			out.close();
		}
	}
return 0;
}