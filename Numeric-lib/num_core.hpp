#ifndef __Num_core_hpp
#define __Num_core_hpp

namespace numeric_lib
{
	typedef long long int lli;
	const lli BASE=1000000000000000000LL, BS2=1000000000;
	const char LEN=18;

	class num::nat
	{
	public:
		struct fmod
		{
			lli pom1, pom2;
			fmod(){}
			~fmod(){}
		};
		std::vector<lli> w;
		nat(): w(1,0){}
		~nat(){}
		nat(const lli& _x): w(1,_x){}
		nat(const nat& _n): w(_n.w){}
		lli size() const;
		void kas0();
		void swap(nat& _n){this->w.swap(_n.w);}
		nat& operator++();
		nat& operator--();
		nat& operator+=(const nat&);
		nat& operator-=(const nat&);
		nat& operator*=(const lli&);
		void gen_mod(std::vector<fmod>&) const;
		nat& mult(const lli&, const std::vector<fmod>&);
		void to_old_type(std::vector<int>&) const;
		nat& from_old_type(std::vector<int>&);
		class FFT;
		nat& operator*=(const nat&);
		nat& operator/=(const nat&);
		nat& operator%=(const nat&);
		nat& nwd(const nat&);
		nat& pow(const nat&);
		bool operator<(const nat&) const;
		bool operator>(const nat&) const;
		bool operator<=(const nat&) const;
		bool operator>=(const nat&) const;
		bool operator==(const nat&) const;
		bool operator!=(const nat&) const;
	};
}

#endif // __Num_core_hpp