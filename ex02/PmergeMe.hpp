/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/09 18:38:00 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <list>
#include <ostream>

class PmergeMe
{
private:
	std::list<unsigned long>	lst;
	template <typename C>
	void	printC(C const &c) const;
	PmergeMe();
public:
	PmergeMe(char const **argv);
	PmergeMe(PmergeMe const &rhs);
	~PmergeMe();
	PmergeMe &operator=(PmergeMe const &rhs);
	void	printLst(void) const;
};
