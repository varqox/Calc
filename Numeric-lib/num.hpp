#ifndef __num_H
#define __num_H

#include <bits/localefwd.h>
#include <string>
#include <vector>

namespace numeric_lib
{
	/*
	unlimited integer type
	*/
	class num
	{
	private:
		/*
		unlimited natural type
		*/
		class nat;
		bool z; // znak
		nat *l, *m; // wartość
		void spwd(const num&, nat&);
		void cut();
	public:
		num();
		~num();
		num(long long int);
		num(const char*);
		num(const char*, unsigned int, unsigned int);
		num(const std::string&);
		num(const std::string&, unsigned int, unsigned int);
		num(const num&);
		num& operator=(const num&);
		template<typename type>
		num& operator=(const type&);
		void swap(num&);
		std::string str() const;
		num& opp();
		friend num operator+(const num&);
		friend num operator-(const num&);
		num operator+(const num&);
		num& operator+=(const num&);
		num operator-(const num&);
		num& operator-=(const num&);
		num operator*(const num&);
		num& operator*=(const num&);
		num operator/(const num&);
		num& operator/=(const num&);
		num operator%(const num&);
		num& operator%=(const num&);
		bool operator>(const num&) const;
		bool operator<(const num&) const;
		bool operator>=(const num&) const;
		bool operator<=(const num&) const;
		bool operator==(const num&) const;
		bool operator!=(const num&) const;
		num& pow(const num&);
		num& factorial();
		void output(const bool*);
		friend std::ostream& operator<<(std::ostream&, const nat*);
	};

	num pow(const num&, const num&);
	num factorial(const num&);

	template<typename type>
	num& num::operator=(const type& _n)
	{
		num(_n).swap(*this);
	return *this;
	}
}

using namespace numeric_lib;

#endif /* __num_H */