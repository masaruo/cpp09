/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/13 23:23:37 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <list>
#include <ostream>
#include <utility>

typedef std::list<std::pair<std::size_t, std::size_t> >::const_iterator c_iter;
typedef std::list<std::pair<std::size_t, std::size_t> >::const_reverse_iterator c_rev_iter;
typedef std::list<std::pair<std::size_t, std::size_t> >::iterator iter;

class PmergeMe
{
private:
	std::list<std::pair<std::size_t, std::size_t> > pair_lst;
	std::list<std::size_t> main_;
	std::list<std::size_t> pmend;
	std::list<std::size_t> jacob_seq;
	std::list<std::size_t>::const_iterator get_iter(std::size_t idx) const;
	PmergeMe();
public:
	PmergeMe(int const argc, char const **argv);
	PmergeMe(PmergeMe const &rhs);
	~PmergeMe();
	PmergeMe &operator=(PmergeMe const &rhs);
	void	printLst(void) const;
	// void	printList() const;
};
