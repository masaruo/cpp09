/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:33:09 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/09 18:41:38 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <cerrno>

PmergeMe::PmergeMe(){ return ; }

static	bool	is_valid_num(char const *argv)
{
	std::size_t i = 0;

	while (argv[i])
	{
		if (!std::isdigit(argv[i]) && argv[i] != '+')
			return (false);
		i++;
	}
	return (true);
}

PmergeMe::PmergeMe(char const **argv)
{
	std::size_t	i = 0;

	while (argv[i])
	{
		if (!is_valid_num(argv[i]))
		{
			std::cout << "Error" << std::endl;
			std::exit(1);
		}
		unsigned long	tmp = std::strtoul(argv[i], NULL, 10);
		// std::cout << tmp << std::endl;
		lst.push_back(tmp);
		i++;
	}
}

PmergeMe::~PmergeMe()
{
	return ;
}

PmergeMe::PmergeMe(PmergeMe const &rhs)
{
	return ;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs)
{
	if (this != &rhs)
	{
		//todo
	}
	return (*this);
}

template <typename C>
void	PmergeMe::printC(C const &c) const
{
	typename C::const_iterator iter = c.begin();
	for (; iter != c.end(); iter++)
	{
		std::cout << *iter << std::endl;
	}
}

void	PmergeMe::printLst(void) const
{
	printC<std::list<unsigned long> >(lst);
}
