/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:33:09 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/10 19:11:21 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <sstream>

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
	std::size_t	odd = 0;
	std::size_t	even = 0;

	while (argv[i])
	{
		if (!is_valid_num(argv[i]))
		{
			std::cout << "Error" << std::endl;
			std::exit(1);
		}
		std::size_t	num = std::strtoul(argv[i], NULL, 10);//* check l to num
		if (i % 2 == 0)
		{
			even = num;
		}
		else
		{
			odd = num;
			// std::pair<std::size_t, std::size_t> pair = make_pair()
			pair_t	pair = std::make_pair(std::max(even, odd), std::min(even, odd));
			lst.push_back(pair);
		}
		i++;
	}
	lst.sort();
	std::list<pair_t>::const_iterator it;
	for (; it != lst.end(); it++)
		std::cout << (*it).first << " | " << (*it).second << std::endl;
}

PmergeMe::~PmergeMe()
{
	return ;
}

PmergeMe::PmergeMe(PmergeMe const &rhs)
{
	//todo
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

// template <typename C>
// void	PmergeMe::printC(C const &c) const
// {
// 	std::stringstream ss;
// 	typename C::const_iterator iter = c.begin();
// 	for (; iter != c.end(); iter++)
// 	{
// 		ss << *iter << " ";
// 		// std::cout << *iter << std::endl;
// 	}
// 	std::cout << ss.str() << std::endl;
// }

// void	PmergeMe::printLst(void) const
// {
// 	printC<std::list<std::size_t> >(lst);
// }
