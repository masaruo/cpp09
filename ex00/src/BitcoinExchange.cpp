/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:49:18 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/27 21:50:51 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include "iostream"
#include "iomanip"
#include "istream"
#include "sstream"
#include "fstream"

std::string const	DIGITS = "0123456789";

void	BitcoinExchange::load_data_csv(void)
{
	std::ifstream ifs("./data/data.csv");
	if (!ifs)
		throw (std::invalid_argument("Error: could not set up data file"));
	for (xString buf; std::getline(ifs, buf) ; )
	{
		if (buf == "date,exchange_rate")
			continue ;
		std::istringstream	iss(buf);
		xString	key, value_str;
		if (std::getline(iss, key, ',') && std::getline(iss, value_str))
		{
			double	value;
			std::stringstream	ss(value_str);
			ss >> value;
			px_list.insert(std::make_pair(key, value));
		}
		else
		{
			throw (std::invalid_argument("Error: could not set up data file"));
		}
	}
}

double 	BitcoinExchange::get_valid_ss_value(xString &value) const
{
	bool	is_valid = true;
	double				value_d;

	if (value.front() != ' ' || value.size() < 2)
		is_valid = false;
	else
		value.pop();
	if (value > "1000" || value.contain_not_of(DIGITS + "."))
		is_valid = false;
	std::stringstream	val_ss(value);
	val_ss >> value_d;
	if (!val_ss || !val_ss.str().empty())
		is_valid = false;
	if (!is_valid)
	{
		throw (std::invalid_argument("Error: unit number is not valid"));
		return (0);
	}
	else
		return (value_d);
}

void	BitcoinExchange::assert_date_validity(xString const &date) const
{
	xString	y, m, d;
	char const	SPACE = ' ';
	std::istringstream	iss(date);
	bool	is_valid = true;

	if (std::getline(iss, y, '-') && std::getline(iss, m, '-') && std::getline(iss, d))
	{
		//year validation
		if (y.contain_not_of(DIGITS) || y.size() != 4 || y < "2009")
			is_valid = false;

		//month validation
		if (m.contain_not_of(DIGITS) || m.size() != 2 || y < "01" || y > "12") 
			is_valid = false;

		//delete space at back
		if (d.back() != SPACE)
			is_valid = false;
		else
			d.pop_back();
		
		//date validation
		if (d.contain_not_of(DIGITS) || m.size() != 2 || y < "01" || y > "31")
			is_valid = false;
	}
	else
	{
		is_valid = false;
	}
	if (!is_valid)
		throw (std::invalid_argument("Error: invalid date format"));
}

void	BitcoinExchange::get_input_date_and_value(xString const &buf, xString &date, double &value) const
{
	std::istringstream	iss(buf);
	xString	date_str, value_str;
	if (std::getline(iss, date_str, '|') && std::getline(iss, value_str))
	{
		assert_date_validity(date_str);
		date = date_str;
		value = get_valid_ss_value(value_str);
	}
	else
	{
		throw (std::invalid_argument("Error: Failed to parse input"));
	}
}

void	BitcoinExchange::calculate(int argc, char **argv) const
{
	if (argc != 2)
		throw (std::invalid_argument("Error: could not open file"));
	std::ifstream	ifs(argv[1]);
	if (!ifs)
		throw (std::invalid_argument("Error: could not open input date"));
	for (xString buf; std::getline(ifs, buf) ; )
	{
		if(buf == "date | value")
			continue ;
		xString date;
		double	value;
		get_input_date_and_value(buf, date, value);
		const_iterator	pos = px_list.lower_bound(date);
		if (pos != px_list.end())
		{
			//todo print
		}
	}
}

BitcoinExchange::BitcoinExchange()
{
	load_data_csv();
	return ;
}

BitcoinExchange::~BitcoinExchange()
{
	return ;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &rhs)
:px_list(rhs.px_list)
{
	return ;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this != &rhs)
	{
		px_list.operator=(rhs.px_list);
	}
}

// char const	*BitcoinExchange::BTCInvalidInput::what() const throw ()
// {
// 	return ()
// }
