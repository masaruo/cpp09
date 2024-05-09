/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 00:34:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/09 15:04:39 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw (std::invalid_argument("Error: could not open file."));
		BitcoinExchange btc(argv[1]);
	}
	catch(std::invalid_argument const &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "some error detected." << std::endl;
	}
	return (0);
}
