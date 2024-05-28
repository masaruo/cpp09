/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:45:04 by mogawa            #+#    #+#             */
/*   Updated: 2024/05/27 19:39:48 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "xString.hpp"
#include <map>
#include <utility>
#include <exception>
#include <sstream>

class BitcoinExchange
{
public:
	typedef std::map<xString, double, std::greater<xString> >	btc_map;
	typedef btc_map::const_iterator		const_iterator;
private:
	btc_map	px_list;
	static	std::string const DIGITS;
	void	load_data_csv(void);
	void	get_input_date_and_value(xString const &buf, xString &date, double &value) const;
	void	assert_date_validity(xString const &date) const;
	double 	get_valid_ss_value(xString &value) const;
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &rhs);
	BitcoinExchange &operator=(BitcoinExchange const &rhs);
	void	calculate(int argc, char **argv) const;
	// exceptions
	class BTCInvalidInput : public std::exception
	{
		char const *what() const throw ();
	};
};
