/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:28:39 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/10 16:55:13 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "xString.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iterator>
// #include <utility>
// #include <algorithm>
// #include <vector>
// #include <deque>
// #include <limits>
// #include <exception>
// #include <stdexcept>

template <typename Con>
class PmergeMe
{
public: //typedef
	typedef typename Con::const_iterator	const_iterator;
	typedef typename Con::iterator			iterator;
	typedef typename Con::size_type			size_type;
	typedef typename Con::difference_type	difference_type;

private:
	Con			argv_seq;
	Con			jacob_seq;
	Con			sorted_seq;
	double		sorting_duration;
	double		data_mgmt_duration;
	size_type	valid_argc;
	void	gen_argv_seq(char const **argv);
	void	gen_jacob_seq(size_type size);
	Con		merge_insert_sort(Con *prev_main, Con *prev_pmend);
	void	print_con(Con const &con) const;
	PmergeMe();//hidden
	PmergeMe(PmergeMe const &rhs);
	PmergeMe &operator=(PmergeMe const &rhs);
public:
	PmergeMe(char const **argv);
	~PmergeMe();
	void		sort_start(void);
	double		get_duration(void) const;
	std::size_t	get_valid_argc(void) const;
	void		print(void) const;
	#ifdef DEBUG
	void	debug(Con main, Con pmend, Con prevmain, Con prevpmend, std::string msg);
	void	debug_print(Con c, std::string);
	#endif
};

static void put(std::size_t const &n)
{
	std::cout << n << " ";
}

template <typename Con>
void	PmergeMe<Con>::print_con(Con const &con) const
{
	const_iterator	beg = con.begin();
	const_iterator	end = con.end();

	std::for_each(beg, end, &put);
}

template <typename Con>
void	PmergeMe<Con>::print(void) const
{
	std:: cout << "Before: ";
	std::for_each(argv_seq.begin(), argv_seq.end(), &put);
	std::cout << std::endl << "After : ";
	std::for_each(sorted_seq.begin(), sorted_seq.end(), &put);
	std::cout << std::endl;
}

template <typename Con>
PmergeMe<Con>::PmergeMe(){ return ; }// hidden

template <typename Con>
PmergeMe<Con>::PmergeMe(char const **argv)
{
	std::clock_t start = std::clock();
	gen_argv_seq(argv);
	valid_argc = argv_seq.size();
	gen_jacob_seq(valid_argc + 1);
	std::clock_t end = std::clock();
	data_mgmt_duration = static_cast<double>((end - start)) / CLOCKS_PER_SEC * 1000.0;
}

template <typename Con>
PmergeMe<Con>::~PmergeMe()
{
	return ;
}

template <typename Con>
PmergeMe<Con>::PmergeMe(PmergeMe const &rhs)//hidden
{
	(void) rhs;
	return ;
}

template <typename Con>
PmergeMe<Con>	&PmergeMe<Con>::operator=(PmergeMe const &rhs)//hidden
{
	(void) rhs;
	return (*this);
}

static void	assert_valid_number(xString const &num_str, std::stringstream const &ss)
{
	if (!ss || ss.str().empty())
		throw(std::invalid_argument("Error"));
	else if (num_str.contain_not_of("0123456789"))
		throw (std::invalid_argument("Error"));
}

template <typename Con>
void	PmergeMe<Con>::gen_argv_seq(char const **argv)
{
	for (std::size_t i = 1; argv[i]; i++)
	{
		xString	num_str = argv[i];
		std::stringstream num_ss(num_str);
		std::size_t	num_ui;
		num_ss >> num_ui;
		assert_valid_number(num_str, num_ss);
		argv_seq.push_back(num_ui);
	}
}

template <typename Con>
void	PmergeMe<Con>::gen_jacob_seq(size_type size)
{
	size_type	prev = 1;
	size_type	before_prev = 0;
	size_type	jacob = 0;

	jacob_seq.push_back(0);
	while (true)
	{
		jacob = prev + (2 * before_prev);
		jacob_seq.push_back(jacob);
		for (size_type i = jacob - 1; i > prev; i--)
		{
			jacob_seq.push_back(i);
		}
		if (std::find(jacob_seq.begin(), jacob_seq.end(), size) != jacob_seq.end())
			break ;
		before_prev = prev;
		prev = jacob;
		jacob++;
	}
	return ;
}

template <typename Con>
double	PmergeMe<Con>::get_duration(void) const
{
	return (sorting_duration + data_mgmt_duration);
}

template <typename Con>
std::size_t	PmergeMe<Con>::get_valid_argc(void) const
{
	return (valid_argc);
}

#include <sys/time.h>

template <typename Con>
void	PmergeMe<Con>::sort_start(void)
{
	std::clock_t start = std::clock();
	sorted_seq = merge_insert_sort(NULL, NULL);
	std::clock_t end = std::clock();
	sorting_duration = static_cast<double>((end - start)) / CLOCKS_PER_SEC * 1000.0;
}

#ifdef DEBUG
#include <sstream>
template <typename Con>
void	PmergeMe<Con>::debug_print(Con c, std::string msg)
{
	typename Con::const_iterator	iter = c.begin();
	std::cout << "[" << msg << "]";
	while (iter != c.end())
	{
		std::cout << "" << *iter << " ";
		iter++;
	}
	std::cout << std::endl;
}

template <typename Con>
void	PmergeMe<Con>::debug(Con main, Con pmend, Con prevmain, Con prevpmend, std::string msg)
{
	std::cout << msg << std::endl;
	debug_print(main, "main");
	debug_print(pmend, "pmend");
	debug_print(prevmain, "prevmain");
	debug_print(prevpmend, "prevpmend");
	std::cout << std::endl;
}
#endif

template <typename Con>
Con	PmergeMe<Con>::merge_insert_sort(Con *prev_main, Con *prev_pmend)
{
	Con			main, pmend;

	if (prev_main == NULL)
	{
		main = argv_seq;
	}
	//スタック積み上げ時
	else
	{
		const_iterator		crnt = prev_main->begin();
		const_iterator		next = prev_main->begin() + 1;
		const_iterator		end = prev_main->end();

		while (crnt != end && next != end)
		{
			main.push_back(std::max(*crnt, *next));
			pmend.push_back(std::min(*crnt, *next));
			crnt += 2, next += 2;
		}
		if (crnt != end)
			pmend.push_back(*crnt);
	}

	//再起キックイン
	if (main.size() > 1)
	{
		merge_insert_sort(&main, &pmend);
	}

	//スタック減少時
	//jacobの順番に沿ってpmendの数字をmainに戻す
	if (prev_main == NULL || prev_pmend == NULL)
		return (main);
	#ifdef DEBUG
	debug(main, pmend, *prev_main, *prev_pmend, "before loop: ");
	#endif
	pmend.insert(pmend.begin(), main.begin(), main.end());
	for (const_iterator jacob_idx = jacob_seq.begin(); jacob_idx != jacob_seq.end(); jacob_idx++)
	{
		if (*jacob_idx >= pmend.size())
			continue ;
		//jacobのindexに対応したpmendの数字を確保
		std::size_t	value_to_insert_into_main = pmend.at(*jacob_idx);

		//@prev_main: 数字のindexを確保
		const_iterator	pos_in_prevmain = std::find(prev_main->begin(), prev_main->end(), value_to_insert_into_main);
		difference_type	idx_of_shift_tgt = pos_in_prevmain - prev_main->begin();

		//上記INDEXのprevpmend数字を確保
		// std::size_t	prevmain_insert_val = prev_main->at(idx_of_shift_tgt);//?should be equal to value_to_insert
		std::size_t	prevpmend_insert_val = prev_pmend->at(idx_of_shift_tgt);//prev_pmendの対応する数値

		//insert_idxの数字を削除
		prev_main->erase(prev_main->begin() + idx_of_shift_tgt);
		prev_pmend->erase(prev_pmend->begin() + idx_of_shift_tgt);
		//mainにおいて、ターゲットの数値をインサートする場所を見つける
		iterator	insert_pos_iter = std::lower_bound(prev_main->begin(), prev_main->end(), value_to_insert_into_main);
		std::size_t		insert_pos_idx = std::distance(prev_main->begin(), insert_pos_iter);
		
		prev_main->insert(prev_main->begin() + insert_pos_idx, value_to_insert_into_main);
		prev_pmend->insert(prev_pmend->begin() + insert_pos_idx, prevpmend_insert_val);
	}
		// main = *prev_main;
		// pmend = *prev_pmend;
		#ifdef DEBUG
		debug(main, pmend, *prev_main, *prev_pmend, "after loop: ");
		#endif
		return (main);
}
