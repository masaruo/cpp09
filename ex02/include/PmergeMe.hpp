/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/12 10:02:04 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "xString.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iterator>

template <typename Con>
class PmergeMe
{
public: //typedef
	typedef typename Con::const_iterator	const_iterator;
	typedef typename Con::iterator			iterator;
	typedef typename Con::size_type			size_type;
	typedef typename Con::difference_type	difference_type;
	//for nested_vec
	typedef std::vector<std::vector <std::size_t> > 	nested_vec;
	typedef nested_vec::const_iterator					const_nested_vec_iter;
	typedef nested_vec::size_type						nested_vec_size_type;
	//for nested_deque
	typedef std::deque<std::deque <std::size_t> >		nested_dq;
	typedef nested_dq::const_iterator					const_nested_dq_iter;
	typedef nested_dq::size_type						nested_dq_size_type;
private:
	Con			argv_seq;
	Con			jacob_seq;
	Con			sorted_seq;
	double		sorting_duration;
	double		data_mgmt_duration;
	size_type	valid_argc;
	void	gen_argv_seq(char const **argv);
	void	gen_jacob_seq(size_type size);
	void	sort_vector(nested_vec &);
	void	sort_deque(nested_dq &);
	void	print_con(Con const &con) const;
	PmergeMe();//hidden
	PmergeMe(PmergeMe const &rhs);
	PmergeMe &operator=(PmergeMe const &rhs);
public:
	PmergeMe(char const **argv);
	~PmergeMe();
	void		sort_start(void);
	double		get_duration(void) const;
	std::size_t	get_valid_argc(void) const;
	void		print(void) const;
};

static void put(std::size_t const &n)
{
	std::cout << n << " ";
}

template <typename Con>
void	PmergeMe<Con>::print_con(Con const &con) const
{
	const_iterator	beg = con.begin();
	const_iterator	end = con.end();

	std::for_each(beg, end, &put);
}

template <typename Con>
void	PmergeMe<Con>::print(void) const
{
	std:: cout << "Before: ";
	std::for_each(argv_seq.begin(), argv_seq.end(), &put);
	std::cout << std::endl << "After : ";
	std::for_each(sorted_seq.begin(), sorted_seq.end(), &put);
	std::cout << std::endl;
}

template <typename Con>
PmergeMe<Con>::PmergeMe(){ return ; }// hidden

template <typename Con>
PmergeMe<Con>::PmergeMe(char const **argv)
{
	std::clock_t start = std::clock();
	gen_argv_seq(argv);
	valid_argc = argv_seq.size();
	gen_jacob_seq(valid_argc + 1);
	std::clock_t end = std::clock();
	data_mgmt_duration = static_cast<double>((end - start)) / CLOCKS_PER_SEC * 1000.0;
}

template <typename Con>
PmergeMe<Con>::~PmergeMe()
{
	return ;
}

template <typename Con>
PmergeMe<Con>::PmergeMe(PmergeMe const &rhs)//hidden
{
	(void) rhs;
	return ;
}

template <typename Con>
PmergeMe<Con>	&PmergeMe<Con>::operator=(PmergeMe const &rhs)//hidden
{
	(void) rhs;
	return (*this);
}

static void	assert_valid_number(xString const &num_str, std::stringstream const &ss, std::size_t num_ui)
{
	if (!ss || ss.str().empty())
		throw(std::invalid_argument("Error"));
	else if (num_str.contain_not_of("0123456789"))
		throw (std::invalid_argument("Error"));
	else if (num_ui == 0)
		throw (std::invalid_argument("Error"));
}

template <typename Con>
void	PmergeMe<Con>::gen_argv_seq(char const **argv)
{
	for (std::size_t i = 1; argv[i]; i++)
	{
		xString	num_str = argv[i];
		std::stringstream num_ss(num_str);
		std::size_t	num_ui;
		num_ss >> num_ui;
		assert_valid_number(num_str, num_ss, num_ui);
		argv_seq.push_back(num_ui);
	}
}

template <typename Con>
void	PmergeMe<Con>::gen_jacob_seq(size_type size)
{
	size_type	prev = 1;
	size_type	before_prev = 0;
	size_type	jacob = 0;

	jacob_seq.push_back(0);
	while (true)
	{
		jacob = prev + (2 * before_prev);
		jacob_seq.push_back(jacob);
		for (size_type i = jacob - 1; i > prev; i--)
		{
			jacob_seq.push_back(i);
		}
		if (std::find(jacob_seq.begin(), jacob_seq.end(), size) != jacob_seq.end())
			break ;
		before_prev = prev;
		prev = jacob;
		jacob++;
	}
	return ;
}

template <typename Con>
double	PmergeMe<Con>::get_duration(void) const
{
	return (sorting_duration + data_mgmt_duration);
}

template <typename Con>
std::size_t	PmergeMe<Con>::get_valid_argc(void) const
{
	return (valid_argc);
}

#include <sys/time.h>

template <typename Con>
void	PmergeMe<Con>::sort_start(void)
{
	nested_vec	v_seq;
	const_iterator		argv_iter = argv_seq.begin();
	std::clock_t start = std::clock();
	while (argv_iter != argv_seq.end())
	{
		std::vector<std::size_t> tmp;
		tmp.push_back(*argv_iter);
		v_seq.push_back(tmp);
		argv_iter++;
	}
	sort_vector(v_seq);
	std::clock_t end = std::clock();
	sorting_duration = static_cast<double>((end - start)) / CLOCKS_PER_SEC * 1000.0;
}

template <typename Con>
void	PmergeMe<Con>::sort_vector(nested_vec &seq)
{
	//stack building
	if (seq.size() < 2)
		return ;

	nested_vec					tmp_nested;
	Con							tmp_vec;
	const_nested_vec_iter		crnt = seq.begin();
	const_nested_vec_iter		next = crnt + 1;
	const_nested_vec_iter		end = seq.end();
	while (true)
	{
		if (crnt->front() == 0 || next->front() == 0)
		{
			Con	zeropad1(crnt->size(), 0);
			zeropad1.insert(zeropad1.end(), crnt->begin(), crnt->end());
			tmp_nested.push_back(zeropad1);
			Con	zeropad2(crnt->size(), 0);
			zeropad2.insert(zeropad2.end(), next->begin(), next->end());
			tmp_nested.push_back(zeropad2);
		}
		else if (*crnt >= *next)
		{
			tmp_vec = *crnt;
			tmp_vec.insert(tmp_vec.end(), next->begin(), next->end());
			tmp_nested.push_back(tmp_vec);
		}
		else
		{
			tmp_vec = *next;
			tmp_vec.insert(tmp_vec.end(), crnt->begin(), crnt->end());
			tmp_nested.push_back(tmp_vec);
		}
		if (crnt + 2 == end)
		{
			break ;
		}
		else if (next + 2 == end)
		{
			crnt += 2;
			Con	zeros(crnt->size(), 0);
			zeros.insert(zeros.end(), crnt->begin(), crnt->end());
			tmp_nested.push_back(zeros);
			break ;
		}
		crnt += 2;
		next += 2;
	}
	seq = tmp_nested;

	// check size of nested container (1 container ex 0 then finish stack build up)
	nested_vec_size_type	size = 0;
	for (const_nested_vec_iter i = seq.begin(); i != seq.end(); i++)
	{
		if (i->front() != 0)
			size++;
	}

	//!resurse
	if (size != 1)
	{
		sort_vector(seq);
	}

	//!stack unwinding
	if (seq.front().size() == 1)
		return ;

	// ベクターを中間地点にて大きい数字ベクターと小さい数字ベクターに分割(要素が２よりも大きいとき)
	nested_vec	large, small;
	for (const_nested_vec_iter v = seq.begin(); v != seq.end(); v++)
	{
		Con	front, back;
		const_iterator	mid = v->begin();
		if (seq.front().size() != 2)
		{
			std::advance(mid, v->size() / 2);
		}
		else
		{
			std::advance(mid, 1);
		}

		front.insert(front.end(), v->begin(), mid);
		back.insert(back.end(), mid, v->end());
		if (front.front() != 0)
		{
			large.push_back(front);
		}
		small.push_back(back);
	}

	// insert
	for (const_nested_vec_iter small_iter = small.begin(); small_iter != small.end(); small_iter++)
	{
		nested_vec	tmp;
		for (const_nested_vec_iter large_iter = large.begin(); large_iter != large.end(); large_iter++)
		{
			if (small_iter->front() == 0)
			{
				large.push_back(*small_iter);
				break ;
			}
			else if (*large_iter > *small_iter)
			{
				large.insert(large_iter, *small_iter);
				break ;
			}
			else if (large_iter + 1 == large.end())
			{
				large.push_back(*small_iter);
				break ;
			}
		}
	}
	seq = large;
}
