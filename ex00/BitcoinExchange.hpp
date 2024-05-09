/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:51:47 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/08 18:43:38 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>
#include <stdexcept>

class BitcoinExchange;
typedef void	(BitcoinExchange::*f)(std::string const &buf);
typedef std::map<std::string, double>::const_iterator btc_it;
typedef std::string::const_iterator	s_it;

class BitcoinExchange
{
private:
	std::map<std::string, double>	rate_;
	//helper
	void	parseData(std::string const &file, f fptr);
	void	parse_data_csv(std::string const &buf);
	void	input_handler(std::string const &buf);//コンストにしたいが、関数ポインタのか型地が異なってしまう
	btc_it	get_spot_or_lower_iter(std::string const &key) const;
	void	assert_correct_value_range(std::string const &value) const;
	void	assert_correct_input(std::string const &date, std::string const &delim, std::string const &value) const;
	BitcoinExchange();//hidden
public:
	BitcoinExchange(std::string const &file);
	BitcoinExchange(BitcoinExchange const &rhs);
	~BitcoinExchange();
	BitcoinExchange &operator=(BitcoinExchange const &rhs);

	class BtcNegativeValueException : public std::out_of_range
	{
	public:
		BtcNegativeValueException():std::out_of_range("Error: not a positive number."){}
		char const	*what() const throw ();
	};

	class BtcTooLargeValueException : public std::out_of_range
	{
	public:
		BtcTooLargeValueException():std::out_of_range("Error: too large a number."){}
		char const *what() const throw ();
	};

	// class BtcBadInputException : public std::runtime_error
	// {
	// private:
	// 	std::string	msg_;
	// 	std::string	err_;
	// public:
	// 	BtcBadInputException(std::string const &msg):std::runtime_error(msg), msg_(msg), err_("Error: bad input => " + msg){}
	// 	char const *what() const throw ();
	// };
};
