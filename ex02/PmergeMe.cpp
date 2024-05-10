/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:33:09 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/10 17:53:14 by mogawa           ###   ########.fr       */
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

static pair_t	make_pair(std::size_t num, bool is_second)
{
	
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
		std::size_t	num = std::strtoul(argv[i], NULL, 10);//* check l to num
		std::pair<std::size_t, std::size_t>	pair(0, 0);
		if (i % 2 == 0)//todo 最後の要素が奇数の時
			pair.first = num;
		else
		{
			pair.second = num;
			lst.push_back(pair);
		}
		i++;
	}
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

template <typename C>
void	PmergeMe::printC(C const &c) const
{
	std::stringstream ss;
	typename C::const_iterator iter = c.begin();
	for (; iter != c.end(); iter++)
	{
		ss << *iter << " ";
		// std::cout << *iter << std::endl;
	}
	std::cout << ss.str() << std::endl;
}

void	PmergeMe::printLst(void) const
{
	printC<std::list<std::size_t> >(lst);
}
