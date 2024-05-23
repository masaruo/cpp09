/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/23 21:45:35 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "XString.hpp"
#include <iostream>
#include <sstream>
#include <utility>
#include <ctime>
#include <algorithm>
#include <vector>
#include <deque>
#include <limits>
#include <iterator>
#include <exception>
#include <stdexcept>

template <typename Con>
class PmergeMe
{
public: //typedef
	typedef typename Con::const_iterator	cit_t;
	typedef typename Con::iterator			it_t;
	typedef typename Con::size_type			con_size_t;
	typedef typename Con::difference_type	diff_t;

private:
	Con			argv_seq;
	Con			jacob_seq;
	Con			sorted_seq;
	double		duration;
	con_size_t	valid_argc;
	void	gen_argv_seq(char const **argv);
	void	gen_jacob_seq(con_size_t size);
	Con		merge_insert_sort(Con *prev_main, Con *prev_pmend);
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
	cit_t	beg = con.begin();
	cit_t	end = con.end();

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
	gen_argv_seq(argv);
	valid_argc = argv_seq.size();
	gen_jacob_seq(valid_argc + 1);
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

static void	assert_valid_number(xString const &num_str, std::stringstream const &ss)
{
	if (!ss || ss.str().empty())
		throw(std::invalid_argument("Error"));
	else if (num_str.contain_not_of("0123456789"))
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
		assert_valid_number(num_str, num_ss);
		argv_seq.push_back(num_ui);
	}
}

template <typename Con>
void	PmergeMe<Con>::gen_jacob_seq(con_size_t size)
{
	con_size_t	prev = 1;
	con_size_t	before_prev = 0;
	con_size_t	jacob = 0;

	jacob_seq.push_back(0);
	while (true)
	{
		jacob = prev + (2 * before_prev);
		jacob_seq.push_back(jacob);
		for (con_size_t i = jacob - 1; i > prev; i--)
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
	return (duration);
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
	std::clock_t start = std::clock();
	sorted_seq = merge_insert_sort(NULL, NULL);
	std::clock_t end = std::clock();
	duration = static_cast<double>((end - start)) / CLOCKS_PER_SEC * 1000.0;
}

template <typename Con>
Con	PmergeMe<Con>::merge_insert_sort(Con *prev_main, Con *prev_pmend)
{
	Con			main, pmend;

	//!Ascend merge part
	if (prev_main == NULL)
	{
		main = argv_seq;
	}
	else
	{
		cit_t		crnt = prev_main->begin();
		cit_t		next = prev_main->begin() + 1;
		cit_t		end = prev_main->end();

		while (crnt != end && next != end)
		{
			main.push_back(std::max(*crnt, *next));
			pmend.push_back(std::min(*crnt, *next));
			crnt += 2, next += 2;
		}
		if (crnt != end)
			pmend.push_back(*crnt);
	}

	if (main.size() > 1)
	{
		merge_insert_sort(&main, &pmend);
	}

	//!Decend insert part

	for (cit_t jacob_it = jacob_seq.begin(); jacob_it != jacob_seq.end(); jacob_it++)
	{
		cit_t	pmend_it = pmend.begin();
		if (*jacob_it >= pmend.size())
			continue ;
		std::advance(pmend_it, *jacob_it);
		cit_t	pos = std::lower_bound(main.begin(), main.end(), *pmend_it);
		main.insert(pos, *pmend_it);
	}
	if (prev_pmend == NULL)
	{
		return (main);
	}
	//* 1: 新メインをループ。それぞれの要素がprev_mainのどこのINDEXかを見つける
	//* 2: 当該INDEXのprev_pmendの数字をsorted_pmendにpush back
	Con	sorted_pmend;
	std::size_t	cnt = 0;
	for (cit_t main_it = main.begin(); main_it != main.end(); main_it++)
	{
		cit_t	pos = std::find(prev_main->begin(), prev_main->end(), *main_it);
		if (pos != prev_main->end())
		{
			cit_t prev_begin = prev_main->begin();
			diff_t	idx = std::distance(prev_begin, pos);
			if (prev_pmend->empty())
				break ;
			sorted_pmend.push_back(prev_pmend->at(static_cast<std::size_t>(idx)));
			cnt++;
		}
	}
	while (cnt < prev_pmend->size())
	{
		sorted_pmend.push_back(prev_pmend->at(cnt));
		cnt++;
	}
	*prev_main = main;
	*prev_pmend = sorted_pmend;

	return (main);
}
