/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/21 20:55:39 by mogawa           ###   ########.fr       */
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

//! input number is positive integer from 0 to 1 less than size_t max

template <typename C>
class PmergeMe
{
public:
	typedef typename C::const_iterator				citer_t;
	typedef typename C::iterator					iter_t;
	typedef typename C::size_type					csize_t;
	// typedef typename C::difference_type				cdiff_t;
	typedef	std::pair<std::size_t, std::size_t>		pair_t;
	typedef std::vector<pair_t>						pair_seq;
	typedef	pair_seq::iterator						pair_iter;
	typedef pair_seq::const_iterator				pair_citer;
	typedef pair_seq::size_type						psize_t;
	// typedef	pair_seq.first						large;
	// typedef	pair_seq.second						small;
	static std::size_t const						sizemax_;

private:
	C					argv_seq;
	C					sorted_seq;
	C					jacob_seq;
	double				duration;
	static std::size_t const	THRESHOLD = 2;
	PmergeMe();//hidden
	//! helper functions
	void		gen_argv_seq(char const **argv);
	void		genJacobSeq(csize_t size);
	C			merge_insert_sort(C prev);
	C			convert(pair_seq pair);
	pair_seq	convert(C cont);
	C			insert(pair_seq pair);
	pair_seq	sort_pair(C const &large, pair_seq unsorted);

public:
	PmergeMe(char const **argv);
	PmergeMe(PmergeMe const &rhs);
	~PmergeMe();
	PmergeMe &operator=(PmergeMe const &rhs);
	void	sort_start(void);
	double	get_duration(void) const;
};

#include "PmergeMe.tpp"

template <typename C>
std::size_t	const PmergeMe<C>::sizemax_ = std::numeric_limits<std::size_t>::max();

template <typename C>
PmergeMe<C>::PmergeMe()//hidden
{
	return ;
}

template <typename C>
PmergeMe<C>::PmergeMe(char const **argv)
{
	gen_argv_seq(argv);
	genJacobSeq(argv_seq.size() / 2 + 1);
}

template <typename C>
PmergeMe<C>::~PmergeMe()
{
	return ;
}

template <typename C>
PmergeMe<C>::PmergeMe(PmergeMe const &rhs)
{
	//todo
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
	else if (num_ui == std::numeric_limits<std::size_t>::max())
		is_valid = false;
	else if (num_str != "0" && num_ui == 0)
		is_valid = false;
	return (is_valid);
}

template <typename C>
void	PmergeMe<C>::gen_argv_seq(char const **argv)
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

template <typename C>
double	PmergeMe<C>::get_duration(void) const
{
	return (duration);
}

template <typename C>
void	PmergeMe<C>::sort_start(void)
{
	C	sorting = argv_seq;
	std::time_t	start = std::time(NULL);
	C empty, sorted;
	sorted = merge_insert_sort(empty);
	sorted_seq = sorted;
	std::time_t	end = std::time(NULL);
	duration = static_cast<double>((start - end)) / CLOCKS_PER_SEC * 1000.0;
}

template <typename C>
C PmergeMe<C>::merge_insert_sort(C prev)
{
    pair_seq crnt;
    C bigger;
	C sorted;

    if (prev.empty())
    {
        crnt = convert(argv_seq); // Initial call, convert the initial sequence
    }
    else 
    {
        crnt = convert(prev); // Recursive call, convert the previous sequence
    }
    
    bigger = convert(crnt); // Convert the current pairs to a container of large elements

    std::cout << "Bigger: ";
    for (citer_t it = bigger.begin(); it != bigger.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    if (crnt.size() > 2)
    {
        // return bigger;
    	sorted = merge_insert_sort(bigger);
    }


    pair_seq sorted_pair = sort_pair(sortedq, crnt);

    C res = insert(sorted_pair);

    std::cout << "Result: ";
    for (citer_t it = res.begin(); it != res.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    return res;
}


// template <typename C>
// C	PmergeMe<C>::merge_insert_sort(C prev)
// {
// 	pair_seq	crnt;
// 	C			bigger;
// 	//!Ascending phase (create pair by spliting large)
// 	if (prev.empty())
// 	{
// 		crnt = convert(argv_seq);
// 	}
// 	else 
// 	{
// 		crnt = convert(prev);
// 	}
// 	bigger = convert(crnt);
// 	if (crnt.size() == 2)
// 		return (bigger);
// 	C	sorted = merge_insert_sort(bigger);
// 	//!Decending phase
// 	pair_seq	sorted_pair;
// 	sorted_pair = sort_pair(sorted, crnt);
// 	C			res;
// 	res = insert(sorted_pair);
// 	//todo sortedをベースにcrntのlargeをソート、そして、smを挿入ソート
// 	//todo 新しいソートされたコンテナをリターン
// 	return (res);
// }


// template <typename C>
// typename PmergeMe<C>::pair_seq	PmergeMe<C>::sort_pair(C const &large, pair_seq unsorted)
// {
// 	csize_t		size = large.size();
// 	pair_seq	sorted(size);
// 	pair_iter	it = unsorted.begin();

// 	while (it != unsorted.end())
// 	{
// 		citer_t pos = std::find(large.begin(), large.end(), (*it).first);
// 		if (pos == large.end())
// 		{
// 			throw (std::runtime_error("Elem not found in sort_pair"));
// 		}
// 		std::size_t index = pos - large.begin();
// 		sorted.at(index) = *it;
// 		it++;
// 	}
// 	return (sorted);
// }

// Function implementations
template <typename C>
typename PmergeMe<C>::pair_seq PmergeMe<C>::sort_pair(const C &large, pair_seq unsorted)
{
    std::size_t size = large.size();
    pair_seq sorted(size);
    typename pair_seq::iterator it = unsorted.begin();

    while (it != unsorted.end())
    {
        citer_t pos = std::find(large.begin(), large.end(), it->first);
        if (pos == large.end())
        {
            // throw std::runtime_error("Element not found in large container");
        }
        std::size_t index = pos - large.begin();
        sorted.at(index) = *it;
        ++it;
    }
    return sorted;
}
template <typename C>
C PmergeMe<C>::insert(pair_seq pair)
{
    C cont;
    C tmp;
    pair_citer p_iter = pair.begin();
    std::size_t size = pair.size();

    // Add first elements to 'cont' and second elements to 'tmp'
    while (p_iter != pair.end())
    {
        cont.push_back(p_iter->first);
        tmp.push_back(p_iter->second);
        ++p_iter;
    }

    // Print current state
    std::cout << "Cont (first elements): ";
    for (citer_t it = cont.begin(); it != cont.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Tmp (second elements): ";
    for (citer_t it = tmp.begin(); it != tmp.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    // Insert second elements based on Jacob's sequence
    for (std::vector<std::size_t>::const_iterator jacob_iter = jacob_seq.begin();
         jacob_iter != jacob_seq.end() && *jacob_iter <= size;
         ++jacob_iter)
    {
        citer_t idx_by_jacob = tmp.begin();
        std::advance(idx_by_jacob, *jacob_iter);
        std::size_t insert_val = *idx_by_jacob;
        typename C::iterator insert_pos = std::lower_bound(cont.begin(), cont.end(), insert_val);
        cont.insert(insert_pos, insert_val);

        // Print current state
        std::cout << "Inserting " << insert_val << ": ";
        for (citer_t it = cont.begin(); it != cont.end(); ++it)
            std::cout << *it << " ";
        std::cout << std::endl;
    }

    return cont;
}


// template <typename C>
// C	PmergeMe<C>::insert(pair_seq pair)
// {
// 	C				cont;
// 	C				tmp;
// 	citer_t			jacob_iter = jacob_seq.begin();
// 	pair_citer		p_iter = pair.begin();
// 	psize_t			size = pair.size();

// 	while (p_iter != pair.end())
// 	{
// 		cont.push_back((*p_iter).first);
// 		tmp.push_back((*p_iter).second);
// 		p_iter++;
// 	}
// 	while (jacob_iter != jacob_seq.end() && *jacob_iter <= size)
// 	{
// 		citer_t	idx_by_jacob = tmp.begin();
// 		std::advance(idx_by_jacob, *jacob_iter);
// 		std::size_t	insert_val = *idx_by_jacob;
// 		citer_t	insert_pos = std::lower_bound(cont.begin(), cont.end(), insert_val);
// 		cont.insert(insert_pos, insert_val);
// 		jacob_iter++;
// 	}
// }

template <typename C>
C PmergeMe<C>::convert(pair_seq pair)
{
    typedef typename pair_seq::const_iterator pair_citer;

    C cont;
    pair_citer it = pair.begin();

    while (it != pair.end())
    {
        cont.push_back(it->first);
        ++it;
    }
    return cont;
}



// template <typename C>
// C	PmergeMe<C>::convert(pair_seq pair)
// {
// 	C cont;
// 	pair_citer it = pair.begin();

// 	while (it != pair.end())
// 	{
// 		cont.push_back((*it).first);
// 		it++;
// 	}
// 	return (cont);
// }


template <typename C>
typename PmergeMe<C>::pair_seq PmergeMe<C>::convert(C cont)
{
    typedef typename C::const_iterator citer_t;

    citer_t crnt = cont.begin();
    citer_t next;
    pair_seq pair;

    // Handle the case where the container is empty or has one element
    if (cont.empty() || cont.size() == 1)
        return pair;

    next = crnt;
    ++next;
    while (crnt != cont.end() && next != cont.end())
    {
        pair.push_back(std::make_pair(std::max(*crnt, *next), std::min(*crnt, *next)));
        std::advance(crnt, 2);
        std::advance(next, 2);
    }

    // Handle the case where there is an odd number of elements
    if (crnt != cont.end())
    {
        std::size_t first = sizemax_;
        std::size_t second = *crnt;
        pair.push_back(std::make_pair(first, second));
    }
    return pair;
}

// template <typename C>
// typename PmergeMe<C>::pair_seq	PmergeMe<C>::convert(C cont)
// {
// 	citer_t			crnt = cont.begin();
// 	citer_t			next;
// 	pair_seq		pair;

// 	//todo error
// 	// if (cont.empty() || size == 1)
// 	// 	return ;
// 	next = crnt + 1;
// 	while (crnt != cont.end() && next != cont.end())// nextの領域外アクセス？
// 	{
// 		pair.push_back(std::make_pair(std::max(*crnt, *next), std::min(*crnt, *next)));
// 		next += 2;
// 		crnt += 2;
// 	}
// 	if (crnt != cont.end())
// 	{
// 		std::size_t first = sizemax_;
// 		std::size_t second = *crnt;
// 		pair.push_back(std::make_pair(first, second));
// 	}
// 	return (pair);
// }

template <typename C>
void	PmergeMe<C>::genJacobSeq(csize_t size)
{
	csize_t	prev = 1;
	csize_t	before_prev = 0;
	csize_t	jacob = 0;

	while (jacob < size)
	{
		jacob = prev + (2 * before_prev);
		jacob_seq.push_back(jacob);
		for (csize_t i = jacob - 1; i > prev; i--)
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
