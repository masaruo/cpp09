/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:52:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/17 19:05:35 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

std::string BitcoinExchange::DIGITS = "0123456789";

bool	BitcoinExchange::parse_data_csv(std::string const &line)
{
	std::istringstream	iss(line);
	std::string	key, value_str;
	double		value;
	if (std::getline(iss, key, ',') && std::getline(iss, value_str))
	{
		std::stringstream	ss(value_str);
		ss >> value;
		px_.insert(std::make_pair(key, value));
		return (true);
	}
	else
		return (false);
}

void	BitcoinExchange::assert_input_date(std::string const &line, std::string const &date)
{
	std::istringstream	iss(date);
	std::string	yyyy, mm, dd;

	if (std::getline(iss, yyyy, '-') && std::getline(iss, mm, '-') && std::getline(iss, dd))
	{
		if (yyyy.find_first_not_of(DIGITS) != std::string::npos 
			|| mm.find_first_not_of(DIGITS) != std::string::npos
			|| dd.find_first_not_of(DIGITS) != std::string::npos) // no digits?
		{
			throw(BTCBadInputException(line));
		}

		std::stringstream ymd_ss(yyyy + mm + dd);
		std::size_t date_in_int;
		ymd_ss >> date_in_int;
		if (date_in_int < 20090102 || 20220329 < date_in_int) // out of date range?
			throw (BTCBadInputException(line));

		std::stringstream	y_ss(yyyy), m_ss(mm), d_ss(dd);
		std::size_t	y_num, m_num, d_num;
		y_ss >> y_num;
		m_ss >> m_num;
		d_ss >> d_num;
		if (y_num < 2009 || 2022 < y_num) // year mm dd range
			throw (BTCBadInputException(line));
		else if (m_num < 1 || 12 < m_num)
			throw (BTCBadInputException(line));
		else if (d_num < 1 || 31 < d_num)
			throw (BTCBadInputException(line));
	}
	else
	{
		throw (BTCBadInputException(line));
	}
}

void	BitcoinExchange::assert_input_value(std::string const &line, std::string const &value)
{
	double value_d;
	std::stringstream value_ss(value);
	value_ss >> value_d;

	if (value.front() == '-' || value_d < 0)// minus?
		throw (BTCNegativeNumException());
	else if (value_d > 1000)// > 1000?
		throw (BTCTooLargeNumException());
	else if (value.find_first_not_of(DIGITS + ".") != std::string::npos)// no digits?
		throw (BTCBadInputException(line));
}

void	BitcoinExchange::assert_input_format(std::string const &line, std::string &date, std::string &value)
{
	int	const	space_ = ' ';

	if (line.empty() || date.empty() || value.empty())
		throw (BTCBadInputException(line));
	else if (date.back() != space_ || value.front() != space_)
		throw (BTCBadInputException(line));
	date.erase(date.end() - 1);
	assert_input_date(line, date);
	value.erase(0, 1);
	assert_input_value(line, value);
}

double	BitcoinExchange::get_px(std::string const &key) const
{
	itr data = px_.lower_bound(key);
	return (data->second);
}

static void	print(std::string const &date, double unit, double px)
{
	std::ostringstream oss;

	oss << date;
	oss << " => ";
	oss << unit;
	oss << " = ";
	oss << std::setw(3) << unit * px;
	std::cout << oss.str() << std::endl;
}

bool	BitcoinExchange::input_handler(std::string const &line)
{
	std::string	key, value_str;
	double		value;
	std::istringstream	iss(line);
	if (std::getline(iss, key, '|') && std::getline(iss, value_str))
	{
		assert_input_format(line, key, value_str);
		std::stringstream	ss(value_str);
		ss >> value;

		double px = get_px(key);
		print(key, value, px);
		return (true);
	}
	else
		return (false);
}

void	BitcoinExchange::calculate(char const **argv)
{
	std::size_t i = 1;
	while (argv[i])
	{
		for_each_line(argv[i], &BitcoinExchange::input_handler);
		i++;
	}
}

void	BitcoinExchange::for_each_line(char const *file, F func)
{
	std::ifstream	ifs(file, std::ios_base::in);
	if (!ifs.is_open())
	{
		throw (std::invalid_argument("Error: could not open file."));
	}
	for (std::string buf; std::getline(ifs, buf);)
	{
		if (buf == "date,exchange_rate" || buf == "date | value")
			continue ;
		try
		{
			bool is_valid = (this->*func)(buf);
			if (!is_valid)
				throw (BTCBadInputException(buf));
		}
		catch (BTCException const &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return ;
}

//! constructors / destructor

BitcoinExchange::BitcoinExchange()
{
	for_each_line("./data.csv", &BitcoinExchange::parse_data_csv);
	return ;
}

// BitcoinExchange::BitcoinExchange(char const *file)
// {
// 	for_each_line(file, &BitcoinExchange::parse_data_csv);
// 	return ;
// }

BitcoinExchange::~BitcoinExchange()
{
	return ;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &rhs)
:px_(rhs.px_)
{
	return ;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this != &rhs)
	{
		this->px_ = rhs.px_;
	}
	return (*this);
}

//!exceptions

std::string const BitcoinExchange::BTCException::what() const
{
	return ("ERROR: BTC exception.");
}

BitcoinExchange::BTCBadInputException::BTCBadInputException(std::string const &inMsg)
:err_msg(inMsg)
{
	return ;
}

std::string const BitcoinExchange::BTCBadInputException::what() const
{
	std::string	ans = "Error: bad input => " + err_msg;
	return (ans);
}

std::string const BitcoinExchange::BTCNegativeNumException::what() const
{
	return ("Error: not a positive number.");
}

std::string const BitcoinExchange::BTCTooLargeNumException::what() const
{
	return ("Error: too large a number.");
}
