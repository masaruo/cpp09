/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/22 16:25:55 by mogawa           ###   ########.fr       */
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
	PmergeMe();//hidden
	PmergeMe(PmergeMe const &rhs);
public:
	PmergeMe(char const **argv);
	~PmergeMe();
	PmergeMe &operator=(PmergeMe const &rhs);
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
void	PmergeMe<Con>::print(void) const
{
	std:: cout << "Before: ";
	std::for_each(argv_seq.begin(), argv_seq.end(), &put);
	std::cout << std::endl << "After: ";
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
	std::for_each(jacob_seq.begin(), jacob_seq.end(), &put);//delete;
}

template <typename Con>
PmergeMe<Con>::~PmergeMe()
{
	return ;
}

template <typename Con>
PmergeMe<Con>::PmergeMe(PmergeMe const &rhs)
{
	(void) rhs;
	return ;
}

template <typename Con>
PmergeMe<Con>	&PmergeMe<Con>::operator=(PmergeMe const &rhs)
{
	(void) rhs;
	return (*this);
}

static bool	is_valid_number(xString const &num_str, std::size_t num_ui)
{
	bool	is_valid = true;

	if (num_str.contain_any_of("-"))
		throw (std::invalid_argument("Error"));
	else if (num_str.empty())
		is_valid = false;
	else if (num_str.contain_not_of("0123456789"))
		is_valid = false;
	else if (num_ui == std::numeric_limits<std::size_t>::max())
		is_valid = false;
	else if (num_str != "0" && num_ui == 0)
		is_valid = false;
	return (is_valid);
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
		if (!is_valid_number(num_str, num_ui))
			continue ;
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
	while (jacob < size)
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

template <typename Con>
void	PmergeMe<Con>::sort_start(void)
{
	Con	sorting = argv_seq;
	std::time_t	start = std::time(NULL);
	Con	sorted;
	sorted = merge_insert_sort(NULL, NULL);
	sorted_seq = sorted;
	std::time_t	end = std::time(NULL);
	duration = static_cast<double>((start - end)) / CLOCKS_PER_SEC * 1000.0;
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
	// mainにpmendを挿入
	// for (cit_t pmend_it = pmend.begin(); pmend_it != pmend.end(); pmend_it++)//change to jacob
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
		}
	}
	*prev_main = main;
	*prev_pmend = sorted_pmend;
	return (main);
}
