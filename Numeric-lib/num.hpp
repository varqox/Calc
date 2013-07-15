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
		nat* w; // wartość
	public:
		num();
		~num();
		num(const long long int&);
		num(const char*);
		num(const std::string&);
		num(const num&);
		num& operator=(const num&);
		template<typename type>
		num& operator=(const type&);
		long long int size() const;
		void swap(num&);
		std::string str() const;
		num& operator++();
		num& operator--();
		num operator++(int);
		num operator--(int);
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
		friend num nwd(const num&, const num&);
		/* output num with ostream */
		friend std::ostream& operator<<(std::ostream&, const num&);
		/* input num with istream */
		friend std::istream& operator>>(std::istream&, num&);
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