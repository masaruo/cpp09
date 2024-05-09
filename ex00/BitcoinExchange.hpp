/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:51:47 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/09 15:15:18 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <string>
#include <stdexcept>

class BitcoinExchange;
typedef void	(BitcoinExchange::*f)(std::string const &buf);
typedef std::map<std::string, double>::const_iterator map_iter;
typedef std::string::const_iterator	string_iter;

class BitcoinExchange
{
private:
	std::map<std::string, double>	rate_;
	//helper funcs
	void		parseData(std::string const &file, f fptr);
	void		parse_data_csv(std::string const &buf);
	void		input_handler(std::string const &buf);//コンストにしたいが、関数ポインタのか型地が異なってしまう
	map_iter	get_spot_or_lower_iter(std::string const &key) const;
	void		assert_correct_value_range(std::string const &value, std::string const &buf) const;
	void		assert_correct_input(std::string const &date, std::string const &buf, std::string const &value) const;
	void		assert_date_correct(std::string const &date, std::string const &buf) const;
	//hidden constructor
	BitcoinExchange();
public:
	BitcoinExchange(std::string const &file);
	BitcoinExchange(BitcoinExchange const &rhs);
	~BitcoinExchange();
	BitcoinExchange &operator=(BitcoinExchange const &rhs);

	class BTCException : public std::logic_error
	{
	public:
		BTCException();//! need constructor to inherit non std::exception
		virtual char const	*what() const throw();
	};
	class BtcNegativeValueException : public BTCException
	{
	public:
		char const	*what() const throw();
	};
	class BtcTooLargeValueException : public BTCException
	{
	public:
		char const	*what() const throw();
	};
	class BtcBadInput
	{
	private:
		std::string	const error_msg;
	public:
		BtcBadInput(std::string const &inMsg);//! this way can get msg to error class
		char const	*what() const throw();
		// https://stackoverflow.com/questions/53829852/exception-specification-of-overriding-function-is-more-lax-than-base-version
	};
};
