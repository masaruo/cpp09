/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/10 19:10:43 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <list>
#include <ostream>
#include <utility>

typedef std::pair<std::size_t, std::size_t> pair_t;

class PmergeMe
{
private:
	std::list<pair_t> lst;
	// std::list<std::pair<std::size_t, std::size_t> > lst;
	// template <typename C>
	// void	printC(C const &c) const;
	PmergeMe();
public:
	PmergeMe(char const **argv);
	PmergeMe(PmergeMe const &rhs);
	~PmergeMe();
	PmergeMe &operator=(PmergeMe const &rhs);
	// void	printLst(void) const;
};
