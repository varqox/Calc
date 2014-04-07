#include <cstdio>
#include <vector>
#include <utility>
#include <functional>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cmath>
#include <stack>
#include <iostream>

using namespace std;

#define FOR(x,b,e) for(int x = b; x < (e); ++x)
#define FOR2(x,b,e) for(int x = b; x <= (e); ++x)
#define FORD(x,b,e) for(int x = b; x >= (e); --x)
#define REP(x,n) for(int x = 0; x < (n); ++x)
#define REP2(x,n) for(int x = 0; x <= (n); ++x)
#define VAR(v,n) typeof(n) v = (n)
#define ALL(x) x.begin(), x.end()
#define ALL2(x) x.rbegin(), x.rend()
#define FOREACH(i,c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define FOREACH2(i,c) for(VAR(i, (c).rbegin()); i != (c).rend(); ++i)
#define PB push_back
#define ST first
#define ND second
#define PF push_front
#define MP make_pair
#define I(x) static_cast<int>(x)
#define U(x) static_cast<unsigned>(x)
#define eprint(...) fprintf(stderr, __VA_ARGS__)

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VLL;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLLLL;
typedef vector<PII> VPII;
typedef vector<PLLLL> VPLLLL;
typedef vector<VPII> VVPII;

template<class T>
inline T abs(T x)
{return x<T() ? -x : x;}

#define MOD(x) {if(x>=1000000007) x%=1000000007; else if(x<0){x%=1000000007;if(x<0) x+=1000000007;}}

#ifdef DEBUG
#include <iostream>

#define D(...) __VA_ARGS__
#define LOG(x) cerr << #x << ": " << x << flush
#define LOGN(x) cerr << #x << ": " << x << endl

ostream& operator<<(ostream& os, const PII& _)
{return os << "(" << _.ST << "," << _.ND << ")";}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& _)
{
	os << "{";
	if(_.size())
	{
		os << *_.begin();
		for(typename vector<T>::const_iterator i=++_.begin(); i!=_.end(); ++i)
			os << ", " << *i;
	}
	return os << "}";
}

template<class T>
ostream& operator<<(ostream& os, const deque<T>& _)
{
	os << "{";
	if(_.size())
	{
		os << *_.begin();
		for(typename deque<T>::const_iterator i=++_.begin(); i!=_.end(); ++i)
			os << ", " << *i;
	}
	return os << "}";
}

template<class T, class K>
ostream& operator<<(ostream& os, const set<T, K>& _)
{
	os << "{";
	if(_.size())
	{
		os << *_.begin();
		for(typename set<T>::const_iterator i=++_.begin(); i!=_.end(); ++i)
			os << ", " << *i;
	}
	return os << "}";
}

#else
#define D(...)
#define LOG(x)
#define LOGN(x)
#endif

int rev(int x, int l)
{
	int left = 1 << (l-1), right = 1, res = 0;
	do
	{
		if(x & left)
			res |= right;
		left >>= 1;
		right <<= 1;
	}
	while(left > 0);
	return res;
}

int main()
{
	int n, l;
	scanf("%i", &n);
	if(n & (n-1))
	{
		eprint("n have to be power of 2\n");
		return 1;
	}
	l = sizeof(n)*8 - 1 - __builtin_clz(n); // lg of n
	LOGN(l);
	vector<int> arr(n);
	REP(i, n)
		arr[i] = i;
	// LOGN(arr);
	// REP(i, n)
	// 	arr[i] = rev(i, l);
	for(int i = 0, x; i < n; ++i)
	{
		x = rev(i, l);
		if(x > i)
			swap(arr[i], arr[x]);
	}
	// LOGN(arr);
	return 0;
}