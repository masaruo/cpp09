/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:02:44 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/09 18:36:55 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Error" << std::endl;
	}
	PmergeMe	pm(const_cast<char const **>(argv + 1));
	pm.printLst();
	return (0);
}
