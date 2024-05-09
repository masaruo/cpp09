/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:52:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/08 18:49:46 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <utility>
#include <algorithm>
#include <limits>

void	BitcoinExchange::parse_data_csv(std::string const &buf)
{
	std::pair<std::string, double>	pair;

	std::string const	date = buf.substr(0, buf.find(","));
	std::string const	rate = buf.substr(buf.find(",") + 1);
	if (date == "date")
		return ;
	pair.first = date;
	pair.second = std::atof(rate.c_str());
	rate_.insert(pair);
	return ;
}

btc_it	BitcoinExchange::get_spot_or_lower_iter(std::string const &key) const
{
	btc_it	iter;

	iter = rate_.find(key);
	if (iter == rate_.end())
	{
		iter = rate_.lower_bound(key);
		if (iter != rate_.begin())
			iter--;
	}
	return (iter);
}

void	BitcoinExchange::assert_correct_value_range(std::string const &value) const
{
	double	const val_d = std::atof(value.c_str());

	if (val_d > 1000)
		throw (BtcTooLargeValueException());
	else if (val_d < 0)
		throw (BtcNegativeValueException());
}

static bool	is_date_correct(std::string const &date)
{
	// 2011-01-03
	std::string const	delim = "-";
	std::string const	yyyy = date.substr(0, date.find(delim));
	std::string const	mm = date.substr(date.find(delim) + 1, 2);
	std::string const	dd = date.substr(date.rfind(delim) + 1, 2);
	// std::cout << yyyy << mm << dd << std::endl;
	if (yyyy < "2009" || yyyy > "2022")
		return (false);
	else if (mm < "01" || mm > "12")
		return (false);
	else if (dd < "01" || dd > "31")
		return (false);
	else
		return (true);
}

void	BitcoinExchange::assert_correct_input(std::string const &date, std::string const &delim, std::string const &value) const
{
	std::cout << delim << std::endl;
}

void	BitcoinExchange::input_handler(std::string const &buf)
{
	std::string const	delim = " | ";
	std::string const	date = buf.substr(0, buf.find(delim));
	std::string const	delim_part = buf.substr(buf.find(delim), buf.find(delim) + 3);
	std::string const	value = buf.substr(buf.find(delim) + 3, buf.size());

	//todo delete
	std::cout << is_date_correct(date) << " | " << date << std::endl;

	if (date == "date")
		return ;
	try
	{
		assert_correct_input(date, delim_part, value);
		assert_correct_value_range(value);
		double const		price_d = std::atof(value.c_str());
		btc_it	iter = get_spot_or_lower_iter(date);
		if (iter != rate_.end())
		{
			std::cout << date << " => " << price_d << " = " << iter->second * price_d << std::endl;
			// std::cout << "first: " << iter->first << " and 2nd: " << iter->second << std::endl;
		}
	}
	catch (std::out_of_range const &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void	BitcoinExchange::parseData(std::string const &file, f fptr)
{
	std::ifstream	ifs(file);
	if (ifs.fail())
	{
		std::cout << "Error: failed to open the data.csv." << std::endl;
		std::exit(1);
	}
	for (std::string buf; std::getline(ifs, buf);)
	{
		(this->*fptr)(buf);
	}
}

BitcoinExchange::BitcoinExchange(){ return ; }
BitcoinExchange::BitcoinExchange(std::string const &input)
{
	parseData("./data.csv", &BitcoinExchange::parse_data_csv);
	parseData(input, &BitcoinExchange::input_handler);
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

//exceptions
char const	*BitcoinExchange::BtcNegativeValueException::what() const throw ()
{
	return ("Error: not a positive number.");
}

char const	*BitcoinExchange::BtcTooLargeValueException::what() const throw ()
{
	return ("Error: too large a number.");
}

// char const	*BitcoinExchange::BtcBadInputException::what() const throw ()
// {
// 	return (this->err_.c_str());
// }
