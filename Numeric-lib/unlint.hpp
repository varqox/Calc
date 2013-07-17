#ifndef __UNLINT_H
#define __UNLINT_H

#include <bits/localefwd.h>
#include <string>
#include <vector>

namespace unlimited_int
{
	/*
	unlimited integer type
	*/
	class unlint
	{
	private:
		/*
		unlimited natural type
		*/
		class num;
		bool z; // znak
		num* w; // wartość
	public:
		unlint();
		~unlint();
		unlint(long long int);
		unlint(const char*);
		unlint(const std::string&);
		unlint(const unlint&);
		unlint& operator=(const unlint&);
		template<typename type>
		unlint& operator=(const type&);
		long long int size() const;
		void swap(unlint&);
		std::string str() const;
		unlint& operator++();
		unlint& operator--();
		unlint operator++(int);
		unlint operator--(int);
		friend unlint operator+(const unlint&);
		friend unlint operator-(const unlint&);
		unlint operator+(const unlint&);
		unlint& operator+=(const unlint&);
		unlint operator-(const unlint&);
		unlint& operator-=(const unlint&);
		unlint operator*(const unlint&);
		unlint& operator*=(const unlint&);
		unlint operator/(const unlint&);
		unlint& operator/=(const unlint&);
		unlint operator%(const unlint&);
		unlint& operator%=(const unlint&);
		bool operator>(const unlint&) const;
		bool operator<(const unlint&) const;
		bool operator>=(const unlint&) const;
		bool operator<=(const unlint&) const;
		bool operator==(const unlint&) const;
		bool operator!=(const unlint&) const;
		unlint& pow(const unlint&);
		unlint& factorial();
		friend unlint nwd(const unlint&, const unlint&);
		/* output unlint with ostream */
		friend std::ostream& operator<<(std::ostream&, const unlint&);
		/* input unlint with istream */
		friend std::istream& operator>>(std::istream&, unlint&);
	};

	unlint pow(const unlint&, const unlint&);
	unlint factorial(const unlint&);

	template<typename type>
	unlint& unlint::operator=(const type& _n)
	{
		unlint(_n).swap(*this);
	return *this;
	}
}

using namespace unlimited_int;

#endif /* __UNLINT_H */