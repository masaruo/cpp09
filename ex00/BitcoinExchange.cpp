/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:52:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/15 11:32:31 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <utility>

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

map_iter	BitcoinExchange::get_spot_or_lower_iter(std::string const &key) const
{
	map_iter	iter;

	iter = rate_.find(key);
	if (iter == rate_.end())
	{
		iter = rate_.lower_bound(key);
		if (iter != rate_.begin())
			iter--;
	}
	return (iter);
}

void	BitcoinExchange::assert_correct_value_range(std::string const &value, std::string const &buf) const
{
	for (string_iter i = value.begin(); i != value.end(); i++)
	{
		if (!std::isdigit(*i) && *i != '-' && *i != '+' && *i != '.')
			throw(BtcBadInput(buf));
	}
	double	const val_d = std::atof(value.c_str());
	if (val_d > 1000)
		throw (BtcTooLargeValueException());//float flow check omitted
	else if (val_d < 0)
		throw (BtcNegativeValueException());
}

void	BitcoinExchange::assert_date_correct(std::string const &date, std::string const &buf) const
{
	// 2011-01-03
	bool				is_valid = true;
	std::string const	delim = "-";
	std::string const	yyyy = date.substr(0, date.find(delim));
	std::string const	mm = date.substr(date.find(delim) + 1, 2);
	std::string const	dd = date.substr(date.rfind(delim) + 1, 2);
	// std::cout << yyyy << mm << dd << std::endl;
	if (yyyy < "2009" || yyyy > "2022")
		is_valid = false;
	else if (mm < "01" || mm > "12")
		is_valid = false;
	else if (dd < "01" || dd > "31")
		is_valid = false;
	else
		;
	if (!is_valid)
		throw (BtcBadInput(buf));
}

void	BitcoinExchange::assert_correct_input(std::string const &date, std::string const &buf, std::string const &value) const
{
	assert_date_correct(date, buf);
	assert_correct_value_range(value, buf);
}

void	BitcoinExchange::input_handler(std::string const &buf)
{
		std::string const	delim = " | ";
	try
	{
		if (buf.empty())
			throw (BtcBadInput(buf));
		std::string const	date = buf.substr(0, buf.find(delim));
		std::string const	value = buf.substr(buf.find(delim) + 3, buf.size());
		if (date == "date")
			return ;
		assert_correct_input(date, buf, value);
		double const		price_d = std::atof(value.c_str());
		map_iter	iter = get_spot_or_lower_iter(date);
		if (iter != rate_.end())
		{
			std::cout << date << " => " << price_d << " = " << iter->second * price_d << std::endl;
		}
	}
	catch (std::out_of_range const &e)
	{
		throw (BtcBadInput(buf));
	}
	catch (BtcBadInput const &e)
	{
		std::cout << e.what() << std::endl;
		return ;
	}
	catch (BtcNegativeValueException const &e)
	{
		std::cout << e.what() << std::endl;
		return ;
	}
	catch (BtcTooLargeValueException const &e)
	{
		std::cout << e.what() << std::endl;
		return ;
	}
	catch (std::exception const &e)
	{
		std::cout << e.what() << std::endl;
		return ;
	}
}

void	BitcoinExchange::parseData(std::string const &file, f fptr)
{
	std::ifstream	ifs(file);
	if (ifs.fail())
	{
		throw (std::invalid_argument("Error: could not open file."));
	}
	for (std::string buf; std::getline(ifs, buf);)
	{
		(this->*fptr)(buf);
	}
}

BitcoinExchange::BitcoinExchange(){ return ; }
BitcoinExchange::BitcoinExchange(std::string const &input)
{
	parseData("./data.csv", &BitcoinExchange::parse_data_csv);//!関数ポインタ渡すときは＆className::func
	parseData(input, &BitcoinExchange::input_handler);
	return ;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &rhs)
:rate_(rhs.rate_)
{
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
		this->rate_ = rhs.rate_;
	}
	return (*this);
}

//!exceptions
BitcoinExchange::BTCException::BTCException()
:std::logic_error("logic error")
{
	return ;
}

char const	*BitcoinExchange::BTCException::what() const throw ()
{
	return ("BTC Exception.");
}

char const	*BitcoinExchange::BtcNegativeValueException::what() const throw ()
{
	return ("Error: not a positive number.");
}

char const	*BitcoinExchange::BtcTooLargeValueException::what() const throw ()
{
	return ("Error: too large a number.");
}

BitcoinExchange::BtcBadInput::BtcBadInput(std::string const &buf)
:error_msg("Error: bad input => " + buf)
{
	return ;
}

char const	*BitcoinExchange::BtcBadInput::what() const throw ()
{
	return (error_msg.c_str());
}
