/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/15 11:17:56 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <ostream>
#include <utility>
#include <iostream>
#include <algorithm>
#include <ctime>

template <typename T, template<typename, typename = std::allocator<T> > class C>
class PmergeMe
{
private:
	C<std::pair<T, T>, std::allocator<std::pair<T, T> > > pair_lst;
	C<T>		argv_container;
	C<T>		main;
	C<T>		pmend;
	C<T>		jacob_seq;
	double		duration;
	std::size_t	argc_;
	//!helper functions
	std::size_t						make_pair_seq_and_get_odd(char const **argv);
	void							make_main_and_pmend(bool odd, std::size_t odd_num);
	void							make_jacobsthal_seq(std::size_t size);
	void							insert_pmend(void);
	typename C<T>::const_iterator	get_pmend_iter(std::size_t idx) const;
	void							print_container(C<T> const &container) const;
	//!typedef for iter
	typedef typename C<T>::const_iterator	c_const_iter;
	typedef typename C<T>::iterator			c_iter;
	typedef typename C<std::pair<T, T>, std::allocator<std::pair<T, T> > >::const_iterator	pair_const_iter;
	typedef typename C<std::pair<T, T>, std::allocator<std::pair<T, T> > >::iterator		pair_iter;
	PmergeMe();
	PmergeMe(PmergeMe const &rhs);
	PmergeMe &operator=(PmergeMe const &rhs);
	struct sort_op
	{
		bool	operator()(std::pair<std::size_t, std::size_t> &lhs, std::pair<std::size_t, std::size_t> &rhs)
		{
			return (rhs.first > lhs.first);
		}
	};
public:
	PmergeMe(int const argc, char const **argv);
	~PmergeMe();
	void	print_argv(void) const;
	void	print_sorted(void) const;
	double	get_duration(void) const;
	std::size_t	get_argc_(void) const;
};

template <typename T>
static void	print(T const &n)
{
	std::cout << n << " ";
}

// hidden default constructor
template <typename T, template<typename, typename = std::allocator<T> > class C>
PmergeMe<T, C>::PmergeMe(){ return ; }

template <typename T, template<typename, typename = std::allocator<T> > class C>
void	PmergeMe<T, C>::print_container(C<T> const &container) const
{
	std::for_each(container.begin(), container.end(), print<T>);
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
void	PmergeMe<T, C>::print_argv(void) const
{
	std::cout << "Before: ";
	print_container(argv_container);
	std::cout << std::endl;
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
void	PmergeMe<T, C>::print_sorted(void) const
{
	std::cout << "After: ";
	print_container(main);
	std::cout << std::endl;
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
double	PmergeMe<T, C>::get_duration(void) const
{
	return (duration);
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
std::size_t	PmergeMe<T, C>::get_argc_(void) const
{
	return (argc_);
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
void	PmergeMe<T, C>::make_jacobsthal_seq(std::size_t size)
{
	std::size_t	prev = 1;
	std::size_t	before_prev = 0;
	std::size_t	jacob = 0;
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
	return ;
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

static std::size_t	validate_input_and_get_argc(int const argc, char const **argv)
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
	else if (i == 2)
	{
		std::cout << argv[1] << std::endl;
		std::exit(0);
	}
	return (i);
}

static bool	is_odd(char const **argv)
{
	std::size_t i = 1;

	while(argv[i])
		i++;
	if (i % 2 != 0)
		return (true);
	else
		return (false);
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
typename C<T>::const_iterator PmergeMe<T, C>::get_pmend_iter(std::size_t idx) const
{
	std::size_t		i = 1;
	c_const_iter	it = pmend.begin();

	while (i < idx)
	{
		if (i == idx)
			return (it);
		it++;
		i++;
	}
	return (it);
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
std::size_t	PmergeMe<T, C>::make_pair_seq_and_get_odd(char const **argv)
{
	std::size_t	odd_left = 0;
	std::size_t	i = 1;

	while (argv[i] && argv[i + 1])
	{
		std::size_t	first = std::strtoull(argv[i], NULL, 10);
		std::size_t	second = std::strtoull(argv[i + 1], NULL, 10);
		argv_container.push_back(first);
		argv_container.push_back(second);
		std::pair<std::size_t, std::size_t> pair(std::max(first, second), std::min(first, second));
		pair_lst.push_back(pair);
		i += 2;
		if (argv[i + 1] == NULL)
		{
			odd_left = std::strtoull(argv[i], NULL, 10);
			argv_container.push_back(odd_left);
		}
	}
	std::sort(pair_lst.begin(), pair_lst.end(), sort_op());
	//std::sort needs random access iter = vector, deque. list has own sort function.
	return (odd_left);
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
void	PmergeMe<T, C>::make_main_and_pmend(bool odd, std::size_t odd_num)
{
	pair_iter	iter = pair_lst.begin();

	while (iter != pair_lst.end())
	{
		main.push_back((*iter).first);
		pmend.push_back((*iter).second);
		iter++;
	}
	if (odd)
		pmend.push_back(odd_num);
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
void	PmergeMe<T, C>::insert_pmend(void)
{
	c_const_iter	jacob_iter = jacob_seq.begin();
	while (jacob_iter != jacob_seq.end())
	{
		if (*jacob_iter <= pmend.size())
		{
			c_const_iter	main_lower_bound = std::lower_bound(main.begin(), main.end(), *get_pmend_iter(*jacob_iter));
			main.insert(main_lower_bound, *get_pmend_iter(*jacob_iter));
		}
		jacob_iter++;
	}
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
PmergeMe<T, C>::PmergeMe(int const argc, char const **argv)
{
	argc_ = validate_input_and_get_argc(argc, argv);
	bool const			odd_flg = is_odd(argv + 1);
	std::clock_t const	start = std::clock();
	std::size_t const	odd_num = make_pair_seq_and_get_odd(argv);
	make_main_and_pmend(odd_flg, odd_num);
	make_jacobsthal_seq(pmend.size());
	insert_pmend();
	std::clock_t const	end = std::clock();
	// duration = static_cast<double>(1000.0 * (end - start) / CLOCKS_PER_SEC);
	duration = 1000.0 * (end - start) / CLOCKS_PER_SEC;
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
PmergeMe<T, C>::~PmergeMe()
{
	return ;
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
PmergeMe<T, C>::PmergeMe(PmergeMe const &rhs)
{
	(void) rhs;
	return ;
}

template <typename T, template<typename, typename = std::allocator<T> > class C>
PmergeMe<T, C> &PmergeMe<T, C>::operator=(PmergeMe const &rhs)
{
	(void) rhs;
	return (*this);
}

//merge insertion sort
// https://codereview.stackexchange.com/questions/116367/ford-johnson-merge-insertion-sort

// template template parameter
// https://stackoverflow.com/questions/16596422/template-class-with-template-container

// clock_t
// https://en.cppreference.com/w/cpp/chrono/c/clock
