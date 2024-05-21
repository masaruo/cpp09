/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/22 08:20:43 by mogawa           ###   ########.fr       */
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

template <typename Con>
class PmergeMe
{
public: //typedef
	typedef typename Con::const_iterator	cit_t;
	typedef typename Con::iterator			it_t;
	typedef typename Con::size_type			con_size_t;
	typedef typename Con::difference_type	con_diff_t;

private:
	Con		argv_seq;
	Con		jacob_seq;
	double	duration;
	PmergeMe();//hidden
	void		gen_argv_seq(char const **argv);
	void		gen_jacob_seq(con_size_t size);
public:
	PmergeMe(char const **argv);
	PmergeMe(PmergeMe const &rhs);
	~PmergeMe();
	PmergeMe &operator=(PmergeMe const &rhs);
	void	sort_start(void);
	double	get_duration(void) const;
};

template <typename Con>
PmergeMe<Con>::PmergeMe(){ return ; }// hidden

template <typename Con>
PmergeMe<Con>::PmergeMe(char const **argv)
{
	gen_argv_seq(argv);
	gen_jacob_seq(argv_seq.size() / 2 + 1);
}

template <typename Con>
PmergeMe<Con>::~PmergeMe()
{
	return ;
}

template <typename Con>
PmergeMe<Con>::PmergeMe(PmergeMe const &rhs)
{
	//todo
	return ;
}

template <typename Con>
PmergeMe<Con>	&PmergeMe<Con>::operator=(PmergeMe const &rhs)
{
	//todo
	return (*this);
}

static bool	is_valid_number(xString const &num_str, std::size_t num_ui)
{
	bool	is_valid = true;

	if (num_str.empty())
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
void	PmergeMe<Con>::sort_start(void)
{
	Con	sorting = argv_seq;
	std::time_t	start = std::time(NULL);
	//todo sorts
	std::time_t	end = std::time(NULL);
	duration = static_cast<double>((start - end)) / CLOCKS_PER_SEC * 1000.0;
}
