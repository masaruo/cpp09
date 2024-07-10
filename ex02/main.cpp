/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:02:44 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/08 10:18:59 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <deque>
#include <vector>
#include <sstream>
#include "color.hpp"
#include <exception>

void	print_duration(std::size_t argc_, std::string const &container, double duration)
{
	std::stringstream ss;

	ss << "Time to process a range of ";
	ss << argc_;
	ss << " elements with std::" << container << " : ";
	ss << std::fixed << duration << " ms";
	std::cout << ss.str() << std::endl;
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	try
	{
		PmergeMe<std::vector<std::size_t> >vec_sort(const_cast<char const **>(argv));
		PmergeMe<std::deque<std::size_t> >deque_sort(const_cast<char const **>(argv));
		vec_sort.sort_start();
		deque_sort.sort_start();
		std::cout << BLUE;
		vec_sort.print();
		std::cout << MAGENTA;
		print_duration(vec_sort.get_valid_argc(), "vector", vec_sort.get_duration());
		std::cout << YELLOW;
		// deque_sort.print();
		print_duration(deque_sort.get_valid_argc(), "deque", deque_sort.get_duration());
		std::cout << RESET;
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << '\n';
		return (1);
	}
	catch(...)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	return (0);
}
