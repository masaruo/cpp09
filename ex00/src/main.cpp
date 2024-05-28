/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 08:43:33 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/27 12:23:01 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "iostream"
#include <exception>

int	main(int argc, char **argv)
{
	try
	{
		if (argc == 1)
		{
			throw (std::invalid_argument("Error: could not open file."));
			return (1);
		}
		BitcoinExchange	btc;
		// btc.calculate(const_cast<char const**>(argv));
		std::cout << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}
