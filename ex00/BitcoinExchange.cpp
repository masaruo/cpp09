/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:52:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/03 01:43:35 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <utility>
#include <algorithm>

BitcoinExchange::BitcoinExchange(){ return ; }
BitcoinExchange::BitcoinExchange(std::string const &file, int amt)
{
	std::ifstream ifs(file);
	if (ifs.fail())
	{
		std::cout << "failed to open the csv file." << std::endl;
		std::exit(1);
	}
	for (std::string buf; std::getline(ifs, buf);)
	{
		std::string::const_iterator	delim;
		delim = std::find(buf.begin(), buf.end(), ',');
		std::string	first(buf.begin(), std::string::difference_type(delim - buf.begin()));
		data_.emplace(std::make_pair(buf, ))
		std::cout << buf << std::endl;
	}
	return ;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &rhs)
{
	//todo
	return ;
}

BitcoinExchange::~BitcoinExchange()
{
	return ;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this != &rhs)
	{
		//todo
	}
	return (*this);
}
