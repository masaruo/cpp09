/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/20 03:25:55 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "XString.hpp"
#include <iostream>
#include <sstream>

template <typename C>
class PmergeMe
{
private:
	C	argv_c;
	PmergeMe();//hidden

	//! helper functions
	void	create_argv_container(char const **argv);
public:
	PmergeMe(char const **argv);
	PmergeMe(PmergeMe const &rhs);
	~PmergeMe();
	PmergeMe &operator=(PmergeMe const &rhs);
};

#include "PmergeMe.tpp"

template <typename C>
PmergeMe<C>::PmergeMe()//hidden
{
	return ;
}

template <typename C>
PmergeMe<C>::PmergeMe(char const **argv)
{
	create_argv_container(argv);
	//todo;
}

template <typename C>
PmergeMe<C>::~PmergeMe()
{
	return ;
}

template <typename C>
PmergeMe<C>	&PmergeMe<C>::operator=(PmergeMe const &rhs)
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
	else if (num_str != "0" && num_ui == 0)
		is_valid = false;
	return (is_valid);
}

template <typename C>
void	PmergeMe<C>::create_argv_container(char const **argv)
{
	for (std::size_t i = 1; argv[i]; i++)
	{
		xString	num_str = argv[i];
		std::stringstream num_ss(num_str);
		std::size_t	num_ui;
		num_ss >> num_ui;
		if (!is_valid_number(num_str, num_ui))
			continue ;
		argv_c.push_back(num_ui);
	}
}
