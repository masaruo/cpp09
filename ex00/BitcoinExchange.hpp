/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:51:47 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/24 08:29:55 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <utility>
#include <sstream>
#include <functional>

class BitcoinExchange
{
private:
//*typedef
	typedef std::map<std::string, double, std::greater<std::string> >	btc_map;//! std::greater<T> or std::less<T>でソートの順序を変えられる <functional>
	typedef btc_map::const_iterator	itr;
	typedef std::pair<std::string, double>	btc_pair;
	typedef bool(BitcoinExchange::*F)(std::string const &line);
	static std::string DIGITS;
//container
	btc_map	px_;
//helper
	void	for_each_line(char const *file, F func);
	bool	parse_data_csv(std::string const &line);
	bool	input_handler(std::string const &line);
	void	assert_input_format(std::string const &line, std::string &date, std::string &value);
	void	assert_input_date(std::string const &line, std::string const &date);
	void	assert_input_value(std::string const &line, std::string const &value);
	double	get_px(std::string const &key) const;
public:
	BitcoinExchange();
	// BitcoinExchange(char const *file);
	~BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &rhs);
	BitcoinExchange &operator=(BitcoinExchange const &rhs);
	void	calculate(char const **argv);

//! exceptions
	class BTCException
	{
	public:
		virtual std::string const what() const;
	};
	class BTCBadInputException : public BTCException
	{
	private:
		std::string	err_msg;
	public:
		BTCBadInputException(std::string const &inMsg);
		std::string const what() const;
	};
	class BTCNegativeNumException : public BTCException
	{
	public:
		std::string const what() const;
	};
	class BTCTooLargeNumException : public BTCException
	{
	public:
		std::string const what() const;
	};
};

// noexceptの使用ができないため、std::exceptionなどからのerror処理の継承を諦める。
/*
./BitcoinExchange.hpp:40:8: error: exception specification of overriding function is more lax than base version
        class BTCException : std::exception
              ^
/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/__exception/exception.h:77:11: note: overridden virtual function is here
  virtual ~exception() _NOEXCEPT;
*/
