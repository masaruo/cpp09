/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:02:44 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/22 15:13:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <deque>
#include <vector>
#include <sstream>
#include "color.hpp"
#include "iomanip"

// void	print_duration(std::size_t argc_, std::string const &container, double duration)
// {
// 	std::stringstream ss;

// 	ss << "Time to process a range of ";
// 	ss << argc_;
// 	ss << " elements with std::" << container << " : ";
// 	ss << std::fixed << duration << " ms";
// }



int	main(int argc, char **argv)
{
	//todo argc
	PmergeMe<std::vector<std::size_t> >pm(const_cast<char const **>(argv));
	pm.sort_start();
	pm.print();
	return (0);
}
