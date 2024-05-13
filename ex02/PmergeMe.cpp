/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:33:09 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/14 08:09:47 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

static void	printList(std::list<std::size_t> lst)
{
	std::list<std::size_t>::const_iterator it = lst.begin();
	while (it != lst.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
}

PmergeMe::PmergeMe(){ return ; }

static std::list<std::size_t>	get_jacobsthal_seq(std::size_t size)
{

	std::size_t	prev = 1;
	std::size_t	before_prev = 0;
	std::size_t	jacob = 0;
	std::list<std::size_t> jacob_seq;
	while (jacob < size)
	{
		jacob = prev + (2 * before_prev);
		jacob_seq.push_back(jacob);
		for (std::size_t i = jacob - 1; i > prev; i--)
			jacob_seq.push_back(i);
		if (std::find(jacob_seq.begin(), jacob_seq.end(), size) != jacob_seq.end())
			break ;
		before_prev = prev;
		prev = jacob;
	}
	return (jacob_seq);
}

static bool	is_valid_num(char const *argv)
{
	std::size_t i = 0;

	while (argv[i])
	{
		if (!std::isdigit(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	validate_input(int const argc, char const **argv)
{
	std::size_t	i = 1;
	bool		is_valid = true;

	if (argc < 2)
		is_valid = false;
	while (argv[i])
	{
		if (!is_valid_num(argv[i]))
			is_valid = false;
		i++;
	}
	if (!is_valid)
	{
		std::cout << "Error" << std::endl;
		std::exit(1);
	}
	else if (i == 1)
	{
		std::cout << argv[1] << std::endl;
		std::exit(0);
	}
}

std::list<std::size_t>::const_iterator PmergeMe::get_iter(std::size_t idx) const
{
	std::size_t i = 1;
	std::list<std::size_t>::const_iterator it = pmend.begin();

	while (true)
	{
		if (i == idx)
			return (it);
		it++;
		i++;
	}
}

PmergeMe::PmergeMe(int const argc, char const **argv)
{
	validate_input(argc, argv);
	std::size_t	i = 1;
	std::size_t max = 0;
	while (argv[i] && argv[i + 1])//todo 奇数対応
	{
		std::size_t	first = std::strtoull(argv[i], NULL, 10);
		std::size_t	second = std::strtoull(argv[i + 1], NULL, 10);
		if (std::max(first, second) > max)
			max = std::max(first, second);
		std::pair<std::size_t, std::size_t> pair(std::max(first, second), std::min(first, second));
		pair_lst.push_back(pair);
		i += 2;
	}
	pair_lst.sort();
	c_iter it = pair_lst.begin();
	while (it != pair_lst.end())
	{
		main_.push_back((*it).first);
		pmend.push_back((*it).second);
		it++;
	}
	std::list<std::size_t> jacob_seq = get_jacobsthal_seq(max);
	std::list<std::size_t>::const_iterator	iter = jacob_seq.begin();
	while (iter != jacob_seq.end())
	{
		if (*iter <= pmend.size())
		{
			std::list<std::size_t>::const_iterator main_lower_bound = std::lower_bound(main_.begin(), main_.end(), *get_iter(*iter));
			main_.insert(main_lower_bound, *get_iter(*iter));
		}
		iter++;
	}
	printList(main_);
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

void	PmergeMe::printLst(void) const
{
	c_iter it = pair_lst.begin();
	
	while (it != pair_lst.end())
	{
		std::cout << "first is " << (*it).first << " and second is " << (*it).second << std::endl;
		it++;
	}
}


