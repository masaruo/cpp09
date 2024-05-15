/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:02:44 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/15 11:18:13 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include "color.hpp"
#include "iomanip"

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
	PmergeMe<std::size_t, std::vector>	pm_vec(argc, const_cast<char const **>(argv));
	PmergeMe<std::size_t, std::deque>	pm_deq(argc, const_cast<char const **>(argv));
	std::cout << RED;
	pm_vec.print_argv();
	std::cout << BLUE;
	pm_vec.print_sorted();
	std::cout << CYAN;
	// pm_deq.print_sorted();
	// std::cout << GREEN;
	print_duration(pm_vec.get_argc_(), "vector", pm_vec.get_duration());
	std::cout << MAGENTA;
	print_duration(pm_deq.get_argc_(), "deq", pm_deq.get_duration());
	std::cout << RESET;
	return (0);
}
