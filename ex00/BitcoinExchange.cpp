/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:52:05 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/07 16:21:03 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <utility>
#include <algorithm>

static std::pair<std::string, double>	parse_data_csv(std::string const &buf)
{
	std::pair<std::string, double>	pair = std::make_pair("header", 0);

	std::string::size_type	const	delim_pos = buf.find(',');
	std::string const				date_ = buf.substr(0, delim_pos);
	if (date_ == "date")
		return (pair);
	std::string const				value_ = buf.substr(delim_pos + 1, buf.size());
	double const					value_in_double = std::atof(value_.c_str());
	pair.first = date_;
	pair.second = value_in_double;
	return (pair);
}

static	bool	check_date_format(std::string const &dt)
{

	std::string::const_iterator	begin = dt.begin();
	std::string::const_iterator	end = dt.end();
	std::string::const_iterator	iter = begin;
	std::string					cal[3];
	std::string::value_type		delim_pos = 0;

	std::size_t 				i = 0;
	while (delim_pos != std::string::npos)
	{
		delim_pos = dt.find("-", delim_pos);
		cal[i](dt, )
	}
}

static std::pair<std::string, double>	parse_data_input(std::string const &buf)
{
	std::pair<std::string, double>	pair = std::make_pair("fail", 0);
	std::string::const_iterator		end = buf.end();
	std::string::const_iterator		iter = buf.begin();
	std::string::const_iterator		delim_pos = std::find(iter, end, " | ");

	if (buf.empty())
		pair.first = "Error: empty data.";
	else if (delim_pos == end)
		pair.first = "Error: wrong format.";
	std::string	date_(buf.begin(), delim_pos);
	std::string	value_(delim_pos + 1, end);
	//wrong format year month day
	//int or float and between 0 and 1000
	
}

template <typename F>
void	BitcoinExchange::parseData(std::string const &file, F functor)
{
	std::ifstream	ifs(file);
	if (ifs.fail())
	{
		std::cout << "failed to open the data.csv." << std::endl;
		std::exit(1);
	}
	for (std::string buf; std::getline(ifs, buf);)
	{
		std::pair<std::string, double>	pair = functor(buf);
		data_.insert(pair);
	}
}

BitcoinExchange::BitcoinExchange(){ return ; }
BitcoinExchange::BitcoinExchange(std::string const &input)
{
	parseData("./data.csv", parse_data_csv);
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
