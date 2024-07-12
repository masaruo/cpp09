/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xBitcoinExchange.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:52:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/07/12 10:56:07 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "xString.hpp"

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

double	BitcoinExchange::get_px(std::string const &key) const
{
	itr data = px_.lower_bound(key);
	if (data == px_.end())
		return (0);
	return (data->second);
}

static void	print(std::string const &date, double unit, double px)
{
	std::ostringstream oss;

	oss << date;
	oss << " => ";
	oss << unit;
	oss << " = ";
	oss << unit * px;
	// oss << std::fixed << std::setprecision(2) << std::fixed << unit * px;
	std::cout << oss.str() << std::endl;
}

void	BitcoinExchange::assert_input_value(std::string const in_value)
{
	std::istringstream	iss(in_value);
	double				val;
	iss >> val;
	if (val < 0)
		throw (BTCNegativeNumException());
	if (val > 1000)
		throw (BTCTooLargeNumException());
}

void	BitcoinExchange::assert_input_date(std::string const &readline, std::string const in_date)
{
		std::istringstream	iss(in_date);
		ft::string	y, m, d;
		if (std::getline(iss, y, '-') && std::getline(iss, m, '-') && std::getline(iss, d))
		{
			std::istringstream	y_ss(y);
			std::istringstream	m_ss(m);
			std::istringstream	d_ss(d);
			std::size_t y_d, m_d, d_d;
			y_ss >> y_d;
			m_ss >> m_d;
			d_ss >> d_d;
			if (y_d < 1)
				throw (BTCBadInputException(readline));
			if (m_d < 1 || m_d > 12)
				throw (BTCBadInputException(readline));
			if (d_d < 1 || d_d > 31)
				throw (BTCBadInputException(readline));
		}
		else
		{
			return ;
		}
}

void	BitcoinExchange::assert_alnum_sequence(std::string const &readline)
{
	ft::string	line(readline);

	if (!line.has_only(ft::string::NUMBER, 0, 3) ||
		!line.has_only("-", 4, 4) ||
		!line.has_only(ft::string::NUMBER, 5, 6) ||
		!line.has_only("-", 7, 7) ||
		!line.has_only(ft::string::NUMBER, 8, 9) ||
		!line.has_only(" ", 10, 10) ||
		!line.has_only("|", 11, 11) ||
		!line.has_only(" ", 12, 12) ||
		!line.has_only(ft::string::NUMBER + "-", 13, 13)
		)
	{
		throw (BTCBadInputException(line));
	}
}

bool	BitcoinExchange::input_handler(std::string const &line)
{
	std::string	key, value_str;
	double		value;
	std::istringstream	iss(line);
	if (std::getline(iss, date, '|') && std::getline(iss, value_str))
	{
		date.pop_back();
		assert_input_date(line, date);
		value_str.pop();
		assert_input_value(value_str);
		std::stringstream	ss(value_str);
		ss >> value;

		double px = get_px(date);
		print(date, value, px);
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
	for (xString buf; std::getline(ifs, buf);)
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
