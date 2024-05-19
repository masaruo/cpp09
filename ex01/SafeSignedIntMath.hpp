/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_si_calc.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:58:59 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/19 14:06:01 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <stdexcept>
#include <limits>
#include <string>

template <typename T>
class SafeSignedIntMath
{
private:
	//static class
	SafeSignedIntMath(){};
	~SafeSignedIntMath(){};
	SafeSignedIntMath(SafeSignedIntMath const &rhs){ (void) rhs; };
	SafeSignedIntMath &operator=(SafeSignedIntMath const &rhs){ (void) rhs; return (*this); };
public:
	static	T	add(T const &si_a, T const &si_b);
	static	T	sub(T const &si_a, T const &si_b);
	static	T	mul(T const &si_a, T const &si_b);
	static	T	div(T const &si_a, T const &si_b);
	static	T	remainder(T const &si_a, T const &si_b);
};

template <typename T>
T	SafeSignedIntMath<T>::add(T const &si_a, T const &si_b)
{
	bool	is_valid;
	if ((si_b > 0) && (si_a > (std::numeric_limits<T>::max() - si_b)))
		is_valid = false;
	else if ((si_b < 0) && (si_a < (std::numeric_limits<T>::min() - si_b)))
		is_valid = false;
	else
		is_valid = true;
	if (!is_valid)
	{
		throw (std::overflow_error("Addition overflow."));
		return (0);
	}
	else
		return (si_a + si_b);
}

template <typename T>
T	SafeSignedIntMath<T>::sub(T const &si_a, T const &si_b)
{
	bool	is_valid;
	if (si_b > 0 && si_a < std::numeric_limits<T>::min() + si_b)
		is_valid = false;
	else if (si_b < 0 && si_a > std::numeric_limits<T>::max() + si_b)
		is_valid = false;
	else
		is_valid = true;
	if (!is_valid)
	{
		throw (std::overflow_error("Subtraction overflow"));
		return (0);
	}
	else
		return (si_a - si_b);
}

template <typename T>
T	SafeSignedIntMath<T>::mul(T const &si_a, T const &si_b)
{
	T	result = si_a * si_b;

	if (result != 0 && result / si_a != si_b)//? ここのロジックがわからない
	{
		throw (std::overflow_error("Multiplication overflow"));
		return (0);
	}
	else
		return (si_a * si_b);
}

template <typename T>
T	SafeSignedIntMath<T>::div(T const &si_a, T const &si_b)
{
	if (si_b == 0)
	{
		throw (std::runtime_error("Division by zero"));
		return (0);
	}
	else if (si_a == std::numeric_limits<T>::min() && si_b == -1)
	{
		throw (std::overflow_error("Division of NUMERIC::MIN / -1"));
		return (0);
	}
	else 
		return (si_a / si_b);
}

template <typename T>
T	SafeSignedIntMath<T>::remainder(T const &si_a, T const &si_b)
{
	if (si_b == 0)
	{
		throw (std::runtime_error("remainder operation by zero"));
		return (0);
	}
	else if (si_a == std::numeric_limits<T>::min() && si_b == -1)
	{
		throw (std::overflow_error("remainder operation of NUMERIC::MIN / -1"));
		return (0);
	}
	else 
		return (si_a % si_b);
}
