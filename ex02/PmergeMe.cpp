/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:33:09 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/13 19:50:55 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <sstream>

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

std::list<std::size_t>	get_jacobsthal_seq(std::size_t size)
{

	typedef std::list<std::size_t>::iterator lst_it;
	std::list<std::size_t>	rev_seq;
	for (std::size_t i = size; i > 0; i--)
	{
		rev_seq.push_back(i);
	}

	std::size_t	prev = 1;
	std::size_t	two_prev = 0;
	std::size_t	jacob = 0;
	std::list<std::size_t> jacob_seq;
	while (jacob < size)
	{
		jacob = prev + 2 * two_prev;
		jacob_seq.push_back(jacob);
		lst_it	forward = rev_seq.begin();
		lst_it	follow = rev_seq.begin();
		lst_it	end = rev_seq.end();
		while (forward != end)
		{
			if (*forward == jacob)
			{
				while (follow != forward)
				{
					jacob_seq.push_back(*follow);
					lst_it tmp = follow;
					follow++;
					rev_seq.erase(tmp);
				}
				lst_it tmp = forward;
				forward++;
				follow = forward;
				rev_seq.erase(tmp);
			}
			else
				forward++;
		}
		two_prev = prev;
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

PmergeMe::PmergeMe(int const argc, char const **argv)
{
	validate_input(argc, argv);
	std::size_t	i = 1;
	while (argv[i] && argv[i + 1])//todo 奇数対応
	{
		std::size_t	first = std::strtoull(argv[i], NULL, 10);
		std::size_t	second = std::strtoull(argv[i + 1], NULL, 10);
		std::pair<std::size_t, std::size_t> pair(std::max(first, second), std::min(first, second));
		pair_lst.push_back(pair);
		i += 2;
	}
	// printLst();
	pair_lst.sort();
	// printLst();
	c_iter it = pair_lst.begin();
	while (it != pair_lst.end())
	{
		main_.push_back((*it).first);
		pmend.push_back((*it).second);
		it++;
	}
	std::list<std::size_t>::const_iterator	iter = pmend.begin();
	while (iter != pmend.end())
	{
		std::list<std::size_t>::const_iterator m_lower_bound = std::lower_bound(main_.begin(), main_.end(), *iter);
		main_.insert(m_lower_bound, *iter);
		iter++;
	}
	// printList();
	std::list<std::size_t> jacob = get_jacobsthal_seq(20);
	printList(jacob);
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
// 

void	PmergeMe::printLst(void) const
{
	c_iter it = pair_lst.begin();
	
	while (it != pair_lst.end())
	{
		std::cout << "first is " << (*it).first << " and second is " << (*it).second << std::endl;
		it++;
	}
}


